// Tonokip RepRap firmware rewrite based off of Hydra-mmm firmware.
// Licence: GPL
#include <WProgram.h>
#include "fastio.h"
#include "enumcodes.h"
//#define STATUS_OK 0
//#define STATUS_SD 1
//#define STATUS_ERROR 2
//const char* status_str[] = { "Ok", "SD", "Error"};
    

//#define ERROR_CODE_NO_ERROR 0
//#define ERROR_CODE_HOTEND_TEMPERATURE 1
//#define ERROR_CODE_BED_TEMPERATURE 2
//const char* error_code_str[] = { "No Error", "Hotend", "Bed" };



extern "C" void __cxa_pure_virtual();

//void __cxa_pure_virtual(){};
void get_command();
void process_commands();
void reset_status();

void manage_inactivity(byte debug);

void manage_heater();
void wait_for_temp();
int temp2analogu(int celsius, const short table[][2], int numtemps, int source);
int analog2tempu(int raw, const short table[][2], int numtemps, int source);
#ifdef HEATER_USES_THERMISTOR
    #define HEATERSOURCE 1
#endif
#ifdef HEATER_USES_AD595
    #define HEATERSOURCE 2
#endif
#ifdef HEATER_USES_MAX6675
    #define HEATERSOURCE 3
#endif
#ifdef BED_USES_THERMISTOR
    #define BEDSOURCE 1
#endif
#ifdef BED_USES_AD595
    #define BEDSOURCE 2
#endif
#ifdef BED_USES_MAX6675
    #define BEDSOURCE 3
#endif

#define temp2analogh( c ) temp2analogu((c),temptable,NUMTEMPS,HEATERSOURCE)
#define temp2analogBed( c ) temp2analogu((c),bedtemptable,BNUMTEMPS,BEDSOURCE)
#define analog2temp( c ) analog2tempu((c),temptable,NUMTEMPS,HEATERSOURCE)
#define analog2tempBed( c ) analog2tempu((c),bedtemptable,BNUMTEMPS,BEDSOURCE)
#if X_ENABLE_PIN > -1
#define  enable_x() WRITE(X_ENABLE_PIN, X_ENABLE_ON)
#define disable_x() WRITE(X_ENABLE_PIN,!X_ENABLE_ON)
#else
#define enable_x() ;
#define disable_x() ;
#endif
#if Y_ENABLE_PIN > -1
#define  enable_y() WRITE(Y_ENABLE_PIN, Y_ENABLE_ON)
#define disable_y() WRITE(Y_ENABLE_PIN,!Y_ENABLE_ON)
#else
#define enable_y() ;
#define disable_y() ;
#endif
#if Z_ENABLE_PIN > -1
#define  enable_z() WRITE(Z_ENABLE_PIN, Z_ENABLE_ON)
#define disable_z() WRITE(Z_ENABLE_PIN,!Z_ENABLE_ON)
#else
#define enable_z() ;
#define disable_z() ;
#endif
#if E_ENABLE_PIN > -1
#define  enable_e() WRITE(E_ENABLE_PIN, E_ENABLE_ON)
#define disable_e() WRITE(E_ENABLE_PIN,!E_ENABLE_ON)
#else
#define enable_e() ;
#define disable_e() ;
#endif

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2
#define E_AXIS 3

void FlushSerialRequestResend();
void ClearToSend();

void get_coordinates();
void prepare_move();
void linear_move(unsigned long steps_remaining[]);
void do_step(int axis);
void kill(byte debug);

void check_buffer_while_arc();
void plan_buffer_line(float x, float y, float z, float e, float feed_rate);
#ifdef USE_ARC_FUNCTION
  inline void get_arc_coordinates();
#endif
void prepare_arc_move(char isclockwise);

// This struct is used when buffering the setup for each linear movement "nominal" values are as specified in 
// the source g-code and may never actually be reached if acceleration management is active.
typedef struct {
  // Fields used by the bresenham algorithm for tracing the line
  long steps_x, steps_y, steps_z, steps_e;  // Step count along each axis

  unsigned long step_event_count;                    // The number of step events required to complete this block
  long accelerate_until;           // The index of the step event on which to stop acceleration
  long decelerate_after;           // The index of the step event on which to start decelerating
  long acceleration_rate;          // The acceleration rate used for acceleration calculation
  unsigned char direction_bits;             // The direction bit set for this block (refers to *_DIRECTION_BIT in config.h)

  #ifdef ADVANCE
    long advance_rate;
    volatile long initial_advance;
    volatile long final_advance;
    float advance;
  #endif

  // Fields used by the motion planner to manage acceleration
//  float speed_x, speed_y, speed_z, speed_e;          // Nominal mm/minute for each axis
  float nominal_speed;                               // The nominal speed for this block in mm/min  
  float entry_speed;                                 // Entry speed at previous-current junction in mm/min
  float max_entry_speed;                             // Maximum allowable junction entry speed in mm/min
  float millimeters;                                 // The total travel of this block in mm
  float acceleration;                                // acceleration mm/sec^2
  unsigned char recalculate_flag;                    // Planner flag to recalculate trapezoids on entry junction
  unsigned char nominal_length_flag;                 // Planner flag for nominal speed always reached


  // Settings for the trapezoid generator
  long nominal_rate;                                 // The nominal step rate for this block in step_events/sec 
  long initial_rate;                        // The jerk-adjusted step rate at start of block  
  long final_rate;                          // The minimal rate at exit
  long acceleration_st;                              // acceleration steps/sec^2
  volatile char busy;
} block_t;

