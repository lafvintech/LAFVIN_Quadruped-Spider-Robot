/*
 * emotiv_spider.ino  —  LAFVIN Quadruped Spider Robot
 * ----------------------------------------------------
 * Wi-Fi (station mode) control for the ESP8266, two ways at once:
 *
 *   1. A built-in web control panel. Connect your PHONE to the same Wi-Fi and
 *      open the ESP8266's IP address in a browser — buttons drive the spider,
 *      no computer required.
 *
 *   2. A UDP command listener (port 4210). The PC program
 *      bridge/emotiv_bridge.py forwards Emotiv EPOC X mental commands here.
 *
 * Both inputs set the same command; the spider keeps doing it until told
 * otherwise:
 *
 *     'F' -> walk forward       'B' -> walk backward
 *     'L' -> turn left          'R' -> turn right
 *     'S' -> stop (standby)
 *
 * Motion engine (SERVO_PINS, ranges, Servo_Zero, the Servo_Forward matrix,
 * init()/zero()/standby()/forward()) is reused unchanged from Course 3 of the
 * LAFVIN documentation. The backward() and turn() gaits are added here.
 *
 * Board:   ESP8266 (spider expansion board)
 * Libs:    ESP8266WiFi, ESP8266WebServer, WiFiUdp, Servo  (all bundled with
 *          the ESP8266 core)
 *
 * >>> Set your Wi-Fi SSID / PASSWORD below, flash, then open the Serial
 *     Monitor @115200 to read the IP address the board was given.
 *       - Type that IP into your phone's browser to use the control panel.
 *       - Put that IP into bridge/config.py (ESP8266_IP) for mental commands.
 *     The phone, the PC and the ESP8266 must all be on the SAME Wi-Fi network.
 */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <Servo.h>
#include <Arduino.h>

// ======================= Wi-Fi / network configuration =======================
const char* WIFI_SSID     = "YOUR_WIFI_SSID";       // <-- change me
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";   // <-- change me

const unsigned int LOCAL_UDP_PORT = 4210;           // must match UDP_PORT in config.py

WiFiUDP Udp;
char incomingPacket[8];                             // we only need the first byte

ESP8266WebServer server(80);                        // phone control panel

// ============================ Servo / motion setup ===========================
// (reused verbatim from Course 3)
const int SERVO_PINS[] = {14, 12, 13, 15, 16, 5, 4, 2};  // G14, G12, G13, G15, G16, G5, G4, G2
const int ALLSERVOS = 8;
const int ALLMATRIX = 9;   // 8 servo angles + trailing delay (ms)

// Servo pulse range (microseconds) and valid angle range
const int SERVOMIN = 400;
const int SERVOMAX = 2400;
const int ANGLE_MIN = 1;
const int ANGLE_MAX = 180;

// Servo zero position (8 angles + settle time)
const int Servo_Zero[] = { 135, 45, 135, 45, 45, 135, 45, 135, 500 };

// Forward motion sequence (11 steps x [8 angles + ms])
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

// ------------------------------- Turn tuning ---------------------------------
// The turn gaits below are DERIVED from the forward gait: we damp the stride of
// the legs on one side so the body curves toward that side. The exact left/right
// leg grouping depends on how YOUR robot is assembled. These are STARTER VALUES
// — expect to fine-tune them on real hardware (use the phone control panel, and
// the servo-calibration page in the LAFVIN docs).
//
// If "turn left" makes the robot turn right (or vice-versa), swap the two
// index lists below. If turns are too weak/strong, change TURN_DAMP
// (0.0 = spins hard in place, 1.0 = walks straight, no turn).
const int  LEFT_H_SERVOS[]  = {0, 2};   // horizontal servos of the left-side legs
const int  RIGHT_H_SERVOS[] = {4, 6};   // horizontal servos of the right-side legs
const int  LEFT_H_COUNT     = 2;
const int  RIGHT_H_COUNT    = 2;
const float TURN_DAMP       = 0.35;     // fraction of stride kept on the damped side

// Neutral (standby) horizontal-servo angles, used as the anchor when damping.
// These are the horizontal columns of Servo_Forward row 0.
const int Neutral_H[ALLSERVOS] = { 70, 90, 90, 110, 110, 90, 90, 70 };

// Current active command; 'S' (stop/standby) at power-up. Set by both the web
// panel and the UDP listener.
char currentCmd = 'S';

