Frequently Asked Questions
==========================

**Need help? Please see here first.**
 - To help you quickly resolve your issues, we have compiled frequently asked questions and troubleshooting methods below. Please try self-troubleshooting first, as this is usually the most efficient way to solve problems.
 - If you cannot find a solution here, please feel free to contact our after-sales team for further technical support.

----

**1.The device doesn’t respond at all after powering on.**

 - This is normal, please don’t worry! To maintain flexibility, our development boards are not pre-installed with functional programs. Simply follow our introductory tutorial to burn your first program and begin your creative journey.

----

**2.The ESP32 development board is not recognized or the program cannot be burned.**

 - Please make sure the CH340 driver is correctly installed on your computer.Click here to view the installation tutorial. :ref:`Install Serial Port Tool` 

 - Use a Type-C data cable （make sure it supports data transmission, not just charging）.

 - Open the Device Manager and check if the “USB-SERIAL CH340” device appears.

 - If the port number is occupied, reconnect the USB or restart the computer.

----

**3.Kept getting errors when uploading code using the Arduino IDE.**

 - Check if the ESP32 development board core package is version 2.0.12.
 - Check if all library files have been imported and check for updates.

----

**4.The button is unresponsive, the speaker is silent, and the RGB lights are not on.**

 - Please check that the wiring is correct and the power supply is connected.
 - Connect one end of the button and speaker to the ESP32 IO pin, and the other end to GND.
 - The interface plane of the RGB LED strip should face Type-C.

----




