/*
Arduino UNO code for controlling 2WD DC gear motors based on serial commands received from ESP32.
Assumed wiring:
- Left Motor: PWM on pin 9, direction control on pin 8.
- Right Motor: PWM on pin 10, direction control on pin 7.
Commands: FORWARD, BACKWARD, LEFT, RIGHT, STOP.
*/

const int leftMotorPWM = 9;
const int leftMotorDir = 8;
const int rightMotorPWM = 10;
const int rightMotorDir = 7;

int motorSpeed = 150; // Adjust speed (0-255)

void setup() {
  Serial.begin(115200); // Communication with ESP32
  pinMode(leftMotorPWM, OUTPUT);
  pinMode(leftMotorDir, OUTPUT);
  pinMode(rightMotorPWM, OUTPUT);
  pinMode(rightMotorDir, OUTPUT);
  
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
    }
  }
}

void moveForward() {
  // Both motors forward
  digitalWrite(leftMotorDir, HIGH);
  digitalWrite(rightMotorDir, HIGH);
  analogWrite(leftMotorPWM, motorSpeed);
  analogWrite(rightMotorPWM, motorSpeed);
  Serial.println("Moving Forward");
}

void moveBackward() {
  // Both motors reverse (assuming LOW is reverse; adjust as needed)
  digitalWrite(leftMotorDir, LOW);
  digitalWrite(rightMotorDir, LOW);
  analogWrite(leftMotorPWM, motorSpeed);
  analogWrite(rightMotorPWM, motorSpeed);
  Serial.println("Moving Backward");
}

void turnLeft() {
  // To turn left: slow left motor, full speed right motor
  digitalWrite(leftMotorDir, HIGH);
  digitalWrite(rightMotorDir, HIGH);
  analogWrite(leftMotorPWM, motorSpeed / 2); // slower left motor
  analogWrite(rightMotorPWM, motorSpeed);
  Serial.println("Turning Left");
}

void turnRight() {
  // To turn right: full speed left motor, slow right motor
  digitalWrite(leftMotorDir, HIGH);
  digitalWrite(rightMotorDir, HIGH);
  analogWrite(leftMotorPWM, motorSpeed);
  analogWrite(rightMotorPWM, motorSpeed / 2); // slower right motor
  Serial.println("Turning Right");
}

void stopMotors() {
  analogWrite(leftMotorPWM, 0);
  analogWrite(rightMotorPWM, 0);
  Serial.println("Motors Stopped");
}
