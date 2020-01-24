// ir sensor
#define IR_PIN_LEFT A2
#define IR_PIN_RIGHT A0
#define IR_PIN_FRONT A1

// ultrasomotorOn sensor
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
long durationLeft;
int distanceLeft;
long durationRight;
int distanceRight;
long durationFront;
int distanceFront;

// timer
unsigned long previousMillis = 0;
unsigned long previousMillisSecond = 0;

char serial [10];
boolean man = false;

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
    //Serial.println("obstakel");
    motorDirectionLeft();
    delay(500);
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
    if (Serial.available() > 0) {
    Serial.readBytes(serial, 7);
    if(serial[6] == 0) 
    {
      man = true;
    }
    if(serial[6] == 1)
    {
      man = false;
    }
  }
  if (man == true)
  {
    //Serial.println("de auto wordt bestuurd");

    if (serial[1] == 1) {
      motorDirectionForward();
      //Serial.println("vooruit = 1 wordt ontvangen door de arduino");
    }
    if (serial[0] == 1) {
      motorDirectionLeft();
      //Serial.println("links = 1 wordt ontvangen door de arduino");
    }
    if (serial[3] == 1) {
      motorDirectionRight();
      //Serial.println("rechts = 1 wordt ontvangen door de arduino");
    }
    if (serial[4] == 1) {
      motorDirectionBackwards();
      //Serial.println("achteruit = 1 wordt ontvangen door de arduino");
    }
    if (serial[5] == 1) {
      motorStop();
      //Serial.println("stoppen = 1 wordt ontvangen door de arduino");
    }
  } 
  if (man == false)
  { 
    //Serial.println("auto rijdt autonoom"); 
  // get value right ultrasonic sensor
  digitalWrite(TRIG_PIN_RIGHT, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN_RIGHT, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN_RIGHT, LOW);

  durationRight = pulseIn(ECHO_PIN_RIGHT, HIGH);
  distanceRight = (durationRight / 2) / 29.1;

  if (distanceRight < 5) {
    //Serial.println("draai links");
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

  if (distanceLeft < 5) {
    //Serial.println("draai rechts");
    motorDirectionRight();
  }

  // front ultrasonic
  ultrasonicFront();

  // get values from ir sensor
  irValueLeft = digitalRead(IR_PIN_LEFT);
  irValueRight = digitalRead(IR_PIN_RIGHT);
  irValueFront = digitalRead(IR_PIN_FRONT);

  // if else for bot driving
  if (irValueLeft == 0 && irValueRight == 0 && irValueFront == 0) {
    //Serial.println("voor uit");
    motorDirectionForward();
  } else if (irValueLeft == 1 && irValueRight == 0 && irValueFront == 0) {
    //Serial.println("rechts");
    motorDirectionRight();
  } else if (irValueLeft == 0 && irValueRight == 1 && irValueFront == 0) {
    //Serial.println("links");
    motorDirectionLeft();
  } else if (irValueFront == 1) {
    //Serial.println("90 draai");
    turn();
  }
}
}
