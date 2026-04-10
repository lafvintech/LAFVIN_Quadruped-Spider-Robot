Frequently Asked Questions
==========================

**Need help? Please see here first.**
 - To help you quickly resolve your issues, we have compiled frequently asked questions and troubleshooting methods below. Please try self-troubleshooting first, as this is usually the most efficient way to solve problems.
 - If you cannot find a solution here, please feel free to contact our after-sales team for further technical support.

----

**1.The device doesn’t respond at all after powering on.**

 - This is normal, please don’t worry! To maintain flexibility, our development boards are not pre-installed with functional programs. Simply follow our introductory tutorial to burn your first program and begin your creative journey.

----

**2.The servo motors are not rotating or rotating in the wrong direction.**

 - Please check the servo wiring: ensure the brown wire (GND) is connected to the ground pin, the red wire (VCC) to 5V, and the orange wire (PWM) to the correct GPIO pin on the ESP8266 board. Also, verify that the servo orientation is correct during assembly - upper servos should face upward, lower servos downward.

----

**3.Unable to connect to the robot's Wi-Fi network.**

 - Ensure the robot is powered on and the ESP8266 board is functioning. On your phone or computer, search for Wi-Fi networks named "Robot-XXXX" and connect using the password "12345678". If the network doesn't appear, try resetting the board or checking the firmware flashing process.

----

**4.The mobile APP cannot control the robot.**

 - After connecting to the robot's Wi-Fi, open the APP and tap the connection icon in the upper left corner. Make sure you're connected to the correct Wi-Fi network (Robot-XXXX). If connection fails, restart both the robot and your device, then try again.

----

**5.The infrared remote control is not working.**

 - Check the battery in the remote control and ensure it's inserted correctly. Point the remote directly at the robot's infrared receiver and avoid obstructions. If issues persist, verify that the infrared sensor is properly connected to the expansion board.

----

**6.Ultrasonic obstacle avoidance is not functioning.**

 - Ensure the ultrasonic sensor is correctly wired: VCC to 5V, GND to ground, Trig and Echo to the designated pins on the ESP8266. Check that the sensor is not obstructed and the firmware includes obstacle avoidance code. Test the sensor connections and power supply.

----

**7.Firmware flashing fails.**

 - Verify the USB cable and port are functional. Ensure the CP2102 driver is installed and the serial port is correctly selected in the flashing tool. Disconnect any servos or sensors during flashing. If problems continue, try a different USB port, restart your computer, or use another cable.

----

**8.Serial port driver installation issues.**

 - For Windows, press Win+X to open Device Manager and check if the CP2102 driver is recognized. If not, download and install the official driver from the provided link. For other operating systems, ensure compatible drivers are installed. Restart your computer after installation.

----

**9.Missing or damaged components.**

 - Upon receiving the kit, check all components against the Bill of Materials in the Introduction section. If any items are missing or damaged, contact our technical support team immediately with your order details for replacement.

----

**10.Unable to download code and resources.**

 - Use the provided Dropbox links in the Resource Download section. Ensure you have a stable internet connection. If download fails, try using a different browser or device. All necessary code, libraries, and tools are available through these links.

----



