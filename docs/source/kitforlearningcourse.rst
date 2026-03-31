kit For Learning Course
======================

**In this section, we will use the components in this kit to expand our learning, gradually mastering the principles and functional characteristics of each component in order of depth, and completing the corresponding program writing.**

**The sixth code is the complete code for this kit "Quadruped Spider Robot," which you can click here to view.**

:ref:`Quadruped Spider Robot`

----

1. ESP8266 Basic GPIO Control
-----------------------------

Wiring diagram
~~~~~~~~~~~~~~

.. image:: _static/course/1.esp8266_basic.png
   :width: 800
   :align: center

.. raw:: html

   <div style="margin-top: 30px;"></div>

- LED —— ESP8266 D1 (GPIO5)

----

Example code
~~~~~~~~~~~~

.. code-block:: cpp

    // ESP8266 Basic GPIO Control - LED Blinking
    #define LED_PIN 5  // GPIO5 (D1)

    void setup() {
      pinMode(LED_PIN, OUTPUT);
      Serial.begin(115200);
      Serial.println("ESP8266 GPIO Control Test");
    }

    void loop() {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED ON");
      delay(1000);

      digitalWrite(LED_PIN, LOW);
      Serial.println("LED OFF");
      delay(1000);
    }

----

Achieved Effect
~~~~~~~~~~~~~~~~

 - The LED connected to GPIO5 blinks on and off every second, demonstrating basic digital output control.

----

2. Button Input and LED Control
-------------------------------

Wiring diagram
~~~~~~~~~~~~~~

.. image:: _static/course/2.button_led.png
   :width: 800
   :align: center

.. raw:: html

   <div style="margin-top: 30px;"></div>

- LED —— ESP8266 D1 (GPIO5)
- Button —— ESP8266 D2 (GPIO4)

----

Example code
~~~~~~~~~~~~

.. code-block:: cpp

    // Button Input and LED Control
    #define LED_PIN 5    // GPIO5 (D1)
    #define BUTTON_PIN 4 // GPIO4 (D2)

    void setup() {
      pinMode(LED_PIN, OUTPUT);
      pinMode(BUTTON_PIN, INPUT_PULLUP);
      Serial.begin(115200);
      Serial.println("Button and LED Control Test");
    }

    void loop() {
      if (digitalRead(BUTTON_PIN) == LOW) {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("Button pressed - LED ON");
      } else {
        digitalWrite(LED_PIN, LOW);
        Serial.println("Button released - LED OFF");
      }
      delay(100);
    }

----

Achieved Effect
~~~~~~~~~~~~~~~~

 - Press the button to turn on the LED, release to turn it off, demonstrating digital input reading and output control.

----

3. Servo Motor Control
----------------------

Wiring diagram
~~~~~~~~~~~~~~

.. image:: _static/course/3.servo_control.png
   :width: 800
   :align: center

.. raw:: html

   <div style="margin-top: 30px;"></div>

- Servo Signal —— ESP8266 D1 (GPIO5)
- Servo Power —— 5V
- Servo Ground —— GND

----

Example code
~~~~~~~~~~~~

.. code-block:: cpp

    // Servo Motor Control
    #include <Servo.h>

    #define SERVO_PIN 5  // GPIO5 (D1)
    Servo myServo;

    void setup() {
      myServo.attach(SERVO_PIN);
      Serial.begin(115200);
      Serial.println("Servo Control Test");
    }

    void loop() {
      // Sweep from 0 to 180 degrees
      for (int angle = 0; angle <= 180; angle += 10) {
        myServo.write(angle);
        Serial.print("Angle: ");
        Serial.println(angle);
        delay(500);
      }

      // Sweep back from 180 to 0 degrees
      for (int angle = 180; angle >= 0; angle -= 10) {
        myServo.write(angle);
        Serial.print("Angle: ");
        Serial.println(angle);
        delay(500);
      }
    }

----

Achieved Effect
~~~~~~~~~~~~~~~~

 - The servo motor sweeps from 0° to 180° and back, demonstrating PWM control for precise angular positioning.

----

4. Ultrasonic Distance Measurement
----------------------------------

Wiring diagram
~~~~~~~~~~~~~~

.. image:: _static/course/4.ultrasonic.png
   :width: 800
   :align: center

.. raw:: html

   <div style="margin-top: 30px;"></div>

- HC-SR04 VCC —— 5V
- HC-SR04 Trig —— ESP8266 D1 (GPIO5)
- HC-SR04 Echo —— ESP8266 D2 (GPIO4)
- HC-SR04 GND —— GND

----

Example code
~~~~~~~~~~~~

.. code-block:: cpp

    // Ultrasonic Distance Measurement
    #define TRIG_PIN 5  // GPIO5 (D1)
    #define ECHO_PIN 4  // GPIO4 (D2)

    void setup() {
      pinMode(TRIG_PIN, OUTPUT);
      pinMode(ECHO_PIN, INPUT);
      Serial.begin(115200);
      Serial.println("Ultrasonic Distance Sensor Test");
    }

    void loop() {
      // Send trigger pulse
      digitalWrite(TRIG_PIN, LOW);
      delayMicroseconds(2);
      digitalWrite(TRIG_PIN, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG_PIN, LOW);

      // Read echo pulse
      long duration = pulseIn(ECHO_PIN, HIGH);

      // Calculate distance
      float distance = duration * 0.034 / 2;

      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.println(" cm");

      delay(500);
    }

