// ir pins
#define IR_PIN_LEFT 8
#define IR_PIN_RIGHT 7
#define IR_PIN_FRONT 6

// ultrasomotorOn sensor pins
#define TRIG_PIN_LEFT 12
#define ECHO_PIN_LEFT 11
#define TRIG_PIN_RIGHT 9
#define ECHO_PIN_RIGHT 10
#define TRIG_PIN_FRONT 23
#define ECHO_PIN_FRONT 22

// ir variabels
int valueLeftSide = 0;
int valueRightSide = 0;
int valueFrontSide = 0;

// ultra smotorOnic variables
long durationLeft = 0;
int distanceLeft = 0;
long durationRight = 0;
int distanceRight = 0;
long durationFront = 0;
int distanceFront = 0;

#define PIN_1 2
#define PIN_2 3
#define PIN_3 4
#define PIN_4 5

unsigned long previousMillis = 0;
unsigned long previousMillisSecond = 0;

// motor forward functimon
void motorDirectionBackwards() {
  digitalWrite(PIN_1, HIGH);
  digitalWrite(PIN_2, LOW);

  digitalWrite(PIN_3, HIGH);
  digitalWrite(PIN_4, LOW);
}

// motor backwards function
void motorDirectionForward() {
  digitalWrite(PIN_1, LOW);
  digitalWrite(PIN_2, HIGH);

  digitalWrite(PIN_3, LOW);
  digitalWrite(PIN_4, HIGH);
}

// motor turn right function
void motorDirectionRight() {
  digitalWrite(PIN_1, HIGH);
  digitalWrite(PIN_2, LOW);

  digitalWrite(PIN_3, LOW);
  digitalWrite(PIN_4, HIGH);
}

// motor turn left function
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

void setup() {
  Serial.begin(9600);
  pinMode(PIN_1, OUTPUT);
  pinMode(PIN_2, OUTPUT);
  pinMode(PIN_3, OUTPUT);
  pinMode(PIN_4, OUTPUT);

  pinMode(IR_PIN_LEFT, INPUT);
  pinMode(IR_PIN_RIGHT, INPUT);

  pinMode(TRIG_PIN_LEFT, OUTPUT);
  pinMode(ECHO_PIN_LEFT, INPUT);
  pinMode(TRIG_PIN_RIGHT, OUTPUT);
  pinMode(ECHO_PIN_RIGHT, INPUT);
  pinMode(TRIG_PIN_FRONT, OUTPUT);
  pinMode(ECHO_PIN_FRONT, INPUT);
}

void loop() {
  valueLeftSide = digitalRead(IR_PIN_LEFT);
  valueRightSide = digitalRead(IR_PIN_RIGHT);
  valueFrontSide = digitalRead(IR_PIN_FRONT);

 digitalWrite(TRIG_PIN_FRONT, LOW);
 delayMicroseconds(2);
 digitalWrite(TRIG_PIN_FRONT, HIGH);
 delayMicroseconds(10);
 digitalWrite(TRIG_PIN_FRONT, LOW);

 durationFront = pulseIn(ECHO_PIN_FRONT, HIGH);
 distanceFront = (durationFront / 2) / 29.1;

 digitalWrite(TRIG_PIN_LEFT, LOW);
 delayMicroseconds(2);
 digitalWrite(TRIG_PIN_LEFT, HIGH);
 delayMicroseconds(10);
 digitalWrite(TRIG_PIN_LEFT, LOW);

 durationLeft = pulseIn(ECHO_PIN_LEFT, HIGH);
 distanceLeft = (durationLeft / 2) / 29.1;;

 digitalWrite(TRIG_PIN_RIGHT, LOW);
 delayMicroseconds(2);
 digitalWrite(TRIG_PIN_RIGHT, HIGH);
 delayMicroseconds(10);
 digitalWrite(TRIG_PIN_RIGHT, LOW);

 durationRight = pulseIn(ECHO_PIN_RIGHT, HIGH);
 distanceRight = (durationRight / 2) / 29.1;

  Serial.print("left ultra: ");
  Serial.println(distanceLeft);
  Serial.print("right ultra: ");
  Serial.println(distanceRight);
  Serial.print("front ultra: ");
  Serial.println(distanceFront);

  if (valueLeftSide == 0 && valueRightSide == 0 && valueFrontSide == 0) {
    motorDirectionForward();
  } else if (valueLeftSide == 1 && valueRightSide == 0 && valueFrontSide == 0) {
    motorDirectionRight();
  } else if (valueLeftSide == 0 && valueRightSide == 1 && valueFrontSide == 0) {
    motorDirectionLeft();
  } else if (valueFrontSide == 1) {
    turn();
  } else {
    motorStop();
  }

 if (distanceRight > 12 && distanceLeft > 12) {
   motorDirectionForward();

 } else if (distanceRight < 12) {
   motorDirectionLeft();

 } else if (distanceFront < 20) {
   motorDirectionRight();
   delay(500);

 } else if (distanceRight < 12 && distanceLeft < 12) {
   motorDirectionForward();

 } else if (distanceLeft < 12) {
   motorDirectionRight();

 } else {
   motorStop();
 }
}

// function to Turn
void turn() {
  unsigned long startMillis = millis();
  // turn 90
  if (startMillis - previousMillis >= 100) {
    valueFrontSide = digitalRead(IR_PIN_FRONT);
    motorDirectionBackwards();
    delay(500);
    motorDirectionLeft();
    delay(1750);
    motorDirectionForward();
    previousMillis = startMillis;
    // turn 180
    if (valueFrontSide == 1 && startMillis - previousMillisSecond <= 5000) {
      motorDirectionLeft();
      delay(2000);
      motorDirectionForward();
    } else {
      previousMillis = startMillis;
      previousMillisSecond = startMillis;
    }
  }
}
