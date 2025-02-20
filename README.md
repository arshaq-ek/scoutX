# ScoutX - Indoor Surveillance and Delivery Robot

ScoutX is an indoor autonomous robot designed for surveillance and light payload delivery. It uses an ESP32-CAM for video streaming and Wi-Fi control, and an Arduino Mega to drive a 2WD chassis with DC gear motors and a servo for additional functionality (such as a gripper or indicator). Commands are received from a web-based control panel and forwarded from the ESP32-CAM to the Arduino Mega.

## Table of Contents

- [Features](#features)
- [Hardware Components](#hardware-components)
- [Software Components](#software-components)
- [Wiring and Assembly](#wiring-and-assembly)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Future Work](#future-work)
- [License](#license)

## Features

- **Wi-Fi Control & Video Streaming:**  
  - The ESP32-CAM connects to Wi-Fi and streams video at `http://<ESP32_IP>:81/stream`.
  - It hosts a lightweight web server to receive movement and servo commands.

- **Remote Command Forwarding:**  
  - A web-based control panel allows users to send commands (e.g., FORWARD, BACKWARD, LEFT, RIGHT, STOP, OPEN, CLOSE).
  - The ESP32-CAM forwards these commands via Serial to the Arduino Mega.

- **2WD Motor Control:**  
  - An Arduino Mega controls two DC gear motors via a motor driver (e.g., L298N) in a 2WD configuration.
  - Motor speeds and directions are adjusted based on the received commands.

- **Servo Control:**  
  - A servo is integrated (e.g., for a gripper or indicator) and controlled via commands from the web interface.
  - Commands "OPEN" and "CLOSE" move the servo to 90° and 0°, respectively.

## Hardware Components

- **ESP32-CAM (AI-Thinker)** with OV2640 camera module.
- **Arduino Mega** for motor and servo control.
- **DC Gear Motors:** TT Motor – N20 12V 125RPM.
- **Motor Driver:** (e.g., L298N) for 2WD configuration.
- **Servo Motor:** For opening/closing function.
- **Power Supply:** Suitable battery (e.g., 12V for motors, regulated 5V for logic and servo).
- **Miscellaneous:** Jumper wires, breadboard/PCB for connections, and a mounting chassis.

## Software Components

- **ESP32-CAM Code:**  
  - Connects to Wi-Fi, streams video, and runs a lightweight web server.
  - Forwards movement commands to the Arduino Mega via Serial.

- **Arduino Mega Code:**  
  - Receives commands over Serial and drives the motor driver to control the 2WD system.
  - Implements functions for forward, backward, turning, stopping, and servo control.

- **Web Control Panel:**  
  - A simple HTML page (hosted on a Flask server or locally) with buttons to send movement and servo commands.

## Wiring and Assembly

**ESP32-CAM to Arduino Mega:**  
- ESP32-CAM TX (e.g., GPIO 4) → Arduino Mega RX (via appropriate Serial channel).  
- ESP32-CAM RX (e.g., GPIO 12) → Arduino Mega TX.  
- Ensure common ground between ESP32-CAM and Arduino Mega.

**Motor Driver (Assuming L298N) Connections:**  
- **Left Motor:**  
  - PWM (ENA) → Arduino Mega PWM pin (e.g., 9)  
  - Direction Pins: IN1 → Mega pin 8, IN2 → Mega pin 7.
- **Right Motor:**  
  - PWM (ENB) → Arduino Mega PWM pin (e.g., 10)  
  - Direction Pins: IN3 → Mega pin 6, IN4 → Mega pin 5.

**Servo:**  
- Signal → Arduino Mega digital pin (e.g., 4).  
- Power the servo using a regulated 5V supply (ensure common ground with the Mega).

**Power:**  
- Connect the motor driver’s power input to your battery (ensure proper voltage for motors).
- Connect the battery ground with the Arduino Mega and other components.

## Usage

1. **ESP32-CAM Setup:**  
   - Program the ESP32-CAM with the provided code.
   - Connect it to your Wi-Fi network.
   - Confirm that video streaming is active at `http://<ESP32_IP>:81/stream`.

2. **Arduino Mega Setup:**  
   - Upload the Arduino Mega code to control motors and servo.
   - Verify that it receives commands from the ESP32 via Serial.

3. **Control Interface:**  
   - Use the provided web control panel (or a Flask server on your PC) to send commands.
   - Commands such as `FORWARD`, `BACKWARD`, `LEFT`, `RIGHT`, `STOP`, `OPEN`, and `CLOSE` will control the robot accordingly.


## Future Work

- **Enhanced Image Processing:**  
  - Integrate face or object recognition on the PC side using OpenCV.
  - Send automated commands to ScoutX based on image processing.

- **Improved Navigation:**  
  - Add sensors (ultrasonic, IR) for obstacle avoidance.
  - Implement path planning algorithms for autonomous navigation.

- **Hardware Refinements:**  
  - Optimize chassis design for stability and weight distribution.
  - Consider using encoder motors for more precise control in later iterations.

## License

This project is open-source. Feel free to modify and use it as needed.  


