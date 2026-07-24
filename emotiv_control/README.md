# Emotiv EPOC X → LAFVIN Spider Robot

Control the LAFVIN quadruped spider (ESP8266 + 8 servos) two ways at once:

- a **phone/browser control panel** with buttons (Forward / Back / Left / Right / Stop),
  served **directly by the ESP8266** — no computer needed, and
- **Emotiv EPOC X mental commands** (think *push / pull / left / right* to move), forwarded
  from a PC.

Both paths set the same one-character command on the robot, so you can verify everything
with the buttons **before** dealing with the headset.

```
   Phone/PC browser  ── http:// <ESP-IP> /cmd?c=F ──────────────┐
   (Forward/Back/Left/Right/Stop)                               ▼
                                                        ESP8266  (web panel :80
   Emotiv EPOC X ──USB/BT──▶ PC: emotiv_bridge.py ──UDP :4210──▶  + UDP listener
   (Cortex "com" stream)      (mental command → 1 char)          → SpiderBotMotion gait)
```

- **Firmware** `firmware/emotiv_spider/emotiv_spider.ino` (C/Arduino) — flashed to the
  ESP8266. It serves the control panel **and** listens for UDP commands.
- **PC program** `bridge/emotiv_bridge.py` (Python) — only needed for the Emotiv path; it
  turns mental commands into UDP characters. (It also serves its own localhost panel, handy
  on the PC.)

Everything is on your normal home Wi-Fi (the ESP8266 runs in **station mode**), so your phone
just uses its regular Wi-Fi connection.

## Command reference

| Char | Robot action | Button | Mental command (default) |
|------|--------------|--------|--------------------------|
| `F`  | walk forward | ▲ Forward | push    |
| `B`  | walk backward| ▼ Back    | pull    |
| `L`  | turn left    | ◄ Left    | left    |
| `R`  | turn right   | ► Right   | right   |
| `S`  | stop (standby)| ■ Stop   | neutral |

---

## 1. Flash the ESP8266

1. In the Arduino IDE, install ESP8266 board support and make sure the `Servo` library is
   available (bundled with the ESP8266 core).
2. Open `firmware/emotiv_spider/emotiv_spider.ino`.
3. Set your home Wi-Fi credentials near the top:
   ```cpp
   const char* WIFI_SSID     = "YOUR_WIFI_SSID";
   const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
   ```
4. Flash the board, then open **Serial Monitor @ 115200**. It prints the IP address the
   board received, e.g. `ESP8266 IP address: 192.168.1.50`. **Write this down.**

> Your phone, the PC and the ESP8266 must all be on the **same Wi-Fi network**.

## 2. Drive from your phone — no PC needed

1. Connect your phone to the **same Wi-Fi** the ESP8266 joined.
2. Open a browser and go to `http://<ESP-IP>` (the IP from the Serial Monitor, e.g.
   `http://192.168.1.50`).
3. Tap **Forward / Back / Left / Right / Stop**. The spider walks, turns, and stops. Each tap
   is echoed on the Serial Monitor as `Web command: …`.

This proves the whole robot works with zero PC setup, and it's the easiest way to tune the
gaits (see *Tuning* below). The Emotiv steps below are only needed for mind control.

## 3. Set up the PC bridge (for mental commands)

```bash
cd bridge
pip install -r requirements.txt        # installs websocket-client
cp config.example.py config.py         # then edit config.py
```

In `config.py` set at least:
```python
ESP8266_IP = "192.168.1.50"   # the IP from the Serial Monitor
```
(`config.py` is git-ignored so your credentials stay private.)

There's also a PC-side control panel if you want to test from the computer without the
headset — `python emotiv_bridge.py --ui-only`, then open `http://localhost:8080`. (The phone
panel from step 2 does the same thing straight from the robot.)

## 4. Add the Emotiv headset

1. Install the **EMOTIV Launcher**, log in, fit the EPOC X with hydrated felts, and confirm a
   good contact-quality signal.
2. Create a **Cortex app** at <https://www.emotiv.com/developer/> to get a **Client ID** and
   **Client Secret**; put them in `config.py`.
3. In **EmotivBCI**, train your mental commands — at minimum **Neutral** plus the actions you
   want (Push / Pull / Left / Right). Save the profile and put its name in `config.py`:
   ```python
   PROFILE_NAME = "MyProfile"
   ```
4. Run the full bridge:
   ```bash
   python emotiv_bridge.py
   ```
   First run only: approve the app in the EMOTIV Launcher when prompted. Then *think* to
   drive — and the phone buttons still work as a manual override.

### Run order recap
router on → flash ESP8266 → note its IP → **drive from the phone to verify** → (for mind
control) fill `config.py` → start EMOTIV Launcher with good signal → `python emotiv_bridge.py`.

---

## Tuning the gaits

Only the **forward** gait comes from the official LAFVIN course; **backward** and the
**turns** are authored here and are *starter values*. If a movement looks off:

- **Backward** replays the forward keyframes in reverse — usually fine as-is.
- **Turns** are the forward gait with one side's stride damped. In `emotiv_spider.ino`:
  - If *Left* turns right (or vice-versa), swap `LEFT_H_SERVOS` and `RIGHT_H_SERVOS`.
  - If turns are too weak/strong, change `TURN_DAMP` (`0.0` = spins hard in place,
    `1.0` = walks straight).
- For per-servo trim, follow the LAFVIN **servo calibration** guide:
  <https://lafvin-quadruped-spider-robot.readthedocs.io/en/latest/AssemblyTutorial.html#servo-calibration-and-debug>

Use the phone control panel while tuning so you can trigger each movement on demand.

## Troubleshooting

| Symptom | Likely cause / fix |
|---------|--------------------|
| Phone can't open the page | Phone not on the same Wi-Fi as the ESP8266; wrong IP; typed `https` instead of `http`. Re-check the IP on the Serial Monitor. |
| PC bridge buttons/commands do nothing | PC and ESP8266 on different networks; wrong `ESP8266_IP`; firewall blocking UDP. Check the ESP Serial Monitor for `UDP command: …`. |
| Only `neutral`/Stop ever fires | Mental commands not trained, or `PROFILE_NAME` empty/wrong. Train in EmotivBCI and set the profile name. |
| `authorize failed` / cert error | EMOTIV Launcher not running/logged in; the script already disables cert verification for the local self-signed cert. |
| `No headset found` | EPOC X off, or USB dongle not inserted / Bluetooth not paired. |
| Servos twitch / robot unstable | Servo calibration — see the *Tuning* link above. |
| `Address already in use` on start | Another process holds `UI_PORT`; change `UI_PORT` in `config.py`. |
| Robot keeps walking after Stop | Make sure `neutral` maps to `S`; Stop must be sent to break the gait loop. |

## Files

```
emotiv_control/
├── README.md
├── firmware/emotiv_spider/emotiv_spider.ino   # ESP8266: Wi-Fi + web panel + UDP + gaits
└── bridge/
    ├── emotiv_bridge.py        # PC-side panel + Emotiv → UDP
    ├── config.example.py       # copy to config.py and edit
    ├── requirements.txt        # websocket-client
    └── .gitignore              # keeps config.py out of git
```
