#define ENA   14
#define ENB   12
#define IN_1  15
#define IN_2  13
#define IN_3  2
#define IN_4  0

#define IR_LEFT 16
#define IR_RIGHT 5

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

String command;
int speedCar = 200;
int speed_Coeff = 3;
bool autoMode = false;

const char* ssid = "NodeMCU_Car";
ESP8266WebServer server(80);

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);  
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);                                                                                                                                                                                                                     
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT); 

  pinMode(IR_LEFT, INPUT);
  pinMode(IR_RIGHT, INPUT);
  
  Serial.begin(115200);

  // Connecting to WiFi
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
  // Starting WEB-server 
  server.on("/", HTTP_handleRoot);
  server.onNotFound(HTTP_handleRoot);
  server.begin();    
}

void goAhead() { 
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}

void goBack() { 
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
}

void goRight() { 
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  analogWrite(ENB, speedCar);
}

void goLeft() {
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}

void stopRobot() {  
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
  analogWrite(ENB, speedCar);
}

void followLine() {
  bool left = digitalRead(IR_LEFT);
  bool right = digitalRead(IR_RIGHT);

  if (!left && !right) {
    autoMode = false;
    stopRobot();
  } else if (!left && right) {
    goLeft();
  } else if (left && !right) {
    goRight();
  } else {
    goAhead();
  }
}

void loop() {
  bool left = digitalRead(IR_LEFT);
  bool right = digitalRead(IR_RIGHT);

  if (left || right) {
    autoMode = true;
  }

  if (autoMode) {
    followLine();
  } else {
    server.handleClient();
  }
}

void HTTP_handleRoot() {
  if (server.hasArg("State")) {
    command = server.arg("State");

    if (command == "F") goAhead();
    else if (command == "B") goBack();
    else if (command == "L") goLeft();
    else if (command == "R") goRight();
    else if (command == "0") speedCar = 400;
    else if (command == "1") speedCar = 410;
    else if (command == "2") speedCar = 420;
    else if (command == "3") speedCar = 430;
    else if (command == "4") speedCar = 440;
    else if (command == "5") speedCar = 450;
    else if (command == "6") speedCar = 460;
    else if (command == "7") speedCar = 470;
    else if (command == "8") speedCar = 480;
    else if (command == "9") speedCar = 490;
    else if (command == "S") stopRobot();
  }
  server.send(200, "text/html", "");
  delay(1);
}

