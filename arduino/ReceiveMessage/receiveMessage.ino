//
// Created by evoosa on 30/05/2019.
//
#include <stdlib.h>
#include <stdio.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
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

// Logging related shit
char SERVER_IP[] = "10.100.102.6";
char MSG_URL[] = "/get_msg";
String LOG_URL = String("http://") + SERVER_IP + ":" + PORT + MSG_URL + "?msg=";

// pump related shit //
#define PUMP1 D13
#define PUMP2 D14
#define PUMP3 D15

int PUMP_PINS[3] = { D13, D14, D15 };
int PUMP_DELAY_TIME = 2;

// Connect to WebServer on port PORT
ESP8266WebServer server(PORT);
//Declare an object of class HTTPClient
HTTPClient http;

void send_get_to_server(String msg) {
    msg.replace(" ", "%20");
    Serial.println(LOG_URL + msg);
    http.begin(LOG_URL + msg);
    http.GET();
}

// Run pump
void runPump(int pump_pin, int pump_time) {
    String str_pump_pin = String(pump_pin);
    String str_pump_time = String(pump_time);

    String msg = "[ !!! ] pump '" + str_pump_pin + "' is ON for " + str_pump_time + " ms";
    send_get_to_server(msg);
    //digitalWrite(pump_pin, HIGH);
    //delay(pump_time);
    //digitalWrite(pump_pin, LOW);

    send_get_to_server("[ VVV ] DONE!");
}

//      Handle redirections         //

// Handle Drink / Cocktail redirections

void handleMessage() {
  // Handle messages from the server, and make the drink
    send_get_to_server("[ !!! ] got message!");
    send_get_to_server("[ !!! ] making drink...");
    for ( int i = 0; i < 3; i++ ) {
        int pump_pin = PUMP_PINS[i];
        int pump_time = server.arg(i).toInt();
        //runPump(pump_pin, pump_time);
        delay(PUMP_DELAY_TIME);
    }

    send_get_to_server("[ VVV ] DONE!");

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

    // Print connection data
    Serial.println(String("\nConnected to: ") + SSID);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    // Initialize handles for the redirections
    server.on("/", handleRoot);
    server.on("/handle_drink", handleMessage);
    server.onNotFound(handleNotFound);

    // Start the WebServer !
    server.begin();
    Serial.println("HTTP server started");
  }



void loop(void) {
  server.handleClient();
}
