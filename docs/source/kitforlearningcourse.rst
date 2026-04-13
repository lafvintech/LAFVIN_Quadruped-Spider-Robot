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

.. image:: _static/course/1.servo.gif
   :width: 800
   :align: center

.. raw:: html

   <div style="margin-top: 30px;"></div>

----

