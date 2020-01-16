#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "controls.h"

bool autoControl;

// motor server states
#define MOTOR_STOP_STATE 0
#define MOTOR_FORWARD_STATE 1
#define MOTOR_BACKWARD_STATE 2
#define MOTOR_LEFT_STATE 3
#define MOTOR_RIGHT_STATE 4

// left side pins
#define PIN_1 D1
#define PIN_2 D2
#define PIN_3 D3
#define PIN_4 D4


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

// configure wifi
String wifi_ssid = "";
String wifi_password = "";
// Tesla IoT fsL6HgjN

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  server.begin();

  pinMode(PIN_1, OUTPUT);
  pinMode(PIN_2, OUTPUT);
  pinMode(PIN_3, OUTPUT);
  pinMode(PIN_4, OUTPUT);

  // connect to wifi
  Serial.print("Connecting to ");
  Serial.print(wifi_ssid);
  Serial.println("...");
  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println("WIFI connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    server.send(200, "text/html", controlsHtml);
  });

  server.on("/api/updateAuto", []() {
      if (server.arg("auto") == "true") {
        autoControl = true;
      } else{
        autoControl = false;
      }  
  });

  server.on("/api/updateMotor", []() {
    int motorState = atoi(server.arg("state").c_str());

    if (motorState == MOTOR_FORWARD_STATE) {
      motorDirectionForward();
    }
    if (motorState == MOTOR_LEFT_STATE) {
      motorDirectionLeft();
    }
    if (motorState == MOTOR_RIGHT_STATE) {
      motorDirectionRight();
    }
    if (motorState == MOTOR_BACKWARD_STATE) {
      motorDirectionBackward();
    }
    if (motorState == MOTOR_STOP_STATE) {
      motorStop();
    }

    server.send(200, "application/json", "{\"message\":\"succesfull\"}");
  });
}

void loop() {
  server.handleClient();
}
