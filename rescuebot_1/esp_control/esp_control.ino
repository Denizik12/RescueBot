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

// bot control states
#define CONTROLLED_STATE 5
#define AUTONOMOUS_STATE 6

// serial char array
char serial[10] {0, 0, 0, 0, 0, 1, 0};

// configure wifi
String wifi_ssid = "Tesla IoT";
String wifi_password = "fsL6HgjN";

// esp webserver
ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200);
  server.begin();

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

    server.send(200, "application/json", "{\"message\":\"succesfull\"}");
  });

  server.on("/api/updateMotor", []() {
    int motorState = atoi(server.arg("state").c_str());
    if (motorState == CONTROLLED_STATE) {
      serial[6] = 0;
      Serial.println("bestuurd");
    }
    if (motorState == AUTONOMOUS_STATE) {
      serial[6] = 1;
      Serial.println("autonoom");
    }
    if (motorState == MOTOR_FORWARD_STATE) {
      serial[1] = 1;
    } else {
      serial[1] = 0;
    }
    if (motorState == MOTOR_LEFT_STATE) {
      serial[0] = 1;
    } else {
      serial[0] = 0;
    }
    if (motorState == MOTOR_RIGHT_STATE) {
      serial[3] = 1;
    } else {
      serial[3] = 0;
    }
    if (motorState == MOTOR_BACKWARD_STATE) {
      serial[4] = 1;
    } else {
      serial[4] = 0;
    }
    if (motorState == MOTOR_STOP_STATE) {
      serial[5] = 1;
    } else {
      serial[5] = 0;
    }

    Serial.write(serial, 7);

    server.send(200, "application/json", "{\"message\":\"succesfull\"}");
  });
}

void loop() {
  // keep esp online
  server.handleClient();
}
