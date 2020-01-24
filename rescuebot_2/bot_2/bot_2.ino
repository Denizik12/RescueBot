// ir sensor pins
#define IR_PIN_LEFT A2
#define IR_PIN_RIGHT A0
#define IR_PIN_FRONT A1

// ultrasonic sensor pins
#define TRIG_PIN_LEFT 8
#define ECHO_PIN_LEFT 9
#define TRIG_PIN_RIGHT 10
#define ECHO_PIN_RIGHT 11
#define TRIG_PIN_FRONT 6
#define ECHO_PIN_FRONT 7

// motor pins
#define PIN_1 2
#define PIN_2 3
#define PIN_3 4
#define PIN_4 5

// ir variabels
int irValueLeft = 0;
int irValueRight = 0;
int irValueFront = 0;

// ultra smotorOnic variables
long durationLeft, durationRight, durationFront;
int distanceLeft, distanceRight, distanceFront;

// timer variables
unsigned long previousMillis = 0;
unsigned long previousMillisSecond = 0;

// communication
char serial [10];
boolean manualMode = false;

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

// function to Turn
void turn() {
  unsigned long startMillis = millis();
  // turn 90
  if (startMillis - previousMillis >= 100) {
    irValueFront = digitalRead(IR_PIN_FRONT);
    motorDirectionBackwards();
    delay(350);
    motorDirectionLeft();
    delay(1300);
    motorDirectionForward();
    previousMillis = startMillis;
    // turn 180
    if (irValueFront == 1 && startMillis - previousMillisSecond <= 5000) {
      motorDirectionLeft();
      delay(1750);
      motorDirectionForward();
    } else {
      previousMillis = startMillis;
      previousMillisSecond = startMillis;
    }
  }
}

// front ultrasonic sensor
void ultrasonicFront() {
  // get value front ultrasonic sensor
  digitalWrite(TRIG_PIN_FRONT, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_FRONT, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_FRONT, LOW);
  durationFront = pulseIn(ECHO_PIN_FRONT, HIGH);
  distanceFront = (durationFront / 2) / 29.1; // calculate to cm

  if (distanceFront < 30) {
    motorDirectionLeft();
    delay(400);
  }
}

// left ultrasonic sensor
void ultrasonicLeft() {
  // get value front ultrasonic sensor
  digitalWrite(TRIG_PIN_LEFT, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_LEFT, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_LEFT, LOW);
  durationLeft = pulseIn(ECHO_PIN_LEFT, HIGH);
  distanceLeft = (durationFront / 2) / 29.1; // calculate to cm

  if (distanceLeft < 5) {
    motorDirectionRight();
  }
}

// right ultrasonic sensor
void ultrasonicRight() {
  // get value front ultrasonic sensor
  digitalWrite(TRIG_PIN_RIGHT, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_RIGHT, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_RIGHT, LOW);
  durationRight = pulseIn(ECHO_PIN_RIGHT, HIGH);
  distanceRight = (durationRight / 2) / 29.1; // calculate to cm

  if (distanceRight < 5) {
    motorDirectionLeft();
  }
}

void setup() {
  Serial.begin(115200);

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
}

void loop() {
  // serial communication
  if (Serial.available() > 0) {

    Serial.readBytes(serial, 7);

    // switch between manualMode and autonomous
    if (serial[6] == 0)    {
      manualMode = true;
    }
    if (serial[6] == 1)   {
      manualMode = false;
    }
  }

  // get the bytes from esp if manualMode is on
  if (manualMode == true) {

    if (serial[1] == 1) {
      motorDirectionForward();
    }
    if (serial[0] == 1) {
      motorDirectionLeft();
    }
    if (serial[3] == 1) {
      motorDirectionRight();
    }
    if (serial[4] == 1) {
      motorDirectionBackwards();
    }
    if (serial[5] == 1) {
      motorStop();
    }
  }

  // if manual mode is off drive autonomous
  if (manualMode == false) {

    // ultrasonic sensors
    ultrasonicFront();
    ultrasonicRight();
    ultrasonicLeft();

    // get values from ir sensor
    irValueLeft = digitalRead(IR_PIN_LEFT);
    irValueRight = digitalRead(IR_PIN_RIGHT);
    irValueFront = digitalRead(IR_PIN_FRONT);

    // if else for bot driving
    if (irValueLeft == 0 && irValueRight == 0 && irValueFront == 0) {
      motorDirectionForward();
    } else if (irValueLeft == 1 && irValueRight == 0 && irValueFront == 0) {
      motorDirectionRight();
    } else if (irValueLeft == 0 && irValueRight == 1 && irValueFront == 0) {
      motorDirectionLeft();
    } else if (irValueFront == 1) {
      turn();
    }
  }
}
