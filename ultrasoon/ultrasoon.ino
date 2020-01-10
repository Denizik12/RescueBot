/*
  -project 2.
  -ultrasoon om obstakels te detecteren.
  -versie 2.0.
*/

//ultrasoon pins
#define trigPin 6
#define echoPin 7

// h-bridge module pins
#define PIN_1 2
#define PIN_2 3
#define PIN_3 4
#define PIN_4 5
#define led 9

float duration, distance;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(led, INPUT);
  pinMode(PIN_1, OUTPUT);
  pinMode(PIN_2, OUTPUT);
  pinMode(PIN_3, OUTPUT);
  pinMode(PIN_4, OUTPUT);
}

void loop() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  // Use 343 metres per second as speed of sound
  distance = (duration / 2) * 0.0343;

  //resultaat op de serial monitor printen.
  Serial.print("Distance = ");
  Serial.print(distance);
  Serial.println(" cm");

if(distance <= 5){
  motorDirectionBackward();
  }
  
}


// motor forward function
void motorDirectionForward() {
  digitalWrite(PIN_1, HIGH);
  digitalWrite(PIN_2, LOW);

  digitalWrite(PIN_3, HIGH);
  digitalWrite(PIN_4, LOW);
}

// motor backwards function
void motorDirectionBackward() {
  digitalWrite(PIN_1, LOW);
  digitalWrite(PIN_2, HIGH);

  digitalWrite(PIN_3, LOW);
  digitalWrite(PIN_4, HIGH);
}

// motor turn left function
void motorDirectionRight() {
  digitalWrite(PIN_1, HIGH);
  digitalWrite(PIN_2, LOW);

  digitalWrite(PIN_3, LOW);
  digitalWrite(PIN_4, HIGH);
}

// motor turn right function
void motorDirectionLeft() {
  digitalWrite(PIN_1, LOW);
  digitalWrite(PIN_2, HIGH);

  digitalWrite(PIN_3, HIGH);
  digitalWrite(PIN_4, LOW);
}

// motor stop function
void motorStop() {
  digitalWrite(PIN_1, LOW);
  digitalWrite(PIN_2, LOW);

  digitalWrite(PIN_3, LOW);
  digitalWrite(PIN_4, LOW);
}
