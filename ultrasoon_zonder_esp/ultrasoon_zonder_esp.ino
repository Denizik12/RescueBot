int trigPinLinks = 13;
int echoPinLinks = 12;
int trigPinRechts = 8;
int echoPinRechts = 9;
int trigPinVoor = 10;
int echoPinVoor = 11;

long durationVoor;
int distanceVoor;
long durationLinks;
int distanceLinks;
long durationRechts;
int distanceRechts;

#define PIN_1 2
#define PIN_2 3
#define PIN_3 4
#define PIN_4 5

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
void motorDirectionLeft() {
  digitalWrite(PIN_1, HIGH);
  digitalWrite(PIN_2, LOW);

  digitalWrite(PIN_3, LOW);
  digitalWrite(PIN_4, HIGH);
}

// motor turn right function
void motorDirectionRight() {
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

void setup() {
  Serial.begin(9600);
  pinMode(PIN_1, OUTPUT);
  pinMode(PIN_2, OUTPUT);
  pinMode(PIN_3, OUTPUT);
  pinMode(PIN_4, OUTPUT);

  pinMode(trigPinLinks, OUTPUT);
  pinMode(echoPinLinks, INPUT);

  pinMode(trigPinRechts, OUTPUT);
  pinMode(echoPinRechts, INPUT);

  pinMode(trigPinVoor, OUTPUT);
  pinMode(echoPinVoor, INPUT);
}

void loop() {
  digitalWrite(trigPinVoor, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinVoor, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinVoor, LOW);

  durationVoor = pulseIn(echoPinVoor, HIGH);
  distanceVoor = durationVoor * 0.034 / 2;

  Serial.print("Distance Voor: ");
  Serial.println(distanceVoor);


  digitalWrite(trigPinLinks, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinLinks, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinLinks, LOW);

  durationLinks = pulseIn(echoPinLinks, HIGH);
  distanceLinks = durationLinks * 0.034 / 2;

  Serial.print("Distance Links: ");
  Serial.println(distanceLinks);

  digitalWrite(trigPinRechts, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinRechts, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinRechts, LOW);

  durationRechts = pulseIn(echoPinRechts, HIGH);
  distanceRechts = durationRechts * 0.034 / 2;

  Serial.print("Distance Rechts: ");
  Serial.println(distanceRechts);

  if (distanceVoor > 20 && distanceRechts > 20 && distanceLinks > 20 ) {
    motorDirectionForward();

  } else if (distanceVoor < 15 && distanceLinks < 15) {
    motorDirectionLeft();

  } else if (distanceVoor < 15 && distanceRechts < 15) {
    motorDirectionRight();

  } else if (distanceLinks < 15 && distanceRechts < 15) {
    motorDirectionForward();

  } else if (distanceVoor < 15) {
    motorDirectionRight();

  } else if (distanceRechts < 15) {
    motorDirectionLeft();

  } else if (distanceLinks < 15) {
    motorDirectionRight();

  } else {
    motorStop();
    delay(500);
    motorDirectionRight();
    delay(1000);
  }
}
