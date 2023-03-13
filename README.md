This repo contains my personal customizations for the Nixi-Tube clock I purchased, and assembled, from GRA & AFCH in early 2023.

The clock is their Arduino Shield Nixie IN-14 model. I purchased the kit and assembled it; and with the help of a woodworking friend made a case for it.

<b>NOTE</b>: As of 3/13/2023 this clock does not support automatic Daylight Savings / Standard Time sensing and adjustment. To adjust for daylight savings if using the GPS receiver to sync time, you need to set the "timezone" ahead by one hour. levinedl's github has code for auto daylight savings adjustment, which was submitted as a pull request to gra-afch, tho they have ignored it. Sometime prior to the next shift back to Standard Time in the US I plan to review and incorporate levinedl's DST branch into my own code. See @ https://github.com/levinedl/NixeTubesShieldNCS314/tree/dst/Firmware/Source%20code/Hardware%20Version%203.x%20(HW3.2)/NixieClockShield_NCS314.

Per original GRA & AFCH Readme:

Sketch for Arduino UNO and Nixie Tubes Shield NCS314 and NCS312 by GRA &amp; AFCH

1. This repository content sources of project for Nixie Clock developed by GRA & AFCH.

	Folders description:
  
	FIRMWARES - source code that must be complied in Arduino IDE, and allready compiled Binary files in *.hex format ready to be uploaded on to property board by flasher.
  
	GRA & AFCH Compiled Firmware Flasher - flasher (uploader) that must be used in prevois step.
  
	LIBRARIES - Arduino libraries without which compiling will be failed. That folders must be copied to Arduino LIBRARIES folder, (default path: C:\Users\USER_NAME\Documents\Arduino\libraries)
  
	SCHEMES - electrical shemes for boards: for Nixie Clock Main Units - MCU, and for Nixie Tubes Boards
  
	USB DRIVERS - drivers for USB-to-SERIAL(UART) converters
  
	USER MANUAL - end user's manuals.

2. Link to YouTube video with preparing, compiling and uploading firmware to clock:
https://youtu.be/DQZWPn0iAHw

3. Compatibility:

	Nixie Clock Shield for Arduino - <b>NCS314</b> (Hardware Versions: HW1.0, HW1.1, HW1.2, HW2.0, HW2.2) <br>
	Nixie Clock Shield for Arduino - <b>NCS312</b> (Hardware Versions: HW1.0 - HW1.3) - use the firmware for NCS314 version 2.0
	
The GRA & AFCH on-line presence is at: http://gra-afch.com