----

Achieved Effect
~~~~~~~~~~~~~~~~

 - The ultrasonic sensor measures distance and displays it in the serial monitor, demonstrating non-contact ranging.

----

5. Infrared Remote Control
--------------------------

Wiring diagram
~~~~~~~~~~~~~~

.. image:: _static/course/5.ir_receiver.png
   :width: 800
   :align: center

.. raw:: html

   <div style="margin-top: 30px;"></div>

- IR Receiver VCC —— 3.3V
- IR Receiver GND —— GND
- IR Receiver OUT —— ESP8266 D1 (GPIO5)

----

Example code
~~~~~~~~~~~~

.. code-block:: cpp

    // Infrared Remote Control
    #include <IRremoteESP8266.h>
    #include <IRrecv.h>
    #include <IRutils.h>

    #define IR_RECV_PIN 5  // GPIO5 (D1)
    IRrecv irrecv(IR_RECV_PIN);
    decode_results results;

    void setup() {
      Serial.begin(115200);
      irrecv.enableIRIn();
      Serial.println("IR Receiver Test");
    }

    void loop() {
      if (irrecv.decode(&results)) {
        Serial.print("IR Code: ");
        serialPrintUint64(results.value, HEX);
        Serial.println();

        irrecv.resume();
      }
      delay(100);
    }

----

Achieved Effect
~~~~~~~~~~~~~~~~

 - Point an IR remote at the receiver and press buttons; the hex codes are displayed in the serial monitor.

----

.. _Quadruped Spider Robot:

6. Quadruped Spider Robot Control
---------------------------------

Wiring diagram
~~~~~~~~~~~~~~

.. image:: _static/course/6.spider_robot.png
   :width: 800
   :align: center

.. raw:: html

   <div style="margin-top: 30px;"></div>

- Servo1 (Front Left Hip) —— ESP8266 D1 (GPIO5)
- Servo2 (Front Left Knee) —— ESP8266 D2 (GPIO4)
- Servo3 (Front Right Hip) —— ESP8266 D3 (GPIO0)
- Servo4 (Front Right Knee) —— ESP8266 D4 (GPIO2)
- Servo5 (Rear Left Hip) —— ESP8266 D5 (GPIO14)
- Servo6 (Rear Left Knee) —— ESP8266 D6 (GPIO12)
- Servo7 (Rear Right Hip) —— ESP8266 D7 (GPIO13)
- Servo8 (Rear Right Knee) —— ESP8266 D8 (GPIO15)
- HC-SR04 Trig —— ESP8266 D1 (shared with Servo1)
- HC-SR04 Echo —— ESP8266 D2 (shared with Servo2)
- IR Receiver OUT —— ESP8266 D3 (shared with Servo3)

----

Example code
~~~~~~~~~~~~

