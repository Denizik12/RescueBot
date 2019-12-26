int irPinLeft = A1;
int irPinRight = A0;
int valueLeft = 0;
int valueRight = 0;

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
  pinMode(irPinLeft, INPUT);
  pinMode(irPinRight, INPUT);
}

void loop() {
  valueLeft = digitalRead(irPinLeft);
  Serial.print("left: ");
  Serial.println(valueLeft);

  valueRight = digitalRead(irPinRight);
  Serial.print("right: ");
  Serial.println(valueRight);

  if (valueLeft == 0 && valueRight == 0) {
    motorDirectionForward();

  } else if (valueLeft == 1 && valueRight == 0) {
    motorDirectionRight();

  } else if (valueLeft == 0 && valueRight == 1) {
    motorDirectionLeft();

  } else if (valueLeft == 1 && valueRight == 1) {
    motorStop();
  }
}
