#include <Servo.h>

Servo motor;

int trigPin = 9;
int echoPin = 10;

long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  motor.attach(5);

  Serial.begin(9600);
}

void loop() {

  // Trigger ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.034 / 2;

  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance <= 15) {
    motor.write(90);   // Stop position
    Serial.println("Obstacle detected - Motor stopped");
  }
  else {
    motor.write(0);
    delay(300);
    motor.write(180);
    delay(300);

    Serial.println("Motor running");
  }
}
