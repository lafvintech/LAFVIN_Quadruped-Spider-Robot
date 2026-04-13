kit For Learning Course
======================

**In this section, we will use the components in this kit to expand our learning, gradually mastering the principles and functional characteristics of each component in order of depth, and completing the corresponding program writing.**

----

1. Make the servo motor turn
-----------------------------

Wiring diagram
~~~~~~~~~~~~~~

- MG90 Servo —— ESP8266 D4

----

Example code
~~~~~~~~~~~~

.. code-block:: cpp

 #include <Servo.h>

 Servo myservo;
 #define SERVO_PIN D4

 void setup() {
  myservo.attach(SERVO_PIN);
  myservo.write(0);
 }

 void loop() {
  myservo.write(180);
  delay(3000);
  
  myservo.write(0);
  delay(3000);
 }

----

Achieved Effect
~~~~~~~~~~~~~~~~

- Connect the servo motor to pin D4; the servo motor will rotate 180° every 3 seconds.

- You can use this program to sequentially switch between connecting 8 servos to test whether the servos are working properly.

.. raw:: html

   <div style="margin-top: 30px;"></div>

.. image:: _static/course/1.1servo.gif
   :width: 800
   :align: center

----

Rotate two servo motors
------------------------

Wiring diagram
~~~~~~~~~~~~~~

- MG90 Servo —— ESP8266 D4

- MG90 Servo —— ESP8266 D8

----

Example code
~~~~~~~~~~~~

.. code-block:: cpp

 #include <Servo.h>

 Servo myservo1;  // Pin D4 SERVO
 Servo myservo2;  // Pin D8 SERVO
 
 #define SERVO_PIN1 D4
 #define SERVO_PIN2 D8

 void setup() {
  myservo1.attach(SERVO_PIN1);
  myservo2.attach(SERVO_PIN2);
  
  myservo1.write(0);
  myservo2.write(0);
 }

 void loop() {
  // Both servos rotate 180 degrees simultaneously

  myservo1.write(180);
  myservo2.write(180);
  delay(2000);
  
  // Both servos return to 0 degrees simultaneously

  myservo1.write(0);
  myservo2.write(0);
  delay(2000);
 }

----

Achieved Effect
~~~~~~~~~~~~~~~~

- Similar to the previous lesson, you only need to add one more servo and one more definition in the code to make both servos move simultaneously.

.. raw:: html

   <div style="margin-top: 30px;"></div>

.. image:: _static/course/1.1servo.gif
   :width: 800
   :align: center

----


Let the spider move forward
----------------------------

In the previous two lessons, we've already gotten two servos moving. Next, we'll get all eight servos moving simultaneously to propel the spider forward.

----

Wiring diagram
~~~~~~~~~~~~~~

Please connect the wires as shown in the diagram below.

.. raw:: html

   <div style="margin-top: 30px;"></div>

.. image:: _static/course/2.body.png
   :width: 800
   :align: center

.. raw:: html

   <div style="margin-top: 30px;"></div>

.. image:: _static/course/3.SERVO2.png
   :width: 800
   :align: center

----

.. code-block:: cpp

  #include <Servo.h>
  #include <Arduino.h>

  // Servo pin definitions
  const int SERVO_PINS[] = {14, 12, 13, 15, 16, 5, 4, 2};  // G14, G12, G13, G15, G16, G5, G4, G2
  const int ALLSERVOS = 8;
  const int ALLMATRIX = 9;  // 8 servos + time

  // Servo angle range
  const int SERVOMIN = 400;
  const int SERVOMAX = 2400;
  const int ANGLE_MIN = 1;
  const int ANGLE_MAX = 180;

  // Servo zero position
  const int Servo_Zero[] = { 135, 45, 135, 45, 45, 135, 45, 135, 500 };

  // Forward motion sequence
  const int Servo_Forward_Step = 11;
  const int Servo_Forward[][ALLMATRIX] = {
    // G14, G12, G13, G15, G16, G5,  G4,  G2,  ms
    {  70,  90,  90, 110, 110,  90,  90,  70, 200 }, // standby
    {  90,  90,  90, 110, 110,  90,  45,  90, 200 }, // leg1,4 lift up
    {  70,  90,  90, 110, 110,  90,  45,  70, 200 }, // leg1,4 put down
    {  70,  90,  90,  90,  90,  90,  45,  70, 200 }, // leg2,3 lift up
    {  70,  39, 141,  90,  90,  90,  90,  70, 200 }, // leg1,4 backward, leg2 forward
    {  70,  39, 141, 110, 110,  90,  90,  70, 200 }, // leg2,3 put down
    {  90,  90, 141, 110, 110,  90,  90,  90, 200 }, // leg1,4 lift up
    {  90,  90,  90, 110, 110, 135,  90,  90, 200 }, // leg2,3 backward
    {  70,  90,  90, 110, 110, 135,  90,  70, 200 }, // leg1,4 put down
    {  70,  90,  90, 110,  90, 135,  90,  70, 200 }, // leg3 lift up
    {  70,  90,  90, 110, 110,  90,  90,  70, 200 }, // leg3 put down forward
  };

  class SpiderBotMotion {
  public:
      Servo servos[8];
      
      // Initialize servos
      void init() {
          for (int i = 0; i < ALLSERVOS; i++) {
              servos[i].attach(SERVO_PINS[i], SERVOMIN, SERVOMAX);
          }
          delay(200);
      }
      
      // Move all servos to zero position
      void zero() {
          for (int i = 0; i < ALLSERVOS; i++) {
              int angle = constrain(Servo_Zero[i], ANGLE_MIN, ANGLE_MAX);
              servos[i].write(angle);
          }
          delay(Servo_Zero[8]);
      }
      
      // Forward motion
      void forward() {
          for (int step = 0; step < Servo_Forward_Step; step++) {
              for (int servo = 0; servo < ALLSERVOS; servo++) {
                  int angle = constrain(Servo_Forward[step][servo], ANGLE_MIN, ANGLE_MAX);
                  servos[servo].write(angle);
              }
              delay(Servo_Forward[step][8]);
          }
      }
      
      // Standby pose
      void standby() {
          int standby_angles[] = {60, 90, 90, 120, 120, 90, 90, 60};
          for (int i = 0; i < ALLSERVOS; i++) {
              int angle = constrain(standby_angles[i], ANGLE_MIN, ANGLE_MAX);
              servos[i].write(angle);
          }
          delay(500);
      }
  };

  SpiderBotMotion robot;

  void setup() {
      Serial.begin(9600);
      Serial.println("QuadBot Starting...");
      
      // 1. Initialize servos
      robot.init();
      
      // 2. Move servos to zero position on power-up
      Serial.println("Moving to zero position...");
      robot.zero();
      delay(500);
      
      // 3. Enter standby state
      Serial.println("Standby position...");
      robot.standby();
      delay(500);
      
      Serial.println("Ready! Robot will move forward.");
  }

  void loop() {
      // Execute forward motion repeatedly
      robot.forward();
      delay(100);
  }

----

Achieved Effect
~~~~~~~~~~~~~~~~

- The spider robot will now continuously perform forward movement.

.. raw:: html

   <div style="margin-top: 30px;"></div>

.. image:: _static/course/4.com.png
   :width: 800
   :align: center

.. raw:: html

   <div style="margin-top: 30px;"></div>

- If the spider robot's forward movement is abnormal, ensure that the spider robot's initial installation position is as shown below, and click here to jump to the servo calibration page. :ref:`Servo calibration and debug`

- Since the code here only contains forward motion, the servo cannot be calibrated using the app; you only need to check the manual servo calibration section.

----