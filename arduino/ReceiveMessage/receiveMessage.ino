//
// Created by evoosa on 30/05/2019.
//
#include <stdlib.h>
#include <stdio.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WebSocketClient.h>
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;


// Constants Definitions
String message;

// WIFI related shit
const char* SSID = "NONA";
const char* PASSWORD = "0544556008";
const int PORT = 80;

// WS related shit
char WS_PATH[] = "/ard_ws";
char SERVER_IP[] = "10.100.102.7";

// pump related shit //
#define PUMP1 D13
#define PUMP2 D14
#define PUMP3 D15

int PUMP_PINS[3] = { D13, D14, D15 };
int PUMP_DELAY_TIME = 2;

// Connect to WebServer on port PORT
ESP8266WebServer server(PORT);
// Connect to WS server on port WS_PORT
WebSocketClient webSocketClient;
// Use WiFiClient class to create TCP connections
WiFiClient client;

// Run pump
void runPump(int pump_pin, int pump_time) {
    String str_pump_pin = String(pump_pin);
    String str_pump_time = String(pump_time);
    webSocketClient.sendData("[ !!! ] pump '" + str_pump_pin + "' is ON for " + str_pump_time + " ms");

    //digitalWrite(pump_pin, HIGH);
    //delay(pump_time);
    //digitalWrite(pump_pin, LOW);

    webSocketClient.sendData("[ VVV ] DONE!");
}

//      Handle redirections         //

// Handle Drink / Cocktail redirections

// Handle messages from the server, and make the drink
void handleMessage() {
    webSocketClient.sendData("[ !!! ] got message: " + server.args());
    webSocketClient.sendData("[ !!! ] making drink...");
    for ( int i = 0; i < 4; i++ ) {
        int pump_pin = PUMP_PINS[i];
        int pump_time = server.arg(i).toInt();
        runPump(pump_pin, pump_time);
        delay(PUMP_DELAY_TIME);
    }

    webSocketClient.sendData("[ VVV ] DONE!");

    // tell server everything is damn FINE
    server.send(200, "text/plain", message);
    }


// Handle the '/' redirection
void handleRoot() {
    server.send(200, "text/plain", "THIS IS THE ROOT PAGE GO AWAY");
    Serial.println("Root");
}

// Handle the '/???' redirection
void handleNotFound() {
    server.send(404, "text/plain", "GO AWAY PLS");
    Serial.println("Not Found");
}

void setup(void) {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASSWORD);
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(SSID);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    if (MDNS.begin("esp8266")) {
        Serial.println("MDNS responder started");
    }

    // Initialize handles for the redirections
    server.on("/", handleRoot);
    server.on("/drink", handleMessage);
    server.onNotFound(handleNotFound);

    // Start the WebServer !
    server.begin();
    Serial.println("HTTP server started");

    // Connect to the websocket server
    if (client.connect(SERVER_IP, PORT)) {
      Serial.println("Connected");
    } else {
      Serial.println("Connection failed.");
      while(1) {
        // Hang on failure
      }
    }

    // handshake with the ws server
    webSocketClient.path = WS_PATH;
    webSocketClient.host = SERVER_IP;
    if (webSocketClient.handshake(client)) {
        webSocketClient.sendData("Handshake successful");
    }
    else {
        Serial.println("Handshake failed.");
    while(1) {
      // Hang on failure
        }
    }
}

void loop(void) {
    server.handleClient();
    MDNS.update();
}
