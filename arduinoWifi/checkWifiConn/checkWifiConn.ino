#include <ESP8266WiFi.h>
#include <SPI.h>            // For SPI comm (needed for not getting compile error)
#include <Wire.h>           // For I2C comm, but needed for not getting compile error

WiFiClient client;

// Wifi Details 
const char* ssid     = "NONA";
const char* password = "0544556008";

void setup()
{
  Serial.begin(9600);

    // Connect to WiFi
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("\nWiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 
}
 
void loop()
{
}
