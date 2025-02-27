#include <Servo.h>

// Motor Pins (L298N)
const int leftMotorPWM = 9;
const int leftMotorDir1 = 8;
const int leftMotorDir2 = 7;

const int rightMotorPWM = 10;
const int rightMotorDir1 = 6;
const int rightMotorDir2 = 5;

const int servoPin = 4;
int motorSpeed = 150;  // Speed (0-255)

Servo myServo;

void setup() {
  Serial.begin(115200);  // Debugging
  Serial2.begin(115200); // Communication with ESP32

  pinMode(leftMotorPWM, OUTPUT);
  pinMode(leftMotorDir1, OUTPUT);
  pinMode(leftMotorDir2, OUTPUT);
  
  pinMode(rightMotorPWM, OUTPUT);
  pinMode(rightMotorDir1, OUTPUT);
  pinMode(rightMotorDir2, OUTPUT);
  
  myServo.attach(servoPin);
  myServo.write(0); // Default position

  stopMotors();
}

void loop() {
  if (Serial2.available()) {
    String command = Serial2.readStringUntil('\n');
    command.trim();
    Serial.println("Received from ESP32: " + command);

    if (command == "FORWARD") moveForward();
    else if (command == "BACKWARD") moveBackward();
    else if (command == "LEFT") turnLeft();
    else if (command == "RIGHT") turnRight();
    else if (command == "STOP") stopMotors();
    else if (command == "OPEN") openServo();
    else if (command == "CLOSE") closeServo();
  }
}

void moveForward() {
  digitalWrite(leftMotorDir1, HIGH);
  digitalWrite(leftMotorDir2, LOW);
  analogWrite(leftMotorPWM, motorSpeed);

  digitalWrite(rightMotorDir1, HIGH);
  digitalWrite(rightMotorDir2, LOW);
  analogWrite(rightMotorPWM, motorSpeed);

  Serial.println("Moving Forward");
}

void moveBackward() {
  digitalWrite(leftMotorDir1, LOW);
  digitalWrite(leftMotorDir2, HIGH);
  analogWrite(leftMotorPWM, motorSpeed);

  digitalWrite(rightMotorDir1, LOW);
  digitalWrite(rightMotorDir2, HIGH);
  analogWrite(rightMotorPWM, motorSpeed);

  Serial.println("Moving Backward");
}

void turnLeft() {
  digitalWrite(leftMotorDir1, LOW);
  digitalWrite(leftMotorDir2, HIGH);
  analogWrite(leftMotorPWM, motorSpeed / 2);

  digitalWrite(rightMotorDir1, HIGH);
  digitalWrite(rightMotorDir2, LOW);
  analogWrite(rightMotorPWM, motorSpeed);

  Serial.println("Turning Left");
}

void turnRight() {
  digitalWrite(leftMotorDir1, HIGH);
  digitalWrite(leftMotorDir2, LOW);
  analogWrite(leftMotorPWM, motorSpeed);

  digitalWrite(rightMotorDir1, LOW);
  digitalWrite(rightMotorDir2, HIGH);
  analogWrite(rightMotorPWM, motorSpeed / 2);

  Serial.println("Turning Right");
}

void stopMotors() {
  analogWrite(leftMotorPWM, 0);
  analogWrite(rightMotorPWM, 0);
  Serial.println("Motors Stopped");
}

void openServo() {
  if (myServo.read() != 90) {
    myServo.write(90);
    Serial.println("Servo Opened (90°)");
  }
}

void closeServo() {
  if (myServo.read() != 0) {
    myServo.write(0);
    Serial.println("Servo Closed (0°)");
  }
}
