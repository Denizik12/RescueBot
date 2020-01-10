/*
-Project 2
-reedswitch om magnetische slachtoffers te detecteren.
-versie 1.0
*/

int reed = 7;

// h-bridge module pins
#define PIN_1 2
#define PIN_2 3
#define PIN_3 4
#define PIN_4 5
#define led 9
void setup() {
  pinMode(led, INPUT);
  pinMode(reed, INPUT);
  pinMode(PIN_1, OUTPUT);
  pinMode(PIN_2, OUTPUT);
  pinMode(PIN_3, OUTPUT);
  pinMode(PIN_4, OUTPUT);

}

void loop() {
  int value = digitalRead(reed);

  if (value == HIGH) {
    digitalWrite(led, HIGH);

    motorDirectionForward();
  } else if (value == LOW) {
    digitalWrite(led, LOW);
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
