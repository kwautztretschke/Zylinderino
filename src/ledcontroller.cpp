#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>


#ifndef STASSID
	#define STASSID "dummerhotspot"
	#define STAPSK  "Amogus187"
#endif

#define NETWORK_IP 70
#define LEDR 12
#define LEDG 14
#define LEDB 13

IPAddress staticIP(10,69,0,NETWORK_IP), gateway (10,69,0,1);
IPAddress subnet(255,255,255,0);

WiFiUDP Udp;

void(* resetFunc) (void) = 0;

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

  // initialize pins
  analogWriteRange(255);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, LOW);
  Serial.println("Pins initialized");
}


long int g_i = 0;
int g_color = 0;

void loop() 
{
	if (g_i%50000 == 0)
		g_color++;
	if (g_color>2)
		g_color=0;
	switch (g_color)
	{
		case 0:
		digitalWrite(LEDR, HIGH);
		digitalWrite(LEDG, LOW);
		digitalWrite(LEDB, LOW);
		break;
		case 1:
		digitalWrite(LEDR, LOW);
		digitalWrite(LEDG, HIGH);
		digitalWrite(LEDB, LOW);
		break;
		case 2:
		digitalWrite(LEDR, LOW);
		digitalWrite(LEDG, LOW);
		digitalWrite(LEDB, HIGH);
		break;
	}

	g_i++;
}
