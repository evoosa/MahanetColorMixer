#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Servo.h> 

// Constants Definitions

#ifndef STASSID
#define STASSID "NONA"
#define STAPSK  "0544556008"

// !!!!!!!!! PAY ATTENTION - the pinc names start with D fuck!!!!!!!
// Declare the Servo pin 
#define servoPin D13
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

const int port = 6969;

// Connect to WebServer on port 'port'
ESP8266WebServer server(port);

//    Handle the '/' redirection    //
void handleRoot() {
  server.send(200, "text/plain", "THIS IS THE ROOT PAGE GO AWAY");
  Serial.println("Root");
}

//    Handle On / Off redirections    //

// Zero - 0
void handleZero() {
  server.send(200, "text/plain", "turning 0 degrees");
  // Make servo go to 0 degrees 
  Servo Servo1; 
  Servo1.attach(servoPin);
  Servo1.write(0);   
  Serial.println("turning 0 degrees");
}

//  Ninety - 90
void handleNinety() {
  server.send(200, "text/plain", "turning 90 degrees");
  // Make servo go to 90 degrees
  Servo Servo1; 
  Servo1.attach(servoPin); 
  Servo1.write(90);   
  Serial.println("turning 90 degrees");
}

//  One Eighty - 180
void handleOneEighty() {
  server.send(200, "text/plain", "turning 180 degrees");
  // Make servo go to 180 degrees 
  Servo Servo1; 
  Servo1.attach(servoPin);
  Servo1.write(180);   
  Serial.println("turning 180 degrees");
}

//  Handle the '/???' redirection   //
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  Serial.println("Not Found");

}

void setup(void) {

  // Create a servo object 
  Servo Servo1; 
  Servo1.attach(servoPin);
  // Make servo go to 0 degrees 
  Servo1.write(0); 
  
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  // Initialize handles for the redirections
  server.on("/", handleRoot);
  server.on("/z", handleZero);
  server.on("/n", handleNinety);
  server.on("/oe", handleOneEighty);
  server.onNotFound(handleNotFound);

  // Start the WebServer !
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}
