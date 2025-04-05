# Garbage and Drainage Monitoring System

## Overview
This project is designed to monitor the levels of garbage in bins and detect potential blockages in drainage systems. It uses ultrasonic sensors interfaced with an Arduino Uno board and alerts users with LEDs, buzzers, and serial messages when critical levels are reached.

---

## Hardware Used
- Arduino Uno
- Ultrasonic Sensors (HC-SR04) x2
- Red LED
- Buzzer
- Jumper Wires
- Breadboard

## Components Pin Configuration
| Component | Arduino Pin |
| :-------: | :---------: |
| Garbage Sensor Trigger | 9 |
| Garbage Sensor Echo | 8 |
| Drainage Sensor Trigger | 7 |
| Drainage Sensor Echo | 6 |
| Red LED | 5 |
| Buzzer | 4 |

---

## Working Principle
- **Garbage Monitoring**: Detects the distance from the sensor to the top of the garbage pile.
- **Drainage Monitoring**: Measures water levels in the drainage pipe.
- When the garbage or drainage level crosses a set threshold (10 cm by default), the system triggers an alert by lighting up the LED and activating the buzzer.

---

## Circuit Diagram
*(Please connect according to the pin configuration above. HC-SR04 requires VCC (5V) and GND.)*

---

## Installation & Setup
1. Connect the components according to the hardware configuration table.
2. Install Arduino IDE (if not installed already).
3. Open the provided `Garbage_and_Drainage_Monitoring_System.ino` file.
4. Select the correct board (Arduino Uno) and port.
5. Upload the code to the Arduino Uno.
6. Open Serial Monitor (9600 baud rate) to view system alerts.

---

## Code Explanation
- `measureDistance()` function triggers the ultrasonic sensor and measures the time it takes for the echo to return.
- `alertSystem()` function activates the LED and buzzer whenever the threshold is breached.
- Main `loop()` continuously checks the garbage and drainage levels.

---

## Features
- Real-time monitoring of garbage bins and drainage pipes.
- Immediate alerts using LEDs and buzzers.
- Serial Monitor output for detailed messages.

---

## Future Enhancements
- GSM module integration to send SMS alerts.
- IoT-based cloud integration for remote monitoring.
- Solar-powered operation for outdoor installations.

---

## Contributions
- Developed and maintained by:
  - GitHub ID: [@YourGitHubIDHere]

*(Replace `YourGitHubIDHere` with your actual GitHub username)*

---

## License
This project is open-source under the MIT License.
