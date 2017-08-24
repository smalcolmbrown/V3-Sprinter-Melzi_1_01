# The Completely Unofficial Eaglemoss Vector 3 3D Printer LCD Technical Guide

![alt text][logo]

[logo]: https://www.eaglemoss.com/uploads/141647767867724/original.png "Eaglemoss Vector 3 Firmware Technical Guide"

# Version 1.01.x

![alt text][lcd_over]

[lcd_over]: https://i2.wp.com/v3uc.com/wp-content/uploads/hm_bbpui/3439/3sdh017cme486uxe6o4y3q55e978cud6.jpg "The LCD fitted to the V3 printer"


### The Splash Screen

![alt text][splash]

[splash]: https://i2.wp.com/v3uc.com/wp-content/uploads/hm_bbpui/3458/nb6afttzvukeynlqd56smublbxsfetis.jpg "The LCD Splash screen"


### The Information Screen

![alt text][info]

[info]: https://i0.wp.com/v3uc.com/wp-content/uploads/hm_bbpui/3458/ves0xbpjv0nkez0huw06h1ijo0oskwa5.jpg "The LCD information screen"


## What you need to add a LCD to your Vector 3 3D Printer

1. A 2004 alpha numeric LCD with a YwRobot I2C LCD driver

![alt text][lcd_front]

[lcd_front]: https://ardushop.ro/135-thickbox_default/lcd-2004.jpg "The 20 * 40 aplha numeric LCD from the front"

and from the back showing the YwRobot I2C Lcd driver fitted

![alt text][lcd_back]

[lcd_back]: http://3.bp.blogspot.com/-YtWLjAsjH4A/U84ws4xBOwI/AAAAAAAAAL4/5nC6RlHy0p4/s1600/lcd6.png "The LCD back with YwRobot I2C Lcd driver fitted"

2. the lead that connects the main board to the outside. plugs into JP 16 on the main board Pin 1 (the red trace on the 10 way IDC lead) is nearest to JP 17

![alt text][lcd_lead]

[lcd_lead]: https://i0.wp.com/v3uc.com/wp-content/uploads/hm_bbpui/3447/gyzwsy9tmeknolon0w6k0dr4mx66ldqr.jpg "The the extender lead that extends JP 16 on the main boaed"

3. The lead that connect the 10 way male socket to the XwRobot I2C LCD driver

![alt text][lcd_i2c_lead]

[lcd_i2c_lead]: https://i0.wp.com/v3uc.com/wp-content/uploads/hm_bbpui/3447/8ixl4b4y4rdbppff0ba8jk1me5ihwgfv.jpg "The lead that connect the 10 way male socket to the XwRobot I2C LCD driver"

The lead that connects the I2C interface on the LCD to the 10 way plug on the printer on one end we have a 10 way IDC socket 2×5 way (Maplin code JB59P)  and the other we have two DuPont connectors the I2C connector is 1 * 4 way DuPont and the other is 1 * 8 way DuPont connector available here

If you are not good at soldering then invest in a crimper for the DuPont connectors ebay.

IDC 10 way pin 10 goes to 4 way DuPont pin 1 (GND)  
IDC 10 way pin  9 goes to 4 way DuPont pin 2 (VCC)  
IDC 10 way pin  1 goes to 4 way DuPont pin 3 (SDA)  
IDC 10 way pin  3 goes to 4 way DuPont pin 4 (SCL)  

IDC 10 way pin  2 goes to 8 way DuPont pin 4 (A1)  
IDC 10 way pin  4 goes to 8 way DuPont pin 3 (A2)  
IDC 10 way pin  5 goes to 8 way DuPont pin 3 (TX) 
IDC 10 way pin  6 goes to 8 way DuPont pin 2 (A2)  
IDC 10 way pin  7 goes to 8 way DuPont pin 5 (RX)  
IDC 10 way pin  8 goes to 8 way DuPont pin 1 (A4)  
IDC 10 way pin  9 goes to 8 way DuPont pin 7 (VCC)  
IDC 10 way pin 10 goes to 8 way DuPont pin 8 (GND)  

NOTE the DuPont connector pin 1 is denoted by a small triangle  