.. code-block:: cpp

    // Quadruped Spider Robot Control
    #include <Servo.h>
    #include <IRremoteESP8266.h>
    #include <IRrecv.h>
    #include <IRutils.h>

    // Servo pins
    #define SERVO_FL_HIP 5   // Front Left Hip
    #define SERVO_FL_KNEE 4  // Front Left Knee
    #define SERVO_FR_HIP 0   // Front Right Hip
    #define SERVO_FR_KNEE 2  // Front Right Knee
    #define SERVO_RL_HIP 14  // Rear Left Hip
    #define SERVO_RL_KNEE 12 // Rear Left Knee
    #define SERVO_RR_HIP 13  // Rear Right Hip
    #define SERVO_RR_KNEE 15 // Rear Right Knee

    // Sensor pins
    #define TRIG_PIN 5       // Shared with SERVO_FL_HIP
    #define ECHO_PIN 4       // Shared with SERVO_FL_KNEE
    #define IR_RECV_PIN 0    // Shared with SERVO_FR_HIP

    Servo servos[8];
    int servoPins[8] = {SERVO_FL_HIP, SERVO_FL_KNEE, SERVO_FR_HIP, SERVO_FR_KNEE,
                       SERVO_RL_HIP, SERVO_RL_KNEE, SERVO_RR_HIP, SERVO_RR_KNEE};

    // Default standing positions
    int standAngles[8] = {90, 90, 90, 90, 90, 90, 90, 90};

    IRrecv irrecv(IR_RECV_PIN);
    decode_results results;

    void setup() {
      Serial.begin(115200);

      // Attach servos
      for (int i = 0; i < 8; i++) {
        servos[i].attach(servoPins[i]);
        servos[i].write(standAngles[i]);
      }

      // Setup ultrasonic sensor
      pinMode(TRIG_PIN, OUTPUT);
      pinMode(ECHO_PIN, INPUT);

      // Setup IR receiver
      irrecv.enableIRIn();

      Serial.println("Quadruped Spider Robot Ready");
      delay(1000);
    }

    void loop() {
      // Check IR commands
      if (irrecv.decode(&results)) {
        handleIRCommand(results.value);
        irrecv.resume();
      }

      // Check distance for obstacle avoidance
      float distance = getDistance();
      if (distance < 20.0) {
        // Obstacle detected - stop and turn
        stopMovement();
        delay(500);
        turnRight();
      } else {
        // Normal walking
        walkForward();
      }

      delay(100);
    }

    void handleIRCommand(unsigned long code) {
      switch (code) {
        case 0xFF629D: // Forward
          walkForward();
          break;
        case 0xFFA857: // Backward
          walkBackward();
          break;
        case 0xFF22DD: // Left
          turnLeft();
          break;
        case 0xFFC23D: // Right
          turnRight();
          break;
        case 0xFF02FD: // Stop
          stopMovement();
          break;
      }
    }

    float getDistance() {
      digitalWrite(TRIG_PIN, LOW);
      delayMicroseconds(2);
      digitalWrite(TRIG_PIN, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG_PIN, LOW);

      long duration = pulseIn(ECHO_PIN, HIGH);
      return duration * 0.034 / 2;
    }

    void walkForward() {
      // Simplified walking sequence
      // Lift front left and rear right
      servos[0].write(60);  // FL Hip
      servos[1].write(60);  // FL Knee
      servos[6].write(120); // RR Hip
      servos[7].write(120); // RR Knee
      delay(200);

      // Move forward
      servos[0].write(120);
      servos[1].write(90);
      servos[6].write(60);
      servos[7].write(90);
      delay(200);

      // Lower
      servos[0].write(90);
      servos[1].write(90);
      servos[6].write(90);
      servos[7].write(90);
      delay(200);

      // Repeat for other legs
      // (Simplified - full walking would alternate all legs)
    }

    void walkBackward() {
      // Similar to forward but reversed
      // Implementation would mirror walkForward with opposite directions
    }

    void turnLeft() {
      // Turn left by rotating legs
      servos[0].write(60);  // FL Hip
      servos[2].write(120); // FR Hip
      servos[4].write(60);  // RL Hip
      servos[6].write(120); // RR Hip
      delay(300);
      resetToStand();
    }

    void turnRight() {
      // Turn right
      servos[0].write(120); // FL Hip
      servos[2].write(60);  // FR Hip
      servos[4].write(120); // RL Hip
      servos[6].write(60);  // RR Hip
      delay(300);
      resetToStand();
    }

    void stopMovement() {
      resetToStand();
    }

    void resetToStand() {
      for (int i = 0; i < 8; i++) {
        servos[i].write(standAngles[i]);
      }
    }

----

Achieved Effect
~~~~~~~~~~~~~~~~

:ref:`Quadruped Spider Robot User Guide`

----

Extended code
~~~~~~~~~~~~

 - You can modify the walking sequences to create different gaits (walk, trot, gallop).
 - Add more IR commands for different movements or speeds.
 - Implement autonomous navigation using the ultrasonic sensor for obstacle avoidance.
 - Add battery monitoring and low-power sleep modes.

.. note::

 - Ensure servos are properly calibrated and powered with adequate current.
 - Test each component individually before integrating into the full robot.
 - Use appropriate delays to prevent servo burnout and ensure smooth movement.

----

Example code
~~~~~~~~~~~~

