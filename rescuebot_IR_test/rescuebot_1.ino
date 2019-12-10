#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

// wifi login
const char *ssid = "";
const char *password = "";

// motor enable pins
int motorEnablePinLeftBack = D1;  //Nodemcu PWM pin
int motorEnablePinRightBack = D2; //Nodemcu PWM pin

//motor direction pins
int motorForwardPin1 = 15;
int motorBackwardPin1 = 13;
int motorForwardPin2 = 12;
int motorBackwardPin2 = 14;

//IR_sensor pins
int IR_left = 2;
int IR_right = 3;
int IR_front = 4;

// server
WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  delay(10);

  // set mode direction pins
  pinMode(motorForwardPin1, OUTPUT);
  pinMode(motorBackwardPin1, OUTPUT);
  pinMode(motorForwardPin2, OUTPUT);
  pinMode(motorBackwardPin2, OUTPUT);

  //set pinmode IR-sensors
  pinMode(IR_left, INPUT_PULLUP);
  pinMode(IR_right, INPUT_PULLUP);
  pinMode(IR_front, INPUT_PULLUP);

  // connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // forward the server
  server.begin();
  Serial.println("Server forwarded");
  Serial.print(WiFi.localIP());
}

void loop()
{
  // check if client connected
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }

  // wait until the client sends data
  Serial.println("new client");
  while (!client.available())
  {
    delay(10);
  }

  // read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  int motorOn = 0;
  int directionMotor = 0;
  int left = 0;
  int right = 0;

  //parameters om te checken of de robot kan rijden
  int block_forward = 0;
  int block_right = 0;
  int block_left = 0;
  
  //check if the robot can drive to the left
  if(digitalRead(IR_left) == 1)
  {
    block_left = 1;
  }
  else
    block_left = 0;

  //checkl if the robot can drive to the right
  if(digitalRead(IR_right) == 1)
  {
    block_right = 1;
  }
  else
    block_right = 0;
    
  //check if the robot can drive forward
  if(digitalRead(IR_forward) == 1)
  {
    block_forward = 1;
  }
  else
    block_forward = 0;
  

  // forward direction motor
  if (request.indexOf("/forward=1") != -1 && block_forward != 1)
  {
    digitalWrite(motorForwardPin1, HIGH);
    digitalWrite(motorBackwardPin1, LOW);
    digitalWrite(motorForwardPin2, HIGH);
    digitalWrite(motorBackwardPin2, LOW);
    motorOn = 1;
    directionMotor = 1;
  }

  // backwards direction motor
  if (request.indexOf("/backward=1") != -1)
  {
    digitalWrite(motorForwardPin1, LOW);
    digitalWrite(motorBackwardPin1, HIGH);
    digitalWrite(motorForwardPin2, LOW);
    digitalWrite(motorBackwardPin2, HIGH);
    motorOn = 1;
  }

  // left direction motor
  if (request.indexOf("/left=1") != -1 && block_left != 1)
  {
    digitalWrite(motorForwardPin1, LOW);
    digitalWrite(motorBackwardPin1, HIGH);
    digitalWrite(motorForwardPin2, HIGH);
    digitalWrite(motorBackwardPin2, LOW);
    motorOn = 1;
    left = 1;
  }

  // right direction motor
  if (request.indexOf("/right=1") != -1 && block_right != 1)
  {
    digitalWrite(motorForwardPin1, HIGH);
    digitalWrite(motorBackwardPin1, LOW);
    digitalWrite(motorForwardPin2, LOW);
    digitalWrite(motorBackwardPin2, HIGH);
    motorOn = 1;
    right = 1;
  }

  // stop motor
  if (request.indexOf("/stop=1") != -1)
  {
    digitalWrite(motorForwardPin1, LOW);
    digitalWrite(motorBackwardPin1, LOW);
    digitalWrite(motorForwardPin2, LOW);
    digitalWrite(motorBackwardPin2, LOW);
    motorOn = 0;
  }

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<h1 align=center> RescueBot 1 </h1><br><br>");
  client.println("<br><br>");
  client.println("<a href=\"/forward=1\"\"><button> forward </button></a><br/>");
  client.println("<a href=\"/backward=1\"\"><button> backward </button></a><br/>");
  client.println("<a href=\"/left=1\"\"><button> left </button></a><br/>");
  client.println("<a href=\"/right=1\"\"><button> right </button></a><br/>");
  client.println("<a href=\"/stop=1\"\"><button> stop </button></a><br/>");

  if (motorOn == 1)
  {
    client.println("Motor powered<br/>");
  }
  else
    client.println("Motor halt<br/>");

  if (left == 1)
  {
    client.println("turning left<br/>");
  }
  else
    client.println("not turning left<br/>");

  if (right == 1)
  {
    client.println("turning right<br/>");
  }
  else
    client.println("not turning right<br/>");

  if (directionMotor == 1)
  {
    client.println("Motor rotating in forward direction<br/>");
  }
  else
    client.println("Motor rotating in backward direction<br/>");

  client.println("</html>");
  delay(10);
  Serial.println("Client disonnected");
  Serial.println("");
}
