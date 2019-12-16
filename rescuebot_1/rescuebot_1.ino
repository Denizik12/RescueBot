#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "controls.h"

// motor server states
#define MOTOR_STOP_STATE 0
#define MOTOR_FORWARD_STATE 1
#define MOTOR_BACKWARD_STATE 2
#define MOTOR_LEFT_STATE 3
#define MOTOR_RIGHT_STATE 4

// left side pins
#define FORWARD_LEFT_PIN D0
#define BACKWARD_LEFT_PIN D1
#define ENABLE_LEFT_PIN D2

// right side pins
#define FORWARD_RIGHT_PIN D3
#define BACKWARD_RIGHT_PIN D4
#define ENABLE_RIGHT_PIN D5

// motor forward function
void motorDirectionForward() {
  digitalWrite(FORWARD_LEFT_PIN, HIGH);
  digitalWrite(BACKWARD_LEFT_PIN, LOW);
  digitalWrite(ENABLE_LEFT_PIN, HIGH);

  digitalWrite(FORWARD_RIGHT_PIN, HIGH);
  digitalWrite(BACKWARD_RIGHT_PIN, LOW);
  digitalWrite(ENABLE_RIGHT_PIN, HIGH);
}

// motor backwards function
void motorDirectionBackward() {
  digitalWrite(FORWARD_LEFT_PIN, LOW);
  digitalWrite(BACKWARD_LEFT_PIN, HIGH);
  digitalWrite(ENABLE_LEFT_PIN, HIGH);

  digitalWrite(FORWARD_RIGHT_PIN, LOW);
  digitalWrite(BACKWARD_RIGHT_PIN, HIGH);
  digitalWrite(ENABLE_RIGHT_PIN, HIGH);
}

// motor turn left function
void motorDirectionLeft() {
  digitalWrite(FORWARD_LEFT_PIN, LOW);
  digitalWrite(BACKWARD_LEFT_PIN, HIGH);
  digitalWrite(ENABLE_LEFT_PIN, HIGH);

  digitalWrite(FORWARD_RIGHT_PIN, HIGH);
  digitalWrite(BACKWARD_RIGHT_PIN, LOW);
  digitalWrite(ENABLE_RIGHT_PIN, HIGH);
}

// motor turn right function
void motorDirectionRight() {
  digitalWrite(FORWARD_LEFT_PIN, HIGH);
  digitalWrite(BACKWARD_LEFT_PIN, LOW);
  digitalWrite(ENABLE_LEFT_PIN, HIGH);

  digitalWrite(FORWARD_RIGHT_PIN, LOW);
  digitalWrite(BACKWARD_RIGHT_PIN, HIGH);
  digitalWrite(ENABLE_RIGHT_PIN, HIGH);
}

// motor stop function
void motorStop() {
  digitalWrite(ENABLE_LEFT_PIN, LOW);
  digitalWrite(ENABLE_RIGHT_PIN, LOW);
}

// configure wifi
String wifi_ssid = "";
String wifi_password = "";
// Tesla IoT fsL6HgjN

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  server.begin();

  pinMode(FORWARD_LEFT_PIN, OUTPUT);
  pinMode(BACKWARD_LEFT_PIN, OUTPUT);
  pinMode(ENABLE_LEFT_PIN, OUTPUT);

  pinMode(FORWARD_RIGHT_PIN, OUTPUT);
  pinMode(BACKWARD_RIGHT_PIN, OUTPUT);
  pinMode(ENABLE_RIGHT_PIN, OUTPUT);

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
