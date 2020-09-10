  /*
  UDPSendReceive.pde:
  This sketch receives UDP message strings, prints them to the serial port
  and sends an "acknowledge" string back to the sender

  A Processing sketch is included at the end of file that can be used to send
  and received messages for testing with a computer.

  created 21 Aug 2010
  by Michael Margolis

  This code is in the public domain.

  adapted from Ethernet library examples
*/

//#define UDPREPLIES
//#define PRINTPACKETS

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>


#ifndef STASSID
#define STASSID "***REMOVED***"
#define STAPSK  "***REMOVED***"
#endif

#define NETWORK_IP 175

#define LEDR 12
#define LEDG 14
#define LEDB 4
#define LEDW 5
#define LIGHTSWITCH 13

unsigned int localPort = 26091;      // local port to listen on
//IPAddress broadcast=IPAddress(224, 0, 0, 69); // multicast address (SLOW AND GAY)
IPAddress staticIP(10,96,0,NETWORK_IP), gateway (10,96,0,254); // ***REMOVED***
IPAddress subnet(255,255,255,0);
IPAddress dns(gateway);

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1]; //buffer to hold incoming packet,
char  replyBuffer[UDP_TX_PACKET_MAX_SIZE + 1];       // a string to send back

//bitmasks; 0000 = debug; 0001 = waiting for single color (room light); 0010 = bu2bl input; 0100 = rainbow
char mode = 0;

int r, g, b, w;

int packetCount = 0;
unsigned long previousTime = 0;

WiFiUDP Udp;

void(* resetFunc) (void) = 0;

int getPacket()
{  
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    #ifdef PRINTPACKETS
      Serial.printf("Received packet #%d of size %d from %s:%d\n  Arrived after %d seconds, first one since %d milliseconds\n  (to %s:%d, free heap = %d B)\n",
                  packetCount, packetSize,
                  millis()/60, millis()-previousTime,
                  Udp.remoteIP().toString().c_str(), Udp.remotePort(),
                  Udp.destinationIP().toString().c_str(), Udp.localPort(),
                  ESP.getFreeHeap());
    #endif

    // read the packet into packetBufffer
    int n = Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    packetBuffer[n] = 0;
    
    #ifdef PRINTPACKETS
      Serial.printf("Contents: %d, %d, %d, %d\n", packetBuffer[0], packetBuffer[1], packetBuffer[2], packetBuffer[3]);
    #endif
    
    //parse Packet
    mode = packetBuffer[0];
    if(mode==1&&(packetBuffer[1]==packetBuffer[2])&&(packetBuffer[2]==packetBuffer[3])){
      w = packetBuffer[1]*4; r = 0; g = 0; b = 0;
    }else{
      w = 0; r = packetBuffer[1]*4; g = packetBuffer[2]*4; b = packetBuffer[3]*4;
    }
    
    //update Colors
    analogWrite(LEDR, r);
    analogWrite(LEDG, g);
    analogWrite(LEDB, b);
    analogWrite(LEDW, w);
    packetCount++;
    previousTime=millis(); //update time of last packet
  }
  return packetSize;
}

void sendPacket(char*string)
{
  // send a reply, to the IP address and port that sent us the packet we received
  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
  Udp.write(string);
  Udp.endPacket();
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.config(staticIP, gateway, subnet, dns);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  Serial.printf("UDP server on port %d\n", localPort);
  Udp.begin(localPort);


  // initialize the digital pin as an output.
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  pinMode(LEDW, OUTPUT);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, LOW);
  digitalWrite(LEDW, LOW);

    Serial.println("Send four bytes, first the mode, then the colors RGB");
    Serial.println();

  // OTA
  ArduinoOTA.setHostname("bernie-zimmerlicht");
  ArduinoOTA.setPassword("swag");

  ArduinoOTA.onStart([]() {
      Serial.println("OTA: Start");
      //digitalWrite(BOARD_LED,1);
    });
  ArduinoOTA.onEnd([]() {
      //digitalWrite(BOARD_LED,1);
      Serial.println("\nOTA: End");
    });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
      static bool state = false;
      //digitalWrite(BOARD_LED,state);
      state ^= true;
      Serial.printf("OTA: Progress: %u%%\r", (progress / (total / 100)));
    });
  ArduinoOTA.onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR)      Serial.println("Auth failed");
      else if (error == OTA_BEGIN_ERROR)    Serial.println("Begin failed");
      else if (error == OTA_CONNECT_ERROR)  Serial.println("Connect failed");
      else if (error == OTA_RECEIVE_ERROR)  Serial.println("Receive failed");
      else if (error == OTA_END_ERROR)    Serial.println("End failed");
    });
  ArduinoOTA.begin();
    
  
}

void loop() 
{
  switch(mode)
  { 
    case 0: // Debug
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDG, HIGH);
    digitalWrite(LEDB, HIGH);
    digitalWrite(LEDW, HIGH);
    getPacket();
    break;
    case 1: // Room Light
    getPacket();
    break;
    case 2: // Bu2Bl2
    getPacket();

    if(millis()-previousTime > 5000 && packetCount){
      Serial.printf("Haven't received Packet for five seconds, rebooting into light mode\n");
      delay(10);
      resetFunc();
    }
    break;
  }
  
  
  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("Wifi Disconnected!");
    delay(500);
  }

  /*  OTA
   */
  ArduinoOTA.handle();
}

/*
  test (shell/netcat):
  --------------------
	  nc -u 192.168.esp.address 8888
*/
