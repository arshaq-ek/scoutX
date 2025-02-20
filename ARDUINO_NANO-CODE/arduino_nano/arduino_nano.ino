#include <Servo.h>

/*
Arduino Mega code for controlling 2WD DC gear motors and a servo based on serial commands received from ESP32.
Assumed wiring for motor driver (example with L298N):
- Left Motor: PWM on pin 9, direction control on pins 8 (IN1) and 7 (IN2).
- Right Motor: PWM on pin 10, direction control on pins 6 (IN3) and 5 (IN4).
- Servo: Signal on pin 4.
Commands: FORWARD, BACKWARD, LEFT, RIGHT, STOP, OPEN, CLOSE.
*/

const int leftMotorPWM = 9;
const int leftMotorDir1 = 8;
const int leftMotorDir2 = 7;

const int rightMotorPWM = 10;
const int rightMotorDir1 = 6;
const int rightMotorDir2 = 5;

const int servoPin = 4;

int motorSpeed = 150; // Adjust speed (0-255)

Servo myServo;

void setup() {
  Serial.begin(115200); // Communication with ESP32

  // Set motor control pins as outputs
  pinMode(leftMotorPWM, OUTPUT);
  pinMode(leftMotorDir1, OUTPUT);
  pinMode(leftMotorDir2, OUTPUT);
  
  pinMode(rightMotorPWM, OUTPUT);
  pinMode(rightMotorDir1, OUTPUT);
  pinMode(rightMotorDir2, OUTPUT);
  
  // Initialize servo and attach it to servoPin
  myServo.attach(servoPin);
  myServo.write(0); // Start with servo at 0°

  // Ensure motors are stopped at startup
  stopMotors();
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    Serial.print("Received command: ");
    Serial.println(command);

    if (command == "FORWARD") {
      moveForward();
    } else if (command == "BACKWARD") {
      moveBackward();
    } else if (command == "LEFT") {
      turnLeft();
    } else if (command == "RIGHT") {
      turnRight();
    } else if (command == "STOP") {
      stopMotors();
    } else if (command == "OPEN") {
      openServo();
    } else if (command == "CLOSE") {
      closeServo();
    }
  }
}

void moveForward() {
  // Set left motor: IN1=HIGH, IN2=LOW for forward
  digitalWrite(leftMotorDir1, HIGH);
  digitalWrite(leftMotorDir2, LOW);
  analogWrite(leftMotorPWM, motorSpeed);

  // Set right motor: IN3=HIGH, IN4=LOW for forward
  digitalWrite(rightMotorDir1, HIGH);
  digitalWrite(rightMotorDir2, LOW);
  analogWrite(rightMotorPWM, motorSpeed);

  Serial.println("Moving Forward");
}

void moveBackward() {
  // For backward, reverse the motor directions.
  digitalWrite(leftMotorDir1, LOW);
  digitalWrite(leftMotorDir2, HIGH);
  analogWrite(leftMotorPWM, motorSpeed);

  digitalWrite(rightMotorDir1, LOW);
  digitalWrite(rightMotorDir2, HIGH);
  analogWrite(rightMotorPWM, motorSpeed);

  Serial.println("Moving Backward");
}

void turnLeft() {
  // To turn left, slow the left motor and run the right motor at full speed forward.
  digitalWrite(leftMotorDir1, LOW);
  digitalWrite(leftMotorDir2, HIGH);
  analogWrite(leftMotorPWM, motorSpeed / 2); // slower left motor

  digitalWrite(rightMotorDir1, HIGH);
  digitalWrite(rightMotorDir2, LOW);
  analogWrite(rightMotorPWM, motorSpeed);

  Serial.println("Turning Left");
}

void turnRight() {
  // To turn right, run the left motor at full speed and slow the right motor.
  digitalWrite(leftMotorDir1, HIGH);
  digitalWrite(leftMotorDir2, LOW);
  analogWrite(leftMotorPWM, motorSpeed);

  digitalWrite(rightMotorDir1, LOW);
  digitalWrite(rightMotorDir2, HIGH);
  analogWrite(rightMotorPWM, motorSpeed / 2); // slower right motor

  Serial.println("Turning Right");
}

void stopMotors() {
  analogWrite(leftMotorPWM, 0);
  analogWrite(rightMotorPWM, 0);
  Serial.println("Motors Stopped");
}

void openServo() {
  myServo.write(90);
  Serial.println("Servo Opened (90°)");
}

void closeServo() {
  myServo.write(0);
  Serial.println("Servo Closed (0°)");
}
