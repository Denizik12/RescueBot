// ir sensor pins
#define IR_PIN_LEFT_FRONT A0
#define IR_PIN_RIGHT_FRONT A1
#define IR_PIN_LEFT_SIDE A2
#define IR_PIN_RIGHT_SIDE A3

// ir sensor values
int valueLeftSideFront = 0;
int valueRightSideFront = 0;
int valueLeftSide = 0;
int valueRightSide = 0;

// h-bridge module pins
#define PIN_1 2
#define PIN_2 3
#define PIN_3 4
#define PIN_4 5

void setup() {
  Serial.begin(9600);
  pinMode(IR_PIN_LEFT_FRONT, INPUT);
  pinMode(IR_PIN_RIGHT_FRONT, INPUT);
  pinMode(IR_PIN_LEFT_SIDE, INPUT);
  pinMode(IR_PIN_RIGHT_SIDE, INPUT);
}

void loop() {

  valueLeftSideFront = digitalRead(IR_PIN_LEFT_FRONT);
  valueRightSideFront = digitalRead(IR_PIN_RIGHT_FRONT);
  valueLeftSide = digitalRead(IR_PIN_LEFT_SIDE);
  valueRightSide = digitalRead(IR_PIN_RIGHT_SIDE);

  // if all sensors detect nothing go forward
  if (valueLeftSideFront == 0 && valueRightSideFront == 0 && valueLeftSide == 0 && valueRightSide == 0) {
    motorDirectionForward();

  } else if (valueRightSideFront == 1 && valueLeftSideFront == 0 && valueLeftSide == 0 && valueRightSide == 0) {
    motorDirectionLeft();

  } else if (valueRightSideFront == 0 && valueLeftSideFront == 0 && valueLeftSide == 0 && valueRightSide == 1) {
    motorDirectionLeft();

  } else if (valueRightSideFront == 1 && valueLeftSideFront == 0 && valueLeftSide == 0 && valueRightSide == 1) {
    motorDirectionLeft();

  } else if (valueRightSideFront == 1 && valueLeftSideFront == 1 && valueLeftSide == 0 && valueRightSide == 1) {
    motorDirectionLeft();

  } else if (valueRightSideFront == 1 && valueLeftSideFront == 1 && valueLeftSide == 1 && valueRightSide == 0) {
    motorDirectionRight();

  } else if (valueRightSideFront == 0 && valueLeftSideFront == 1 && valueLeftSide == 1 && valueRightSide == 0) {
    motorDirectionRight();

  } else if (valueRightSideFront == 0 && valueLeftSideFront == 1 && valueLeftSide == 0 && valueRightSide == 0) {
    motorDirectionRight();

  } else if (valueRightSideFront == 0 && valueLeftSideFront == 0 && valueLeftSide == 1 && valueRightSide == 0) {
    motorDirectionRight();

  } else if (valueLeftSide == 1 && valueRightSide == 1 && valueLeftSideFront == 1 && valueRightSideFront == 1) {
    motorStop();
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