// Forward declaration: process web + UDP input (may update currentCmd).
void service();

// ============================== Web control panel ============================
// A self-contained dark-themed D-pad served straight from the ESP8266.
const char CONTROL_PANEL_HTML[] PROGMEM = R"HTML(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Spider Control</title>
<style>
  *{margin:0;padding:0;box-sizing:border-box;}
  body{font-family:-apple-system,BlinkMacSystemFont,'Segoe UI',sans-serif;
       background:#0f1115;color:#e8e8e8;min-height:100vh;display:flex;
       flex-direction:column;justify-content:center;align-items:center;padding:20px;}
  h1{font-weight:500;font-size:22px;margin-bottom:6px;}
  .sub{color:#8a8f98;font-size:13px;margin-bottom:28px;text-align:center;}
  .pad{display:grid;grid-template-columns:repeat(3,90px);grid-template-rows:repeat(3,90px);gap:12px;}
  button{font-size:15px;font-weight:600;color:#e8e8e8;background:#1c2230;
         border:1px solid #2c3444;border-radius:16px;cursor:pointer;
         transition:transform .05s,background .15s;user-select:none;-webkit-tap-highlight-color:transparent;}
  button:active{transform:scale(.94);background:#3a4670;}
  .fwd{grid-column:2;grid-row:1;}
  .left{grid-column:1;grid-row:2;}
  .stop{grid-column:2;grid-row:2;background:#4a1f24;border-color:#6b2b32;}
  .right{grid-column:3;grid-row:2;}
  .back{grid-column:2;grid-row:3;}
  .status{margin-top:26px;font-size:13px;color:#8a8f98;}
  .status b{color:#7dd3fc;font-size:15px;}
</style>
</head>
<body>
  <h1>&#128375;&#65039; Spider Control</h1>
  <div class="sub">Phone buttons and mental commands share the same robot.</div>
  <div class="pad">
    <button class="fwd"   onclick="cmd('F')">&#9650;<br>Forward</button>
    <button class="left"  onclick="cmd('L')">&#9664;<br>Left</button>
    <button class="stop"  onclick="cmd('S')">&#9632;<br>Stop</button>
    <button class="right" onclick="cmd('R')">&#9654;<br>Right</button>
    <button class="back"  onclick="cmd('B')">&#9660;<br>Back</button>
  </div>
  <div class="status">Last command: <b id="last">-</b></div>
<script>
function cmd(c){
  fetch('/cmd?c='+c).then(r=>r.text()).then(()=>{
    document.getElementById('last').innerText=c;
  }).catch(e=>console.error(e));
}
</script>
</body>
</html>
)HTML";

void handleRoot() {
    server.send_P(200, "text/html", CONTROL_PANEL_HTML);
}

void handleCmd() {
    String c = server.arg("c");
    if (c.length() > 0) {
        char ch = c.charAt(0);
        if (ch == 'F' || ch == 'B' || ch == 'L' || ch == 'R' || ch == 'S') {
            if (ch != currentCmd) {
                currentCmd = ch;
                Serial.printf("Web command: %c\n", ch);
            }
            server.send(200, "text/plain", "ok");
            return;
        }
    }
    server.send(400, "text/plain", "invalid");
}

// =============================================================================
class SpiderBotMotion {
public:
    Servo servos[ALLSERVOS];

    // Attach all 8 servos
    void init() {
        for (int i = 0; i < ALLSERVOS; i++) {
            servos[i].attach(SERVO_PINS[i], SERVOMIN, SERVOMAX);
        }
        delay(200);
    }

    // Write one row of angles (indices 0..7) then wait `ms`, servicing input.
    void writeFrame(const int angles[ALLSERVOS], int ms) {
        for (int i = 0; i < ALLSERVOS; i++) {
            int angle = constrain(angles[i], ANGLE_MIN, ANGLE_MAX);
            servos[i].write(angle);
        }
        // Keep the web server responsive during the step delay.
        unsigned long end = millis() + ms;
        while ((long)(end - millis()) > 0) {
            service();
            delay(5);
        }
    }

    // Move all servos to the zero position
    void zero() {
        for (int i = 0; i < ALLSERVOS; i++) {
            int angle = constrain(Servo_Zero[i], ANGLE_MIN, ANGLE_MAX);
            servos[i].write(angle);
        }
        delay(Servo_Zero[8]);
    }

    // Standby pose (legs down, ready)
    void standby() {
        int standby_angles[ALLSERVOS] = {60, 90, 90, 120, 120, 90, 90, 60};
        writeFrame(standby_angles, 500);
    }

    // ---- Forward: one full gait cycle, abortable between steps -------------
    void forward() {
        for (int step = 0; step < Servo_Forward_Step; step++) {
            writeFrame(Servo_Forward[step], Servo_Forward[step][8]);
            if (currentCmd != 'F') return;         // command changed mid-cycle
        }
    }

    // ---- Backward: the forward keyframes walked in reverse order ----------
    void backward() {
        for (int step = Servo_Forward_Step - 1; step >= 0; step--) {
            writeFrame(Servo_Forward[step], Servo_Forward[step][8]);
            if (currentCmd != 'B') return;
        }
    }

    // ---- Turn: forward gait with one side's stride damped ------------------
    // left == true  -> damp the LEFT legs  -> body curves/pivots left
    // left == false -> damp the RIGHT legs -> body curves/pivots right
    void turn(bool left) {
        const int* damp  = left ? LEFT_H_SERVOS : RIGHT_H_SERVOS;
        int        dampN = left ? LEFT_H_COUNT  : RIGHT_H_COUNT;
        char       want  = left ? 'L' : 'R';

        for (int step = 0; step < Servo_Forward_Step; step++) {
            int frame[ALLSERVOS];
            for (int i = 0; i < ALLSERVOS; i++) frame[i] = Servo_Forward[step][i];

            // Pull the damped side's horizontal servos back toward neutral so
            // those legs take a shorter stride -> the robot turns.
            for (int k = 0; k < dampN; k++) {
                int idx = damp[k];
                int raw = Servo_Forward[step][idx];
                frame[idx] = Neutral_H[idx] + (int)((raw - Neutral_H[idx]) * TURN_DAMP);
            }

            writeFrame(frame, Servo_Forward[step][8]);
            if (currentCmd != want) return;
        }
    }
};

SpiderBotMotion robot;

// =============================================================================
// Process both input paths. May update the global currentCmd.
void service() {
    // 1) Web control panel (phone)
    server.handleClient();

    // 2) UDP command (PC / Emotiv)
    int packetSize = Udp.parsePacket();
    if (packetSize) {
        int len = Udp.read(incomingPacket, sizeof(incomingPacket) - 1);
        if (len > 0) {
            incomingPacket[len] = 0;
            char c = incomingPacket[0];
            if (c == 'F' || c == 'B' || c == 'L' || c == 'R' || c == 'S') {
                if (c != currentCmd) {
                    currentCmd = c;
                    Serial.printf("UDP command: %c\n", c);
                }
            }
        }
    }
}

void setup() {
    Serial.begin(115200);
    delay(100);
    Serial.println("\nQuadBot (Emotiv/UDP + Web) starting...");

    // Bring up the servos and park in a known pose
    robot.init();
    Serial.println("Moving to zero position...");
    robot.zero();
    Serial.println("Standby position...");
    robot.standby();

    // Connect to Wi-Fi (station mode)
    Serial.printf("Connecting to Wi-Fi \"%s\"", WIFI_SSID);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("Wi-Fi connected. ESP8266 IP address: ");
    Serial.println(WiFi.localIP());   // <-- open this IP on your phone / put in config.py

    // Start the web control panel
    server.on("/", handleRoot);
    server.on("/cmd", handleCmd);
    server.begin();
    Serial.println("Web control panel ready: open the IP above in a browser.");

    // Start listening for UDP commands
    Udp.begin(LOCAL_UDP_PORT);
    Serial.printf("Listening for UDP commands on port %u\n", LOCAL_UDP_PORT);
    Serial.println("Ready. Drive from the phone panel or send F/B/L/R/S from the PC bridge.");
}

void loop() {
    // Pick up any newly-arrived command (web or UDP)
    service();

    // Run the active command. Gaits loop cycle-after-cycle until the command
    // changes; each returns early when it does (checked inside writeFrame).
    switch (currentCmd) {
        case 'F': robot.forward();      break;
        case 'B': robot.backward();     break;
        case 'L': robot.turn(true);     break;
        case 'R': robot.turn(false);    break;
        case 'S':
        default:
            robot.standby();     // hold the standby pose while stopped
            break;
    }
}
