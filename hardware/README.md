# Hardware Documentation

## Autonomous Mini Sumo Robot

This project integrates an ESP32 microcontroller, a TB6612FNG motor driver, and ultrasonic and infrared sensors to create an autonomous robotic system.

## Main Components

| Component | Quantity | Function |
| --- | --- | --- |
| ESP32 | 1 | Main microcontroller |
| TB6612FNG | 1 | Dual DC motor driver |
| DC Gear Motors | 2 | Robot movement |
| HC-SR04 | 1 | Opponent detection |
| TCRT5000 | 1 | Arena boundary detection |
| Battery System | 1 | Electrical power supply |

## Motor Driver Connections

| TB6612FNG | ESP32 GPIO |
| --- | --- |
| AIN1 | 21 |
| AIN2 | 22 |
| PWMA | 23 |
| BIN1 | 25 |
| BIN2 | 33 |
| PWMB | 32 |

STBY is connected directly to the appropriate logic HIGH supply, rather than controlled through a GPIO.

## Ultrasonic Sensor

| HC-SR04 | ESP32 |
| --- | --- |
| TRIG | GPIO 18 |
| ECHO | GPIO 34 |

The HC-SR04 ECHO signal must be reduced to a safe 3.3 V level before reaching the ESP32.

## Infrared Sensor

| TCRT5000 | ESP32 |
| --- | --- |
| AO | GPIO 26 |

### Sensor Calibration

| Surface | Analog Reading |
| --- | --- |
| Black | Approximately 2800 |
| White | Approximately 700 |
| Detection Threshold | 1750 |

When the sensor reading falls below 1750, the robot identifies the white boundary and performs an escape maneuver.

## Operating Logic

1. Search for an opponent by rotating.
2. Detect objects using the HC-SR04.
3. Move forward when an opponent is detected within 30 cm.
4. Monitor the arena boundary using the TCRT5000.
5. Reverse and turn when the white boundary is detected.

Boundary detection has priority over opponent detection.

## Hardware Safety

- Use a common ground for the ESP32, motor driver, and sensors.
- Keep ESP32 GPIO signals within the permitted voltage range.
- Match the motor power supply to the motor specifications.
- Verify all wiring before connecting the battery.

## Development Status

Firmware v1.0 has been physically tested.

Detailed power-system specifications and circuit schematics will be added after verification.
