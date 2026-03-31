Components Introduction
=======================

**Below is the introduction to each component, which contains the operating principle of the component.**

----

ESP8266 Development Board
--------------------------

The **ESP8266** is a low-cost, highly integrated Wi-Fi microcontroller system-on-chip (SoC) designed for IoT and embedded applications. It features a 32-bit RISC processor with built-in Wi-Fi capability, making it ideal for smart home devices, robotics, and connected sensors.

**Key Features:**

- **Processor**: 32-bit RISC (Tensilica L106) running at 80/160 MHz
- **Memory**: 160 KB RAM, 4 MB Flash (typical, expandable)
- **Wi-Fi**: 802.11 b/g/n support, single-band 2.4 GHz
- **GPIO Pins**: 11 programmable general-purpose I/O pins
- **Communication Protocols**: SPI, I2C, UART, PWM
- **Power Supply**: 3.3V DC, low power consumption (~20 μA in sleep mode)
- **Boot Mode**: Selectable via IO pin configuration

**Operating Principle:**

The ESP8266 operates based on a Xtensa processor core with an integrated Wi-Fi radio (MAC and PHY). It supports both STA (Station) and AP (Access Point) modes, allowing it to connect to existing networks or create its own hotspot. Programs are typically written in the Arduino IDE or MicroPython environment and burned into the onboard flash memory via USB-to-UART bridge (CP2102 in this kit). Upon reset, the bootloader loads the firmware from flash and executes the user program.

----


Quadruped Spider Robot Expansion Board
--------------------------------------

The Quadruped Spider Robot Expansion Board is specifically designed for this kit. It features an onboard battery compartment and charging functionality, along with multiple circuit protection designs including reverse polarity protection and fuses. It also includes large capacitors to enhance system stability and instantaneous response capability, ensuring smooth and reliable servo operation. Additionally, it extends the ESP8266 development board's pins for easy wiring.

The following is a pinout diagram of the expansion board and the ESP8266 development board:

.. list-table:: ESP8266 Digital Pin to GPIO Mapping
   :header-rows: 1

   * - Digital Pin
     - GPIO
   * - D0
     - GPIO16
   * - D1
     - GPIO5
   * - D2
     - GPIO4
   * - D3
     - GPIO0
   * - D4
     - GPIO2
   * - D5
     - GPIO14
   * - D6
     - GPIO12
   * - D7
     - GPIO13
   * - D8
     - GPIO15

----

MG90S servo
-----------