.. code-block:: cpp

 #include <Adafruit_NeoPixel.h>

 // Pin definitions
 #define BUTTON_PIN 5      // Button to change notes
 #define SPEAKER_PIN 33    // Speaker positive pin (negative to GND)
 #define LED_PIN    15     // LED for visual feedback

 #define LED_COUNT 1

 Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

 // Musical notes frequencies (Hz) - C Major Scale
 const int notes[] = {
  262,  // C4 - Do
  294,  // D4 - Re
  330,  // E4 - Mi
  349,  // F4 - Fa
  392,  // G4 - Sol
  440,  // A4 - La
  494   // B4 - Si
 };

 const char* noteNames[] = {
  "Do (C4)",
  "Re (D4)", 
  "Mi (E4)",
  "Fa (F4)",
  "Sol (G4)",
  "La (A4)",
  "Si (B4)"
 };

 // Colors for each note
 uint32_t noteColors[] = {
  strip.Color(255, 0, 0),     // Do - Red
  strip.Color(255, 128, 0),   // Re - Orange
  strip.Color(255, 255, 0),   // Mi - Yellow
  strip.Color(0, 255, 0),     // Fa - Green
  strip.Color(0, 128, 255),   // Sol - Light Blue
  strip.Color(0, 0, 255),     // La - Blue
  strip.Color(128, 0, 255)    // Si - Purple
 };

 // Variables
 int currentNote = 0;          // Current note index (0-6)
 bool lastButtonState = HIGH;
 unsigned long lastPressTime = 0;

 // Speaker setup
 #define SPEAKER_CHANNEL 0

 void setup() {
  Serial.begin(115200);
  
  // Setup button
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  // Setup speaker with LEDC
  ledcSetup(SPEAKER_CHANNEL, 2000, 8);
  ledcAttachPin(SPEAKER_PIN, SPEAKER_CHANNEL);
  
  // Setup LED
  strip.begin();
  strip.show();
  strip.setBrightness(100);
  
  // Show current note
  updateDisplay();
  
  Serial.println("Tone Generator with Speaker");
  Serial.println("Short press: Change to next note");
  Serial.println("----------------------");
 }

 void loop() {
  bool buttonState = digitalRead(BUTTON_PIN);
  
  // Button pressed (detect falling edge)
  if (buttonState == LOW && lastButtonState == HIGH) {
    // Simple debounce
    delay(50);
    
    if (digitalRead(BUTTON_PIN) == LOW) {
      // Change to next note
      changeNote();
      
      // Play the new note briefly
      playNoteBriefly();
    }
  }
  
  lastButtonState = buttonState;
  delay(10);
 }

 void changeNote() {
  // Move to next note
  currentNote = (currentNote + 1) % 7;
  
  updateDisplay();
  
  // Visual feedback
  for (int i = 0; i < 2; i++) {
    strip.setPixelColor(0, strip.Color(255, 255, 255));
    strip.show();
    delay(50);
    strip.setPixelColor(0, noteColors[currentNote]);
    strip.show();
    delay(50);
  }
 }

 void playNoteBriefly() {
  Serial.print("Playing: ");
  Serial.print(noteNames[currentNote]);
  Serial.print(" (");
  Serial.print(notes[currentNote]);
  Serial.println(" Hz)");
  
  // Play note on speaker
  ledcWriteTone(SPEAKER_CHANNEL, notes[currentNote]);
  
  // Visual feedback - bright LED
  strip.setPixelColor(0, noteColors[currentNote]);
  strip.setBrightness(200);
  strip.show();
  
  // Play for 300ms
  delay(300);
  
  // Stop speaker
  ledcWriteTone(SPEAKER_CHANNEL, 0);
  
  // Dim LED back
  strip.setBrightness(100);
  strip.show();
 }

 void updateDisplay() {
  Serial.println("----------------------");
  Serial.print("Current note: ");
  Serial.println(noteNames[currentNote]);
  Serial.print("Frequency: ");
  Serial.print(notes[currentNote]);
  Serial.println(" Hz");
  Serial.println("----------------------");
  
  // Update LED color
  strip.setPixelColor(0, noteColors[currentNote]);
  strip.setBrightness(100);
  strip.show();
 }
----

Achieved Effect
~~~~~~~~~~~~~~~~

 - Press the button, and the speaker will play the Do-Si syllables in sequence and light up different colored lights.

----

5. Triple Bond Piano
--------------------

Wiring diagram
~~~~~~~~~~~~~~

.. image:: _static/course/5.course.png
   :width: 800
   :align: center

.. raw:: html

   <div style="margin-top: 30px;"></div>

- RGB —— ESP32 IO15
- Button1 —— ESP32 IO5
- Button2 —— ESP32 IO18
- Button3 —— ESP32 IO5
- Speaker —— ESP32 IO33

----

Example code
~~~~~~~~~~~~

