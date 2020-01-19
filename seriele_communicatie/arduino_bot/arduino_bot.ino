#include "controls.h"

// left side pins
#define PIN_1 2
#define PIN_2 3
#define PIN_3 4
#define PIN_4 5

char serial[10];

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
  Serial.begin(115200);

  pinMode(PIN_1, OUTPUT);
  pinMode(PIN_2, OUTPUT);
  pinMode(PIN_3, OUTPUT);
  pinMode(PIN_4, OUTPUT);
}

void loop() {

  if (Serial.available() > 0){

    Serial.readBytes(serial,6);

    if (serial[1] == 1) {
      motorDirectionForward();
      Serial.println("vooruit = 1 wordt ontvangen door de arduino");
    }
    if (serial[2] == 1) {
      motorDirectionLeft();
      Serial.println("links = 1 wordt ontvangen door de arduino");
    }
    if (serial[3] == 1) {
      motorDirectionRight();
      Serial.println("recht = 1 wordt ontvangen door de arduino");
    }
    if (serial[4] == 1) {
      motorDirectionBackward();
      Serial.println("achteruit = 1 wordt ontvangen door de arduino");
    }
    if (serial[5] == 1) {
      motorStop();
      Serial.println("stoppen = 1 wordt ontvangen door de arduino");
    }
  }  
}
