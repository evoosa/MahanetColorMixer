#include <SoftwareSerial.h>

SoftwareSerial espchip8266(11,12);
// make RX Arduino line is pin 2, make TX Arduino line is pin 3.
// This means that you need to connect the TX line from the esp to the Arduino's pin 2
// and the RX line from the esp to the Arduino's pin 3


void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  espchip8266.begin(115200);
  
  espchip8266.print("AT+RST\r\n"); // reset module
  Serial.print("resetted");
  
  espchip8266.print("AT+CWJAP=NONA,0544556008");
  Serial.print("connected to wifi");
  
  espchip8266.print("AT+CWMODE=2\r\n"); // configure as access point
  Serial.println("is now an access point");
  
  espchip8266.print("AT+CIPMUX=1\r\n"); // configure for multiple connections
  Serial.print("configured for multiple connections");

  espchip8266.print("AT+CIPSERVER=1,80\r\n"); // turn on server on port 80
  Serial.print("server on port 80");
  
  espchip8266.print("AT+CIFSR\r\n"); // get ip address
  Serial.print("ip is:");
  // Loop through all the data returned
  while(espchip8266.available()) {
        // The esp has data so display its output to the serial window
        char c = espchip8266.read(); // read the next character.
        Serial.write(c);
        
  }
}

void loop() {
}