.. code-block:: cpp

 #include <Adafruit_NeoPixel.h>

 #define BTN1 5   // Do
 #define BTN2 18   // Mi  
 #define BTN3 19   // Sol
 #define SPEAKER 33
 #define LED_PIN 15

 Adafruit_NeoPixel leds(3, LED_PIN, NEO_GRB + NEO_KHZ800);

 // Notes for C major scale
 int notes[] = {262, 294, 330, 349, 392, 440, 494};
 // Our buttons: Do(0), Mi(2), Sol(4)
 int buttonNotes[] = {0, 2, 4};  // Indexes in notes array

 // Chord definitions
 #define CHORD_C_MAJOR 0     // Do + Mi + Sol
 #define CHORD_F_MAJOR 1     // Fa + La + Do
 #define CHORD_G_MAJOR 2     // Sol + Si + Re

 int currentChord = -1;      // -1 = no chord
 bool buttons[3] = {false, false, false};
 unsigned long buttonTime[3] = {0, 0, 0};

 void setup() {
  Serial.begin(115200);
  
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  pinMode(BTN3, INPUT_PULLUP);
  
  ledcSetup(0, 2000, 8);
  ledcAttachPin(SPEAKER, 0);
  
  leds.begin();
  leds.setBrightness(100);
  
  Serial.println("Chord Piano - Three Keys");
  Serial.println("Do+Mi = Interval");
  Serial.println("Do+Mi+Sol = C Major Chord");
  Serial.println("Mi+Sol = Another interval");
 }

 void loop() {
  // Read buttons with debounce
  readButton(0, BTN1);
  readButton(1, BTN2);
  readButton(2, BTN3);
  
  // Check what's being pressed
  int pressedCount = 0;
  for (int i = 0; i < 3; i++) {
    if (buttons[i]) pressedCount++;
  }
  
  // Play appropriate sound
  if (pressedCount == 0) {
    ledcWriteTone(0, 0);  // Stop sound
    currentChord = -1;
  }
  else if (pressedCount == 1) {
    // Single note
    for (int i = 0; i < 3; i++) {
      if (buttons[i]) {
        playSingleNote(i);
        break;
      }
    }
    currentChord = -1;
  }
  else {
    // Multiple buttons - check for chords
    checkChord();
  }
  
  // Update LEDs
  updateLEDs();
  
  delay(10);
 }  

 void readButton(int index, int pin) {
  bool state = digitalRead(pin);
  
  if (state == LOW && !buttons[index]) {
    // Button just pressed
    if (millis() - buttonTime[index] > 50) {  // Debounce
      buttons[index] = true;
      buttonTime[index] = millis();
      Serial.print("Button ");
      Serial.print(index + 1);
      Serial.println(" pressed");
    }
  }
  else if (state == HIGH && buttons[index]) {
    // Button just released
    buttons[index] = false;
    Serial.print("Button ");
    Serial.print(index + 1);
    Serial.println(" released");
  }
 }

 void playSingleNote(int buttonIndex) {
  int noteIndex = buttonNotes[buttonIndex];
  ledcWriteTone(0, notes[noteIndex]);
  
  // LED feedback
  for (int i = 0; i < 3; i++) {
    if (i == buttonIndex) {
      setLEDColor(i, true);
    } else {
      setLEDColor(i, false);
    }
  }
 }

 void checkChord() {
  // Check which buttons are pressed
  bool doPressed = buttons[0];  // Button 1
  bool miPressed = buttons[1];  // Button 2
  bool solPressed = buttons[2]; // Button 3
  
  // Check for C Major chord (Do + Mi + Sol)
  if (doPressed && miPressed && solPressed) {
    if (currentChord != CHORD_C_MAJOR) {
      currentChord = CHORD_C_MAJOR;
      Serial.println("C Major Chord!");
      playChord(CHORD_C_MAJOR);
    }
  }
  // Check for Do+Mi interval
  else if (doPressed && miPressed) {
    if (currentChord != 10) {  // Custom code for this interval
      currentChord = 10;
      Serial.println("Do-Mi Interval");
      // Play alternating between Do and Mi
      static bool alt = false;
      if (alt) {
        ledcWriteTone(0, notes[0]);  // Do
      } else {
        ledcWriteTone(0, notes[2]);  // Mi
      }
      alt = !alt;
    }
  }
  // Check for Mi+Sol interval
  else if (miPressed && solPressed) {
    if (currentChord != 11) {
      currentChord = 11;
      Serial.println("Mi-Sol Interval");
      // Play alternating
      static bool alt = false;
      if (alt) {
        ledcWriteTone(0, notes[2]);  // Mi
      } else {
        ledcWriteTone(0, notes[4]);  // Sol
      }
      alt = !alt;
    }
  }
  // Check for Do+Sol interval
  else if (doPressed && solPressed) {
    if (currentChord != 12) {
      currentChord = 12;
      Serial.println("Do-Sol Interval (Perfect 5th)");
      ledcWriteTone(0, notes[0]);  // Play Do (root)
    }
  }
 }

 void playChord(int chordType) {
  switch(chordType) {
    case CHORD_C_MAJOR:
      // Play C Major chord (Do, Mi, Sol)
      // We'll play the root note, but could also cycle through chord notes
      ledcWriteTone(0, notes[0]);  // Do
      
      // Chord animation on LEDs
      static unsigned long lastBlink = 0;
      if (millis() - lastBlink > 200) {
        lastBlink = millis();
        for (int i = 0; i < 3; i++) {
          leds.setPixelColor(i, 
            buttons[i] ? leds.Color(255, 255, 255) : leds.Color(0, 0, 0));
        }
        leds.show();
        delay(50);
        updateLEDs();
      }
      break;
  }
 }

 void setLEDColor(int index, bool pressed) {
  int colors[][3] = {{255,0,0}, {0,255,0}, {0,0,255}};
  
  if (pressed) {
    leds.setPixelColor(index, colors[index][0], colors[index][1], colors[index][2]);
  } else {
    leds.setPixelColor(index, 
      colors[index][0]/5, colors[index][1]/5, colors[index][2]/5);
  }
 }

 void updateLEDs() {
  for (int i = 0; i < 3; i++) {
    setLEDColor(i, buttons[i]);
  }
  leds.show();
 }

----

Achieved Effect
~~~~~~~~~~~~~~~~

 - The three buttons represent Do, Mi, and Sol, allowing you to use your imagination to play some simple music.

----

.. _ESP32 DIY Electronic Piano:

6. ESP32 DIY Electronic Piano
-----------------------------

Wiring diagram
~~~~~~~~~~~~~~

.. image:: _static/2.WIRING.png
   :width: 800
   :align: center

- RGB —— ESP32 IO15
- Button1 —— ESP32 IO5
- Button2 —— ESP32 IO18
- Button3 —— ESP32 IO19
- Button4 —— ESP32 IO23
- Button5 —— ESP32 IO32
- Button6 —— ESP32 IO33
- Button7 —— ESP32 IO12
- Button8 —— ESP32 IO4
- Speaker —— ESP32 IO13

----

Example code
~~~~~~~~~~~~

