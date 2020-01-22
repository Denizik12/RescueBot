// ir sensor
#define IR_PIN_LEFT 12
#define IR_PIN_RIGHT A0
#define IR_PIN_FRONT 13

// ultrasomotorOn sensor
#define TRIG_PIN_LEFT 10
#define ECHO_PIN_LEFT 11
#define TRIG_PIN_RIGHT 9
#define ECHO_PIN_RIGHT 8
#define TRIG_PIN_FRONT 7
#define ECHO_PIN_FRONT 6

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
long durationLeft;
int distanceLeft;
long durationRight;
int distanceRight;
long durationFront;
int distanceFront;

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

// function to Turn
void turn() {
  unsigned long startMillis = millis();
  // turn 90
  if (startMillis - previousMillis >= 100) {
    irValueFront = digitalRead(IR_PIN_FRONT);
    motorDirectionBackwards();
    delay(500);
    motorDirectionLeft();
    delay(1000);
    motorDirectionForward();
    previousMillis = startMillis;
    // turn 180
    if (irValueFront == 1 && startMillis - previousMillisSecond <= 5000) {
      motorDirectionLeft();
      delay(1500);
      motorDirectionForward();
    } else {
      previousMillis = startMillis;
      previousMillisSecond = startMillis;
    }
  }
}

void ultrasonicFront() {
  // get value front ultrasonic sensor
  digitalWrite(TRIG_PIN_FRONT, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_FRONT, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_FRONT, LOW);
  durationFront = pulseIn(ECHO_PIN_FRONT, HIGH);
  distanceFront = (durationFront / 2) / 29.1;
  //Serial.println(distanceFront);

  if (distanceFront < 30) {
    Serial.println("obstakel");
    motorDirectionLeft();
    delay(250);
  } 
}

void setup() {
  Serial.begin(9600);

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
  // front ultrasonic
  ultrasonicFront();

  // get value right ultrasonic sensor
  digitalWrite(TRIG_PIN_RIGHT, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_RIGHT, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_RIGHT, LOW);

  durationRight = pulseIn(ECHO_PIN_RIGHT, HIGH);
  distanceRight = (durationRight / 2) / 29.1;

  if (distanceRight < 15) {
    Serial.println("draai links");
    motorDirectionLeft();
  }

  // get value left ultrasonic sensor
  digitalWrite(TRIG_PIN_LEFT, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_LEFT, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_LEFT, LOW);

  durationLeft = pulseIn(ECHO_PIN_LEFT, HIGH);
  distanceLeft = (durationLeft / 2) / 29.1;

  if (distanceLeft < 15) {
    Serial.println("draai rechts");
    motorDirectionRight();
  }

  // get values from ir sensor
  irValueLeft = digitalRead(IR_PIN_LEFT);
  irValueRight = digitalRead(IR_PIN_RIGHT);
  irValueFront = digitalRead(IR_PIN_FRONT);

  // if else for bot driving
  if (irValueLeft == 0 && irValueRight == 0 && irValueFront == 0) {
    Serial.println("voor uit");
    motorDirectionForward();
  } else if (irValueLeft == 1 && irValueRight == 0 && irValueFront == 0) {
    //Serial.println("rechts");
    motorDirectionRight();
  } else if (irValueLeft == 0 && irValueRight == 1 && irValueFront == 0) {
    //Serial.println("links");
    motorDirectionLeft();
  } else if (irValueFront == 1) {
    Serial.println("90 draai");
    turn();
  }
}
