Frequently Asked Questions
==========================

**Need help? Please see here first.**

 - To help you quickly resolve your issues, we have compiled frequently asked questions and troubleshooting methods below. Please try self-troubleshooting first, as this is usually the most efficient way to solve problems.
 - If you cannot find a solution here, please feel free to contact our after-sales team for further technical support.

----

**1.The device doesn’t respond at all after powering on.**

 - This is normal, please don’t worry! To maintain flexibility, our development boards are not pre-installed with functional programs. Simply follow our introductory tutorial to burn your first program and begin your creative journey.

----

**2.The servo motor still doesn't respond after the program is burned.**

 - Please ensure that an 18650 battery is installed at the bottom of the expansion board and that it is fully charged. Do not use the data cable for power supply, as this will result in insufficient power.

----

**3.The servo motors are not rotating or rotating in the wrong direction.**

 - Please check the servo wiring: ensure the brown wire (GND) is connected to the ground pin, the red wire (VCC) to 5V, and the orange wire (PWM) to the correct GPIO pin on the ESP8266 board. Also, verify that the servo orientation is correct during assembly - upper servos should face upward, lower servos downward.

----

**4.Unable to connect to the robot's Wi-Fi network.**

 - Ensure the robot is powered on and the ESP8266 board is functioning. On your phone or computer, search for Wi-Fi networks named "Robot-XXXX" and connect using the password "12345678". If the network doesn't appear, try resetting the board or checking the firmware flashing process.

----

**5.The infrared remote control is not working.**

 - The infrared remote control does not contain batteries. Ensure the batteries are installed correctly and point the remote control directly at the robot's infrared receiver.

----


**6.Firmware flashing fails.**

 - Verify the USB cable and port are functional. Ensure the CP2102 driver is installed and the serial port is correctly selected in the flashing tool. Disconnect any servos or sensors during flashing. If problems continue, try a different USB port, restart your computer, or use another cable.

----

**7.Serial port driver installation issues.**

 - For Windows, press Win+X to open Device Manager and check if the CP2102 driver is recognized. If not, download and install the official driver from the provided link. For other operating systems, ensure compatible drivers are installed. Restart your computer after installation.

----

**8.The spider robot exhibits uncoordinated gait and abnormal walking.**

 - Please click here to jump to the servo calibration guide section. :ref:`Servo calibration and debug`


----