.. code-block:: cpp

  #include <FastLED.h>
  #include <WiFi.h>
  #include <WebServer.h>
  
  const char* ssid = "ESP32_Piano";
  const char* password = "12345678";
  
  WebServer server(80);
  
  #define BUZZER_PIN     13
  #define BUZZER_CHANNEL 0
  #define AUTO_KEY_PIN   4
  
  #define LED_PIN   15
  #define NUM_LEDS  8
  CRGB leds[NUM_LEDS];
  
  int keyPins[7] = {5, 18, 19, 23, 32, 33, 12};
  int noteFreq[7] = {262, 294, 330, 349, 392, 440, 494};
  
  uint8_t keyColors[7] = {0, 32, 64, 96, 128, 160, 192};
  
  #define C4 262
  #define D4 294
  #define E4 330
  #define F4 349
  #define G4 392
  #define A4 440
  #define B4 494
  #define C5 523
  #define D5 587
  
  int song1[] = {
    C4,C4,G4,G4,A4,A4,G4,
    F4,F4,E4,E4,D4,D4,C4,
    G4,G4,F4,F4,E4,E4,D4,
    G4,G4,F4,F4,E4,E4,D4,
    C4,C4,G4,G4,A4,A4,G4,
    F4,F4,E4,E4,D4,D4,C4
  };
  
  int rhythm1[] = {
    1,1,1,1,1,1,2,
    1,1,1,1,1,1,2,
    1,1,1,1,1,1,2,
    1,1,1,1,1,1,2,
    1,1,1,1,1,1,2,
    1,1,1,1,1,1,2
  };
  
  int song2[] = {
    E4,E4,E4,  E4,E4,E4,
    E4,G4,C4,D4,E4,
    F4,F4,F4,F4,
    F4,E4,E4,E4,
    E4,D4,D4,E4,
    D4,G4,
  
    E4,E4,E4,  E4,E4,E4,
    E4,G4,C4,D4,E4,
    F4,F4,F4,F4,
    F4,E4,E4,E4,
    G4,G4,F4,D4,C4
  };
  
  int rhythm2[] = {
    1,1,2, 1,1,2,
    1,1,1,1,2,
    1,1,1,1,
    1,1,1,1,
    1,1,1,1,
    2,2,
  
    1,1,2, 1,1,2,
    1,1,1,1,2,
    1,1,1,1,
    1,1,1,1,
    2,2,2,2,4
  };
  
  int song3[] = {
    C4,C4,D4,C4,F4,E4,
    C4,C4,D4,C4,G4,F4,
    C4,C4,C5,A4,F4,E4,D4,
    B4,B4,A4,F4,G4,F4
  };
  
  int rhythm3[] = {
    1,2,1,4,4,6,
    1,2,1,4,4,6,
    1,2,4,4,4,4,6,
    1,2,4,4,6,8
  };
  
  int* songs[]   = {song1, song2, song3};
  int* rhythms[] = {rhythm1, rhythm2, rhythm3};
  int songLen[] = {
    sizeof(song1)/sizeof(int),
    sizeof(song2)/sizeof(int),
    sizeof(song3)/sizeof(int)
  };
  
  int songIndex = -1;
  bool autoPlay = false;
  uint8_t timeHue = 0;
  
  #define BPM 120
  #define NOTE_TIME (60000 / BPM / 2)
  
  bool manualNotePlaying = false;
  unsigned long manualNoteOffTime = 0;
  
  bool webControlActive = false;
  int lastWebKey = -1;
  unsigned long lastWebKeyTime = 0;
  #define WEB_KEY_TIMEOUT 100
  
  void lightKeyLED(int keyIndex) {
    FastLED.clear();
  
    leds[keyIndex] = CHSV(keyColors[keyIndex], 255, 255);
  
    if (keyIndex > 0) {
      leds[keyIndex - 1] = CHSV(keyColors[keyIndex] + 20, 200, 100);
    }
    if (keyIndex < NUM_LEDS - 1) {
      leds[keyIndex + 1] = CHSV(keyColors[keyIndex] - 20, 200, 100);
    }
  
    FastLED.show();
  }
  
  uint8_t freqToHue(int freq) {
    freq = constrain(freq, 262, 587);
    return map(freq, 262, 587, 180, 0);
  }
  
  void colorBurst(uint8_t baseHue, uint8_t brightness) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(baseHue + i * 18 + timeHue, 255, brightness);
    }
    timeHue += 6;
    FastLED.show();
  }
  
  void rainbowChase(uint8_t baseHue, int step) {
    fadeToBlackBy(leds, NUM_LEDS, 60);
    leds[step % NUM_LEDS] = CHSV(baseHue + timeHue, 255, 255);
    timeHue += 10;
    FastLED.show();
  }
  
  void rainbowBreath(uint8_t baseHue, uint8_t brightness) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(baseHue + i * 12 + timeHue, 200, brightness);
    }
    timeHue += 3;
    FastLED.show();
  }
  
  void playNote(int noteIndex, bool fromWeb = false) {
    if (noteIndex >= 0 && noteIndex < 7) {
      ledcWriteTone(BUZZER_CHANNEL, noteFreq[noteIndex]);
      lightKeyLED(noteIndex);
      manualNoteOffTime = millis() + NOTE_TIME;
      manualNotePlaying = true;
      
      if (fromWeb) {
        webControlActive = true;
        lastWebKey = noteIndex;
        lastWebKeyTime = millis();
      }
    }
  }
  
  void startAutoPlay() {
    autoPlay = true;
    songIndex = (songIndex + 1) % 3;
    webControlActive = true;
  }
  
  const char* htmlContent = R"rawliteral(
  <!DOCTYPE html>
  <html lang="en">
  <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>ESP32 Piano</title>
      <style>
          * {
              margin: 0;
              padding: 0;
              box-sizing: border-box;
          }
          
          body {
              background: #000;
              height: 100vh;
              display: flex;
              justify-content: center;
              align-items: center;
              font-family: Arial, sans-serif;
          }
          
          .piano-keys {
              display: flex;
              width: 95%;
              height: 70vh;
              gap: 10px;
              padding: 10px;
          }
          
          .piano-key {
              flex: 1;
              display: flex;
              flex-direction: column;
              justify-content: center;
              align-items: center;
              border-radius: 15px;
              cursor: pointer;
              user-select: none;
              transition: transform 0.1s;
              font-weight: bold;
              font-size: 2.5em;
              box-shadow: 0 5px 15px rgba(0,0,0,0.3);
          }
          
          .key-1, .key-3, .key-5, .key-7 {
              background: white;
              color: black;
          }
          
          .key-2, .key-4, .key-6 {
              background: black;
              color: white;
              border: 2px solid #333;
          }
          
          .key-auto {
              background: linear-gradient(45deg, #ff3366, #33ccff);
              color: white;
          }
          
          .piano-key:active {
              transform: scale(0.95);
          }
          
          .key-number {
              font-size: 1.2em;
              margin-bottom: 5px;
          }
          
          .key-text {
              font-size: 0.6em;
          }
      </style>
  </head>
  <body>
      <div class="piano-keys">
          <div class="piano-key key-1" data-key="0">
              <div class="key-number">1</div>
              <div class="key-text">Do</div>
          </div>
          <div class="piano-key key-2" data-key="1">
              <div class="key-number">2</div>
              <div class="key-text">Re</div>
          </div>
          <div class="piano-key key-3" data-key="2">
              <div class="key-number">3</div>
              <div class="key-text">Mi</div>
          </div>
          <div class="piano-key key-4" data-key="3">
              <div class="key-number">4</div>
              <div class="key-text">Fa</div>
          </div>
          <div class="piano-key key-5" data-key="4">
              <div class="key-number">5</div>
              <div class="key-text">Sol</div>
          </div>
          <div class="piano-key key-6" data-key="5">
              <div class="key-number">6</div>
              <div class="key-text">La</div>
          </div>
          <div class="piano-key key-7" data-key="6">
              <div class="key-number">7</div>
              <div class="key-text">Si</div>
          </div>
          <div class="piano-key key-auto" data-key="auto">
              <div class="key-number">AUTO</div>
          </div>
      </div>
  
      <script>
          document.querySelectorAll('.piano-key').forEach(key => {
              key.addEventListener('mousedown', function() {
                  const keyData = this.dataset.key;
                  
                  if (keyData === 'auto') {
                      fetch('/auto');
                  } else {
                      fetch(`/play?key=${keyData}`);
                  }
                  
                  this.style.transform = 'scale(0.95)';
              });
              
              key.addEventListener('mouseup', function() {
                  this.style.transform = '';
              });
              
              key.addEventListener('mouseleave', function() {
                  this.style.transform = '';
              });
              
              key.addEventListener('touchstart', function(e) {
                  e.preventDefault();
                  const keyData = this.dataset.key;
                  
                  if (keyData === 'auto') {
                      fetch('/auto');
                  } else {
                      fetch(`/play?key=${keyData}`);
                  }
                  
                  this.style.transform = 'scale(0.95)';
              });
              
              key.addEventListener('touchend', function() {
                  this.style.transform = '';
              });
          });
          
          document.addEventListener('keydown', function(e) {
              if (e.key >= '1' && e.key <= '7') {
                  const keyIndex = parseInt(e.key) - 1;
                  const keyElement = document.querySelector(`[data-key="${keyIndex}"]`);
                  if (keyElement) {
                      keyElement.style.transform = 'scale(0.95)';
                      fetch(`/play?key=${keyIndex}`);
                  }
              }
              
              if (e.key === 'a' || e.key === 'A') {
                  const autoKey = document.querySelector('[data-key="auto"]');
                  if (autoKey) {
                      autoKey.style.transform = 'scale(0.95)';
                      fetch('/auto');
                  }
              }
          });
          
          document.addEventListener('keyup', function(e) {
              if (e.key >= '1' && e.key <= '7') {
                  const keyIndex = parseInt(e.key) - 1;
                  const keyElement = document.querySelector(`[data-key="${keyIndex}"]`);
                  if (keyElement) {
                      keyElement.style.transform = '';
                  }
              }
              
              if (e.key === 'a' || e.key === 'A') {
                  const autoKey = document.querySelector('[data-key="auto"]');
                  if (autoKey) {
                      autoKey.style.transform = '';
                  }
              }
          });
      </script>
  </body>
  </html>
  )rawliteral";
  
  void handleRoot() {
    server.send(200, "text/html", htmlContent);
  }
  
  void handlePlay() {
    if (server.hasArg("key")) {
      int keyIndex = server.arg("key").toInt();
      if (keyIndex >= 0 && keyIndex < 7) {
        playNote(keyIndex, true);
        server.send(200, "text/plain", "OK");
      }
    }
  }
  
  void handleAuto() {
    startAutoPlay();
    server.send(200, "text/plain", "OK");
  }
  
  void setup() {
    Serial.begin(115200);
    
    for (int i = 0; i < 7; i++) pinMode(keyPins[i], INPUT_PULLUP);
    pinMode(AUTO_KEY_PIN, INPUT_PULLUP);
  
    ledcSetup(BUZZER_CHANNEL, 2000, 8);
    ledcAttachPin(BUZZER_PIN, BUZZER_CHANNEL);
  
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(200);
    FastLED.clear();
    FastLED.show();
  
    WiFi.softAP(ssid, password);
    Serial.println("AP Started");
    Serial.print("SSID: ");
    Serial.println(ssid);
    Serial.print("IP: ");
    Serial.println(WiFi.softAPIP());
  
    server.on("/", handleRoot);
    server.on("/play", handlePlay);
    server.on("/auto", handleAuto);
    
    server.begin();
    Serial.println("Web Server Started");
  }
  
  void loop() {
    server.handleClient();
    
    if (webControlActive && (millis() - lastWebKeyTime > WEB_KEY_TIMEOUT)) {
      if (millis() > manualNoteOffTime) {
        webControlActive = false;
      }
    }
  
    if (autoPlay && songIndex >= 0 && songIndex < 3) {
      static int noteIndex = 0;
      static unsigned long nextNoteTime = 0;
      
      if (millis() >= nextNoteTime) {
        if (noteIndex < songLen[songIndex]) {
          int freq = songs[songIndex][noteIndex];
          ledcWriteTone(BUZZER_CHANNEL, freq);
          
          uint8_t hue = freqToHue(freq);
          if (songIndex == 0) colorBurst(hue, 255);
          else if (songIndex == 1) rainbowChase(hue, noteIndex);
          else rainbowBreath(hue, 200);
          
          int delayTime = 220 * rhythms[songIndex][noteIndex];
          nextNoteTime = millis() + delayTime;
          noteIndex++;
        } else {
          noteIndex = 0;
          autoPlay = false;
          webControlActive = false;
          ledcWriteTone(BUZZER_CHANNEL, 0);
        }
      }
    }
    
    if (!webControlActive && !autoPlay) {
      if (manualNotePlaying && millis() > manualNoteOffTime) {
        ledcWriteTone(BUZZER_CHANNEL, 0);
        manualNotePlaying = false;
      }
      
      if (!manualNotePlaying) {
        for (int i = 0; i < 7; i++) {
          if (digitalRead(keyPins[i]) == LOW) {
            playNote(i, false);
            break;
          }
        }
      }
      
      if (digitalRead(AUTO_KEY_PIN) == LOW) {
        delay(20);
        if (digitalRead(AUTO_KEY_PIN) == LOW) {
          startAutoPlay();
          while (digitalRead(AUTO_KEY_PIN) == LOW);
        }
      }
    }
    
    if (!manualNotePlaying && !autoPlay) {
      fadeToBlackBy(leds, NUM_LEDS, 30);
      FastLED.show();
    }
    
    delay(5);
  }

