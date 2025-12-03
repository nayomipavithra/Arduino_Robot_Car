#include <Servo.h>
#include <SoftwareSerial.h>

// ------------------- Pin Definitions -------------------
// Motor driver pins (L298N)
#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7

// IR sensors
#define IR_LEFT A0
#define IR_RIGHT A1

// Ultrasonic
#define TRIG 11
#define ECHO 12

// Servo
Servo servoMotor;  // ultrasonic mounted on servo

// ------------------- Variables -------------------
char command,newcommand = ' ';
int mode;
long duration, distance;

// ------------------- Setup -------------------
void setup() {
  Serial.begin(9600);
  Serial.println("Bluetooth ready. Type something:");
  Serial.println("Robot initializing...");

  // Motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // IR pins
  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);

  // Ultrasonic pins
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // Servo init
  servoMotor.attach(9);
  servoMotor.write(90); // look forward

  Serial.println("Setup complete, waiting for commands...");
}

// ------------------- Functions -------------------
void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Motors: Moving forward");
}

void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Motors: Moving backward");
}

void left() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("Motors: Turning left");
}

void right() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("Motors: Turning right");
}

void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  Serial.println("Motors: Stopped");
}

long readUltrasonic() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH, 20000); // 20ms timeout
  distance = duration * 0.034 / 2;       // cm

  if (distance == 0) {
    Serial.println("Ultrasonic: No echo detected");
  } else {
    Serial.print("Ultrasonic: Distance = ");
    Serial.print(distance);
    Serial.println(" cm");
  }

  return distance;
}

// ------------------- Line Following -------------------
void lineFollow() {
  int leftIR = digitalRead(IR_LEFT);
  int rightIR = digitalRead(IR_RIGHT);

  Serial.print("IR Sensors: Left=");
  Serial.print(leftIR);
  Serial.print(", Right=");
  Serial.println(rightIR);

  if (leftIR == HIGH && rightIR == HIGH) {
    Serial.println("Line detected: Both sensors on line, moving forward");
    forward();
  }
  else if (leftIR == LOW && rightIR == HIGH) {
    Serial.println("Line detected: Left off line, turning left");
    left();
  }
  else if (leftIR == HIGH && rightIR == LOW) {
    Serial.println("Line detected: Right off line, turning right");
    right();
  }
  else {
    Serial.println("Line lost: Both sensors off line, stopping");
    stopMotors();
  }
}

// ------------------- Obstacle Avoid -------------------
void obstacleAvoid() {
  long dist = readUltrasonic();

  if (dist < 20 && dist > 0) {
    Serial.println("Obstacle detected! Stopping and scanning...");
    stopMotors();
    delay(300);

    // Look left
    Serial.println("Servo: Looking left");
    servoMotor.write(150);
    delay(500);
    long leftDist = readUltrasonic();

    // Look right
    Serial.println("Servo: Looking right");
    servoMotor.write(30);
    delay(500);
    long rightDist = readUltrasonic();

    // Reset forward
    Serial.println("Servo: Reset forward");
    servoMotor.write(90);
    delay(300);

    // Decide turn
    if (leftDist > rightDist) {
      Serial.println("Turning left to avoid obstacle");
      left();
      delay(500);
    } else {
      Serial.println("Turning right to avoid obstacle");
      right();
      delay(500);
    }
  }
  else {
    Serial.println("No obstacle detected, continuing line follow");
    lineFollow(); // continue following line
  }
}

// ------------------- Loop -------------------
void loop() {
  if (Serial.available()) {
    command = Serial.read();
    Serial.print("Command received: ");
    Serial.println(command);
  }

  if (command == '1') {
    mode=1;
    Serial.println("Mode: Auto (Line follow + Obstacle avoid)");
    obstacleAvoid();  // Auto: line follow + obstacle avoid
  }
  else if (command == '2') {
    mode=2;
    Serial.println("Mode: Manual control");
    
  }
  if(mode==1){

  }
  if(mode==2){
    if (Serial.available()) {
      newcommand = Serial.read();
      Serial.print("Manual command received: ");
      Serial.println(newcommand);
      if (newcommand == 'F') {
        forward();
      } else if (newcommand == 'B') {
        backward();
      } else if (newcommand == 'L') {
        left();
      } else if (newcommand == 'R') {
        right();
      } else if (newcommand == 'S') {
        stopMotors();
      }
    }
  }

  delay(100); // small delay to prevent Serial flooding
}
