#include <ESP8266WiFi.h>
#include <SPI.h>            // For SPI comm (needed for not getting compile error)
#include <Wire.h>           // For I2C comm, but needed for not getting compile error
#include <SoftwareSerial.h>

#define DEBUG true

SoftwareSerial espchip8266(0,1);
// make RX Arduino line is pin 2, make TX Arduino line is pin 3.
// This means that you need to connect the TX line from the esp to the Arduino's pin 2
// and the RX line from the esp to the Arduino's pin 3

// Wifi Details 
//const char* ssid     = "NONA";
//const char* password = "0544556008";

//WiFiClient client;

/*
* Name: sendData
* Description: Function used to send data to espchip8266.
* Params: command - the data/command to send; timeout - the time to wait for a response; debug - print to Serial window?(true = yes, false = no)
* Returns: The response from the espchip8266 (if there is a reponse)
*/
String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    espchip8266.print(command); // send the read character to the espchip8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(espchip8266.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = espchip8266.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}
void setup() {
  Serial.begin(115200);
//
//  // Connect to WiFi
//  Serial.println("Connecting to ");
//  Serial.println(ssid);
//  WiFi.begin(ssid, password);
//  
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//
//  Serial.println("");
//  Serial.println("\nWiFi connected");  
//  Serial.println("IP address: ");
//  Serial.println(WiFi.localIP());

  pinMode(11,OUTPUT);
  digitalWrite(11,LOW);
  
  pinMode(12,OUTPUT);
  digitalWrite(12,LOW);
  
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);

  sendData("AT+RST\r\n",2000,DEBUG); // reset module
//  sendData("AT+CWMODE=2\r\n",1000,DEBUG); // configure as access point
  sendData("AT+CWJAP=NONA,0544556008",1000,DEBUG);
  sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
  Serial.print("ip is ");
  // Loop through all the data returned
  while(espchip8266.available()) {
        // The esp has data so display its output to the serial window
        char c = espchip8266.read(); // read the next character.
        Serial.write(c);
  }
  Serial.println("");
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
}

 
void loop()
{
  if(espchip8266.available()) // check if the esp is sending a message 
  {
 
    
    if(espchip8266.find("+IPD,"))
    {
     delay(1000); // wait for the serial buffer to fill up (read all the serial data)
     // get the connection id so that we can then disconnect
     int connectionId = espchip8266.read()-48; // subtract 48 because the read() function returns 
                                           // the ASCII decimal value and 0 (the first decimal number) starts at 48
          
     espchip8266.find("pin="); // advance cursor to "pin="
     
     int pinNumber = (espchip8266.read()-48)*10; // get first number i.e. if the pin 13 then the 1st number is 1, then multiply to get 10
     pinNumber += (espchip8266.read()-48); // get second number, i.e. if the pin number is 13 then the 2nd number is 3, then add to the first number
     
     digitalWrite(pinNumber, !digitalRead(pinNumber)); // toggle pin    
     
     // make close command
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; // append connection id
     closeCommand+="\r\n";
     
     sendData(closeCommand,1000,DEBUG); // close connection
    }
  }
}
 

