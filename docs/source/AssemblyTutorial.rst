Assembly Tutorial
=================

Assembly Video
--------------

- The video provides a step-by-step assembly tutorial for the quadruped spider robot. Watching this video will help you assemble it quickly.

- For a more detailed assembly guide with text and images, please continue reading below.

----

Assembly Tutorial
-------------------

STEP 1: Assemble expansion board
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Parts list：** Expansion board、Acrylic body panel、M3*10mm screw (4 PCS)、M3*16mm copper pillar (4 PCS).

.. image:: _static/AssemblyTutorial/2.8266.png
   :width: 800
   :align: center

.. raw:: html

   <div style="margin-top: 30px;"></div>

----

STEP 2: Assemble development board
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Parts list：** ESP8266 development board.

.. image:: _static/AssemblyTutorial/3.8266.png
   :width: 800
   :align: center

.. raw:: html

   <div style="margin-top: 30px;"></div>

.. note::

   Ensure the development board orientation matches the silk-screen markings on the expansion board to avoid incorrect installation.

----

STEP 3: Assemble  body servo 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Parts list：** MG90S Servo (4 PCS)、M2*10mm screw (8 PCS)、M2 nut (8 PCS).

.. image:: _static/AssemblyTutorial/4.BODYSERVO.png
   :width: 800
   :align: center

.. raw:: html

   <div style="margin-top: 30px;"></div>

.. note::

   Make sure the four servos are installed with the correct orientation: the two upper servos face upward while the two lower servos face downward.

----

STEP 4: Wiring of the body servo  
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. note::

 The MG90S servo motors are crucial components for controlling the robot's leg movements. Each servo has three wires with specific colors and functions:

 .. image:: _static/AssemblyTutorial/1.servo.png
   :width: 800
   :align: center

 .. raw:: html

   <div style="margin-top: 30px;"></div>

 - **Brown Wire**: Ground (GND) - Connect to the ground pin on the expansion board
 - **Red Wire**: Power (VCC) - Connect to the 5V power pin on the expansion board
 - **Yellow Wire**: Signal (PWM) - Connect to the corresponding GPIO pin on the ESP8266 board

----

**The wiring diagram for the servo motors in the body is shown in the figure:**

 .. image:: _static/AssemblyTutorial/5.body.png
   :width: 800
   :align: center

 .. raw:: html

   <div style="margin-top: 30px;"></div>

----

**Image of the assembled spider body parts:**

 .. image:: _static/AssemblyTutorial/6.bodycom.png
   :width: 800
   :align: center

 .. raw:: html

   <div style="margin-top: 30px;"></div>

----

.. raw:: html

   <div style="background-color: orange; padding: 10px; border: 1px solid #ccc; margin: 10px 0;">
   <strong>Important:</strong> After connecting the servos to the body, install the battery while ensuring the development board is properly mounted on the expansion board. Then, turn on the power of the expansion board. The system will automatically reset, and the servos will rotate to their initial positions.
   </div>

----

STEP 5: Assemble the spider's thigh 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**Parts list：** Acrylic plate for thigh (8 PCS)、One-swing arm (8 PCS)、M2*8mm self-tapping screw (16 PCS).

 .. image:: _static/AssemblyTutorial/7.baibi.png
   :width: 800
   :align: center

 .. raw:: html

   <div style="margin-top: 30px;"></div>

.. note::

 - The one-swing arm and M2*8mm self-tapping screws used in this step are all included in the servo package.
 - A total of 8 need to be installed for use in subsequent steps.

----

STEP 6: Trim swing arm
~~~~~~~~~~~~~~~~~~~~~~~

To ensure smooth movement of the spider robot, please trim the servo arms to the appropriate length as shown in the diagram. Please handle with care during operation.

 .. image:: _static/AssemblyTutorial/8.xiujian.png
   :width: 800
   :align: center

 .. raw:: html

   <div style="margin-top: 30px;"></div>

----

