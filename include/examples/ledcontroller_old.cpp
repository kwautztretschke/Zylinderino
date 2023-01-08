//#define UDPREPLIES
//#define PRINTPACKETS

//#define L_ZIMMER
//#define L_SHISHA
//#define L_WHITEBOARD
#define L_TISCH

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>


#ifndef STASSID
#define STASSID "SSID"
#define STAPSK  "PASSWORD"
#endif

#ifdef L_ZIMMER
  #define L_RGBW
  #define NETWORK_IP 75
  #define LEDR 12
  #define LEDG 14
  #define LEDB 4
  #define LEDW 5
  #define LIGHTSWITCH 13
#endif

#ifdef L_SHISHA
  #define L_RGB
  #define NETWORK_IP 74
  #define LEDR 4
  #define LEDG 14
  #define LEDB 5
#endif  

#ifdef L_WHITEBOARD
  #define L_RGB
  #define NETWORK_IP 71
  #define LEDR 12
  #define LEDG 13
  #define LEDB 14
#endif

#ifdef L_TISCH
  #define L_RGB
  #define NETWORK_IP 70
  #define LEDR 12
  #define LEDG 14
  #define LEDB 13
#endif

unsigned int localPort = 26091;      // local port to listen on
IPAddress staticIP(10,69,0,NETWORK_IP), gateway (10,69,0,1);
IPAddress subnet(255,255,255,0);
//IPAddress dns(gateway);

// buffers for receiving and sending data
#define PACKETBUFFERSIZE 4
char packetBuffer[PACKETBUFFERSIZE]; //buffer to hold incoming packet,
char  replyBuffer[UDP_TX_PACKET_MAX_SIZE + 1];       // a string to send back

//opcodes; 
//0000 = boot/debug; 
//0001 = modify color:  r,    g,    b;
//0010 = brightness:    abs,  N/A,  N/A; 
//0011 = brightness:     rel,  sign, N/A;
//0100 = bu2bl input; 
//0101 = rainbow;

struct s_rgb {
  int r;
  int g;
  int b;
  int brt;
};

char mode = 0;
struct s_rgb rgbC; //current
struct s_rgb rgbN; //new

int fade = 1000; //fade duration in milliseconds

int packetCount = 0;
unsigned long previousTime = 0;

WiFiUDP Udp;

void(* resetFunc) (void) = 0;

int getPacket(struct s_rgb *rgbN, struct s_rgb rgbC)
{  
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    // read the packet into packetBufffer
    int n = Udp.read(packetBuffer, PACKETBUFFERSIZE);
    packetBuffer[n] = 0;
    //parse Packet
    switch(packetBuffer[0]){
      case 0: //reboot
        resetFunc();
      break;
      
      case 1: //modify color
        mode = 1;
        rgbN->r = packetBuffer[1];
        rgbN->g = packetBuffer[2];
        rgbN->b = packetBuffer[3];
      break;
      
      case 2: //absolute brightness
        mode = 1;
        *rgbN = rgbC;
        rgbN->brt = packetBuffer[1];
      break;
      
      case 3: //relative brightness
        mode = 1;
        *rgbN = rgbC;
        (!packetBuffer[2]) ? rgbN->brt+=packetBuffer[1] : rgbN->brt-=packetBuffer[1]; //add or subtract
        if(rgbN->brt<0)   rgbN->brt = 0;   //clip
        if(rgbN->brt>100) rgbN->brt = 100;
      break;
      
      case 4: //bu2bl2
        mode = 4;
        rgbN->brt = 100;
        rgbN->r = packetBuffer[1];
        rgbN->g = packetBuffer[2];
        rgbN->b = packetBuffer[3];
      break;
    }
    
    packetCount++;
    previousTime=millis(); //update time of last packet
  }
  return packetSize;
}
void updateColors(struct s_rgb rgbN, struct s_rgb rgbC, int fade)
{
  if(fade&&(rgbC.brt||rgbN.brt)){ //if the brightnesses are both 0, switch color immediately (for presets)
    for(int i=0; i<fade; i++){
		analogWrite(LEDR, (((rgbC.r*rgbC.brt)/100) * (fade-i)  +  ((rgbN.r*rgbN.brt)/100) * i)/fade);
		analogWrite(LEDG, (((rgbC.g*rgbC.brt)/100) * (fade-i)  +  ((rgbN.g*rgbN.brt)/100) * i)/fade);
		analogWrite(LEDB, (((rgbC.b*rgbC.brt)/100) * (fade-i)  +  ((rgbN.b*rgbN.brt)/100) * i)/fade);
		delay(1);                                           // 1 millisecond delay, total delay = fade;
    }
  }else{        // switch color immediately
	analogWrite(LEDR, (rgbN.r*rgbN.brt)/100);
	analogWrite(LEDG, (rgbN.g*rgbN.brt)/100);
	analogWrite(LEDB, (rgbN.b*rgbN.brt)/100);
  }
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
  if (!WiFi.config(staticIP, gateway, subnet)) Serial.println("STA Failed to configure");
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  Serial.printf("UDP server on port %d\n", localPort);
  Udp.begin(localPort);


  // initialize pins
  analogWriteRange(255);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, LOW);

  Serial.println("Send four bytes, first the opcode, then the colors RGB");
  Serial.println();

  // OTA
  #ifdef L_ZIMMER
  ArduinoOTA.setHostname("bernie-zimmerlicht");
  #endif
  #ifdef L_SHISHA
  ArduinoOTA.setHostname("bernie-shisha");
  #endif
  #ifdef L_WHITEBOARD
  ArduinoOTA.setHostname("bernie-whiteboard");
  #endif
  #ifdef L_TISCH
  ArduinoOTA.setHostname("bernie-tisch");
  #endif
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
    case 0: // Boot/Debug
      rgbC = { 255, 255, 255, 100 };
      rgbN = rgbC;
      updateColors(rgbN, rgbC, 0);
      mode = 1;
    break;
    case 1: // Room Light
      if(getPacket(&rgbN, rgbC)){
        updateColors(rgbN, rgbC, fade);
        rgbC = rgbN;
      }
    break;
    case 4: // Bu2Bl2
      if(getPacket(&rgbN, rgbC)){
        updateColors(rgbN, rgbC, 0);
        rgbC = rgbN;
      }
      
      if(millis()-previousTime > 5000 && packetCount){
        Serial.printf("Haven't received Packet for five seconds, rebooting into light mode\n");
        delay(10);
        resetFunc();
      }
    break;
  }
  /*  OTA
   */
  ArduinoOTA.handle();
}

/*
  test (shell/netcat):
  --------------------
	  nc -u 10.96.esp.address 26091
*/
