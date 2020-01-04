// ultrasoon sensor pins
#define TRIG_PIN_LEFT 8
#define ECHO_PIN_LEFT 9
#define TRIG_PIN_RIGHT 10
#define ECHO_PIN_RIGHT 11
#define TRIG_PIN_FRONT 12
#define ECHO_PIN_FRONT 13

long durationVoor = 0;
int distanceVoor = 0;
long durationLinks = 0;
int distanceLinks = 0;
long durationRechts = 0;
int distanceRechts = 0;

// motor pins
#define PIN_1 2
#define PIN_2 3
#define PIN_3 4
#define PIN_4 5

void setup() {
  Serial.begin(9600);
  pinMode(PIN_1, OUTPUT);
  pinMode(PIN_2, OUTPUT);
  pinMode(PIN_3, OUTPUT);
  pinMode(PIN_4, OUTPUT);

  pinMode(TRIG_PIN_LEFT, OUTPUT);
  pinMode(ECHO_PIN_LEFT, INPUT);
  pinMode(TRIG_PIN_RIGHT, OUTPUT);
  pinMode(ECHO_PIN_RIGHT, INPUT);
  pinMode(TRIG_PIN_FRONT, OUTPUT);
  pinMode(ECHO_PIN_FRONT, INPUT);
}

void loop() {
  digitalWrite(TRIG_PIN_FRONT, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_FRONT, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_FRONT, LOW);

  durationVoor = pulseIn(ECHO_PIN_FRONT, HIGH);
  distanceVoor = (durationVoor / 2) / 29.1;;
  Serial.print("voor: ");
  Serial.println(distanceVoor);

  digitalWrite(TRIG_PIN_LEFT, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_LEFT, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_LEFT, LOW);

  durationLinks = pulseIn(ECHO_PIN_LEFT, HIGH);
  distanceLinks = (durationLinks / 2) / 29.1;;
  Serial.print("links: ");
  Serial.println(distanceLinks);

  digitalWrite(TRIG_PIN_RIGHT, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_RIGHT, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_RIGHT, LOW);

  durationRechts = pulseIn(ECHO_PIN_RIGHT, HIGH);
  distanceRechts = (durationRechts / 2) / 29.1;
  Serial.print("rechts: ");
  Serial.println(distanceRechts);

  if (distanceVoor > 20 && distanceRechts > 20 && distanceLinks > 20 && valueLeft == 0 && valueRight == 0) {
    motorDirectionForward();

  } else if (distanceVoor <= 20 && distanceLinks <= 20 && valueLeft == 0 && valueRight == 1) {
    motorDirectionLeft();

  } else if (distanceVoor <= 20 && distanceRechts <= 20 && valueLeft == 1 && valueRight == 0) {
    motorDirectionRight();

  } else if (distanceLinks <= 20 && distanceRechts <= 20) {
    motorDirectionForward();

  } else if (distanceVoor <= 20) {
    motorDirectionLeft();

  } else if (distanceRechts <= 20) {
    motorDirectionRight();

  } else if (distanceLinks <= 20) {
    motorDirectionLeft();

  } else {
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
