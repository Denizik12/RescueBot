// ir sensor
#define IR_PIN_LEFT 8
#define IR_PIN_RIGHT 7
#define IR_PIN_FRONT 6

// front leds
#define LED_LEFT 45
#define LED_RIGHT 44

// reed switches
#define REED_PIN_FRONT A1
#define REED_PIN_LEFT A2
#define REED_PIN_RIGHT A3

// ultrasomotorOn sensor
#define TRIG_PIN_LEFT 13
#define ECHO_PIN_LEFT 12
#define TRIG_PIN_RIGHT 11
#define ECHO_PIN_RIGHT 10
#define TRIG_PIN_FRONT 40
#define ECHO_PIN_FRONT 42

// ldr sensor
#define LDR_PIN A0

// motor pins
#define PIN_1 2
#define PIN_2 3
#define PIN_3 4
#define PIN_4 5

// reed switch variable
int reedValueFront = 0;
int reedValueLeft = 0;
int reedValueRight = 0;

// ir variabels
int irValueLeft = 0;
int irValueRight = 0;
int irValueFront = 0;

// ultra smotorOnic variables
long durationLeft;
int distanceLeft;
long durationRight;
int distanceRight;
long durationFront;
int distanceFront;

// interrupt variables
const byte interruptPin = 2;
volatile int tunnelState;

// timer
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

// interrupt voor tunnel
void tunnel() {
  tunnelState = 1;
}

// function to Turn
void turn() {
  unsigned long startMillis = millis();
  // turn 90
  if (startMillis - previousMillis >= 100) {
    irValueFront = digitalRead(IR_PIN_FRONT);
    motorDirectionBackwards();
    delay(600);
    motorDirectionLeft();
    delay(1800);
    motorDirectionForward();
    previousMillis = startMillis;
    // turn 180
    if (irValueFront == 1 && startMillis - previousMillisSecond <= 5000) {
      motorDirectionLeft();
      delay(2000);
      motorDirectionForward();
    } else {
      previousMillis = startMillis;
      previousMillisSecond = startMillis;
    }
  }
}

// function that executes when interrupt is triggered
void ultraSonicTunnel() {
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

  if (distanceRight < 12) {
    motorDirectionLeft();
  } else if (distanceLeft < 12) {
    motorDirectionRight();
  } else if (distanceRight > 12 && distanceLeft > 12) {
    motorDirectionForward();
  }
}

// front ultrasonic sensor
void ultraSonicFront() {
  // front ultrasonic sensor
  digitalWrite(TRIG_PIN_FRONT, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_FRONT, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_FRONT, LOW);
  durationFront = pulseIn(ECHO_PIN_FRONT, HIGH);
  distanceFront = (durationFront / 2) / 29.1;

  if (distanceFront < 20) {
    obstacle();
  }
}

// obstacle avoid
void obstacle() {
  unsigned long startMillis = millis();
  // turn 90 right
  if (startMillis - previousMillis >= 100) {
    irValueFront = digitalRead(IR_PIN_FRONT);
    motorStop();
    delay(100);
    motorDirectionRight();
    delay(1500);
    motorDirectionForward();
    previousMillis = startMillis;
    // turn 90 left
    if (irValueFront == 1 && startMillis - previousMillisSecond <= 5000) {
      motorStop();
      delay(100);
      motorDirectionLeft();
      delay(1500);
      motorDirectionForward();
    } else {
      previousMillis = startMillis;
      previousMillisSecond = startMillis;
    }
  }
}

void setup() {
  Serial.begin(9600);
  // reed pin modes
  pinMode(REED_PIN_FRONT, INPUT);
  pinMode(REED_PIN_LEFT, INPUT);
  pinMode(REED_PIN_RIGHT, INPUT);

  // led pin modes
  pinMode(LED_LEFT, OUTPUT);
  pinMode(LED_RIGHT, OUTPUT);

  // motor pin modes
  pinMode(PIN_1, OUTPUT);
  pinMode(PIN_2, OUTPUT);
  pinMode(PIN_3, OUTPUT);
  pinMode(PIN_4, OUTPUT);

  // ir pin modes
  pinMode(IR_PIN_LEFT, INPUT);
  pinMode(IR_PIN_RIGHT, INPUT);

  // ultrasoon pin modes
  pinMode(TRIG_PIN_LEFT, OUTPUT);
  pinMode(ECHO_PIN_LEFT, INPUT);
  pinMode(TRIG_PIN_RIGHT, OUTPUT);
  pinMode(ECHO_PIN_RIGHT, INPUT);
  pinMode(TRIG_PIN_FRONT, OUTPUT);
  pinMode(ECHO_PIN_FRONT, INPUT);

  // interrupt pin mode
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), tunnel, FALLING);
}

void loop() {
  // when ldr is high
  if (digitalRead(LDR_PIN) == 1) {
    // Serial.println(digitalRead(LDR_PIN));
    digitalWrite(LED_LEFT, LOW);
    digitalWrite(LED_RIGHT, LOW);

    // get values from ir sensor
    irValueLeft = digitalRead(IR_PIN_LEFT);
    irValueRight = digitalRead(IR_PIN_RIGHT);
    irValueFront = digitalRead(IR_PIN_FRONT);

    // get value reed switch
    reedValueFront = digitalRead(REED_PIN_FRONT);
    reedValueLeft = digitalRead(REED_PIN_LEFT);
    reedValueRight = digitalRead(REED_PIN_RIGHT);

    // ultrasonic sensors
    ultraSonicTunnel();
    ultraSonicFront();

    // if else for bot driving
    if (irValueLeft == 0 && irValueRight == 0 && irValueFront == 0) {
      // Serial.println("voor uit");
      motorDirectionForward();
    } else if (irValueLeft == 1 && irValueRight == 0 && irValueFront == 0) {
      // Serial.println("rechts");
      motorDirectionRight();
    } else if (irValueLeft == 0 && irValueRight == 1 && irValueFront == 0) {
      // Serial.println("links");
      motorDirectionLeft();
    } else if (irValueFront == 1) {
      // Serial.println("90 draai");
      turn();
    } else if (reedValueFront == 1 || reedValueLeft == 1 || reedValueRight == 1) {
      motorStop();
      Serial.println("stop");
    }

    // when ldr is low
  } else if (digitalRead(LDR_PIN) == 0) {
    // Serial.println(digitalRead(LDR_PIN));
    digitalWrite(LED_LEFT, HIGH);
    digitalWrite(LED_RIGHT, HIGH);
    ultraSonicTunnel();
  }
}