----

Achieved Effect
~~~~~~~~~~~~~~~~

:ref:`Electronic Piano User Guide`

----

Extended code
~~~~~~~~~~~~

 - You can modify the code in the three autoplay tracks to change them to your preferred music.

 - For example, if you want to modify the first song, you only need to modify the two code snippets shown in the image to match the rhythm of the corresponding song.

.. image:: _static/course/4.course.png
   :width: 800
   :align: center

.. raw:: html

   <div style="margin-top: 30px;"></div>

- For example, to change the first song to "Ode to Joy", simply modify the original code as follows.

.. raw:: html

   <div style="margin-top: 30px;"></div>

.. code-block:: cpp

  int song1[] = {
  E4,E4,F4,G4,G4,F4,E4,D4,
  C4,C4,D4,E4,E4,D4,D4,
  E4,E4,F4,G4,G4,F4,E4,D4,
  C4,C4,D4,E4,D4,C4,C4
 };

----

.. code-block:: cpp

  int rhythm1[] = {
  2,2,2,2,2,2,2,2,
  2,2,2,2,3,1,2,
  2,2,2,2,2,2,2,2,
  2,2,2,2,2,2,4
 };

----

.. note::

 - The number of notes must match the number of rhythms; otherwise, playback will fail.

 - Predefined pitch constants can be used: C4, D4, E4, F4, G4, A4, B4, C5, D5.

 - You can use your imagination to combine any tone to create your own music.

----