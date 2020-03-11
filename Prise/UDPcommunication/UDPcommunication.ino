/*
 *  This sketch sends random data over UDP on a ESP32 device
 *
 */
#include <WiFi.h>
#include <WiFiUdp.h>
#include <stdio.h>


// WiFi network name and password:
const char * networkName = "Aron";
const char * networkPswd = "12345678";
//const char * x;

//IP address to send UDP data to:
// either use the ip address of the server or 
// a network broadcast address
const char * udpAddress = "192.168.43.132";
const int udpPort = 1337;

//Are we currently connected?
boolean connected = false;

//The udp library class
WiFiUDP udp;

void setup(){
  // Initilize hardware serial:
  Serial.begin(9600);
  
  //Connect to the WiFi network
  connectToWiFi(networkName, networkPswd);
}

void loop(){
  //only send data when connected
  if(connected){
    
    //Serial.println(Serial.read());
    //udp.beginPacket(udpAddress,udpPort);
    //udp.beginPacket(Serial.read(),udpPort);
    //udp.printf("Seconds since boot: %lu", millis()/1000);
    //x  = Serial.read();
    //udp.printf(x)
    //udp.printf(Serial.read());
    //udp.endPacket();

    if (Serial.available() > 0){
      char bfr[501];
      memset(bfr,0, 501);
      char maggie = Serial.readBytesUntil( '\n',bfr,500);
      //Serial.println(maggie);
      udp.beginPacket(udpAddress,udpPort);
      //udp.printf("Helo i work");
      //udp.printf("Seconds since boot: %lu", millis()/1000);
      udp.printf("%lu", maggie);
      udp.endPacket();
      
      
      
    }
  }
  //Wait for 1 second
  delay(500);
}

void connectToWiFi(const char * ssid, const char * pwd){
  Serial.println("Connecting to WiFi network: " + String(ssid));

  // delete old config
  WiFi.disconnect(true);
  //register event handler
  WiFi.onEvent(WiFiEvent);
  
  //Initiate connection
  WiFi.begin(ssid, pwd);

  Serial.println("Waiting for WIFI connection...");
}

//wifi event handler
void WiFiEvent(WiFiEvent_t event){
    switch(event) {
      case SYSTEM_EVENT_STA_GOT_IP:
          //When connected set 
          Serial.print("WiFi connected! IP address: ");
          Serial.println(WiFi.localIP());  
          //initializes the UDP state
          //This initializes the transfer buffer
          udp.begin(WiFi.localIP(),udpPort);
          connected = true;
          Serial.println("Connected");
          break;
      case SYSTEM_EVENT_STA_DISCONNECTED:
          Serial.println("WiFi lost connection");
          connected = false;
          break;
      default: break;
    }
}
