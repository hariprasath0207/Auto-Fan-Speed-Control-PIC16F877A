# Temperature-Controlled Automatic Fan Speed System (Proteus Simulation)

An embedded hardware and firmware project that automatically monitors ambient temperature and regulates a DC motor/fan speed accordingly using Pulse Width Modulation (PWM). The entire system is built with a PIC microcontroller and simulated accurately in Proteus.

## 🚀 Features
- **Real-time Temperature Sensing:** Monitors ambient temperature using an analog LM35 sensor.
- **Dynamic Speed Modulation:** Processes data with an internal ADC and scales hardware PWM duty cycles dynamically.
- **16x2 LCD Interface:** Visually displays live temperature readings ( °C ) alongside categorized speed levels.
- **Motor Driver Interfacing:** Safely drives a high-current DC motor via an L293D H-Bridge integration circuit.

---

## 🛠️ System Components & Hardware Architecture

| Component | Function | Connection Pin (PIC16F877A) |
| :--- | :--- | :--- |
| **PIC16F877A** | Core Microcontroller Unit (MCU) | Main Controller |
| **LM35** | Precision Centigrade Temperature Sensor | `RA0/AN0` (Analog Input 0) |
| **LM016L (16x2 LCD)** | Data Display Console | Data: `PORTD`, RS: `RC5`, RW: `RC6`, EN: `RC7` |
| **L293D** | H-Bridge Motor Driver IC | IN1/PWM: `RC2/CCP1`, IN2: `RC1`, EN1: `RC0` |
| **DC Motor** | Output Fan Component | Driven via L293D Out1/Out2 pins |

---

## 📊 System Control Logic

The firmware checks the calculated temperature and alters the 10-bit PWM register configuration to regulate the fan through four distinct operational stages:

| Temperature Range | Duty Cycle Flag | Speed Level Profile |
| :--- | :--- | :--- |
| **< 25°C** | 0% (`0`) | **OFF** |
| **25°C to 29°C** | ~25% (`256`) | **LOW** |
| **30°C to 50°C** | ~50% (`512`) | **MED** |
| **> 50°C** | 100% (`1023`) | **HIGH** |

---

## 📁 Repository Structure
* `auto fan speed control.c` - Embedded C Source Code (HI-TECH C/XC8 compiler compatible)
* `Automated Fan speed control.DSN` - Proteus Design Schematic file
* `Screenshot 2026-06-20 193228.png` - Schematic capture layout image

---

## 💻 Firmware Implementation Highlights

The control logic depends heavily on using the internal capture/compare/PWM register modules:
- **ADC Configuration:** Configured to sample analog data inputs at channel `AN0` with right-justified alignments using a standard +5V reference setup.
- **PWM Parameters:** Driven by configuring Timer 2 parameters, setting `PR2 = 249` to form balanced output frequencies controlling the L293D driver signals smoothly.

---

## ⚙️ How to Run the Simulation
1. Clone this repository or download the source directories.
2. Open the `.DSN` file inside **Proteus 8 suite (or higher)**.
3. Compile the code file using your PIC development tools to obtain the compiled binary image code (`.hex`).
4. Double-click the PIC16F877A component symbol layout inside Proteus, locate the **Program File** properties field, and path-link your generated hex file.
5. Hit the **Play/Run** interactive button workspace element at the bottom corner of the software to interactively test variations by adjusting the voltage output buttons on the LM35 sensor package.
