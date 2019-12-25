#include "controls.h"

// left side pins
#define PIN_1 2
#define PIN_2 3
#define PIN_3 4
#define PIN_4 5
#define ir_voor 6
#define ir_links 7
#define ir_rechts 8
#define trigPin 9
#define echoPin 10

char serial[10];
float duration, distance;

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
  pinMode(ir_voor, INPUT);
  pinMode(ir_links, INPUT);
  pinMode(ir_rechts, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  int voor = 1-digitalRead(ir_voor);
  int links = 1-digitalRead(ir_links);
  int rechts = 1-digitalRead(ir_rechts);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = (duration / 2) * 0.0343 -1;
  
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
      Serial.println("links = 1 wordt ontvangen door de arduino");
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
    else
    {
    if(voor == LOW)
    {
      motorDirectionBackward();
      Serial.println("De bot keert om"); 
    }
    if(links == LOW)
    {
      motorDirectionRight();
      Serial.println("De bot maakt een bocht naar rechts");
    }
    if(rechts == LOW)
    {
      motorDirectionLeft();
      Serial.println("De bot maakt een bocht naar links");
    }
    if(distance < 5)
    {
      motorDirectionRight();
      Serial.println("De ultrasoon detecteerd iets en de bot gaat naar rechts");
    }
    else
    {
      motorDirectionForward();
      Serial.println("De bot rijdt vooruit");
    }
    
    
   }

  }