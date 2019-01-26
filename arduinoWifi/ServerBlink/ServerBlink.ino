#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

// Constants Definitions

#ifndef STASSID
#define STASSID "NONA"
#define STAPSK  "0544556008"

// !!!!!!!!! PAY ATTENTION - the pinc names start with D fuck!!!!!!!
#define LED_BUILTIN D13
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

//  On
void handleOn() {
  server.send(200, "text/plain", "turning betches ONNNNNNNNNNNNN");
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.println("turning led:    [ ON ]");
}

//  Off
void handleOff() {
  server.send(200, "text/plain", "turning betches off :(");
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("turning led:    [ OFF ]");
}

//    Handle the '/???' redirection   //
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
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
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
  server.on("/on", handleOn);
  server.on("/off", handleOff);
  server.onNotFound(handleNotFound);

  // Start the WebServer !
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}
