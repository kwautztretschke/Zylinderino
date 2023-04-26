#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>


#ifndef STASSID
	#define STASSID "dummerhotspot"
	#define STAPSK  "Amogus187"
#endif

#define NETWORK_IP 70
#define LEDR 12
#define LEDB 14
#define LEDG 13

IPAddress subnet(255,255,255,0);

IPAddress mqttserver(10,42,0,147);

WiFiClient espClient;
PubSubClient mqttclient(espClient);

void(* resetFunc) (void) = 0;

char payload_buffer[256]={0};

void callback(char* topic, byte* payload, unsigned int length) {
	Serial.printf("Message l=%d arrived [%s] ", length, topic);
	strncpy(payload_buffer, (const char*)payload, length);
	Serial.println(payload_buffer);

	// handle payload
	if(payload_buffer[0] == '#')
	{
		long code = strtol(payload_buffer+1, 0, 16);
		char r = (code & 0xFF0000) >> 16;
		char g = (code & 0x00FF00) >> 8;
		char b = (code & 0x0000FF);
		Serial.printf("Interpreting %s (%ld) as (%d, %d, %d)\n", payload_buffer, code, r, g, b);
		analogWrite(LEDR, r);
		analogWrite(LEDG, g);
		analogWrite(LEDB, b);
	}
	memset(payload_buffer, 0, 256);
}


void setup() {
	Serial.begin(115200);
	WiFi.mode(WIFI_STA);
	WiFi.begin(STASSID, STAPSK);
	while (WiFi.status() != WL_CONNECTED) {
		Serial.print('.');
		delay(500);
	}
	Serial.print("Connected! IP address: ");
	Serial.println(WiFi.localIP());

	mqttclient.setServer(mqttserver, 1883);
	mqttclient.setCallback(callback);
	mqttclient.connect("lustigerESP");
	mqttclient.subscribe("test");
	Serial.println("Mqtt stuff initialized");
	mqttclient.publish("test", "hello world");



	// initialize pins
	analogWriteRange(255);
	pinMode(LEDR, OUTPUT);
	pinMode(LEDG, OUTPUT);
	pinMode(LEDB, OUTPUT);
	digitalWrite(LEDR, LOW);
	digitalWrite(LEDG, LOW);
	digitalWrite(LEDB, LOW);
	if(1)
	{
		delay(100);
		digitalWrite(LEDR, HIGH);
		delay(2000);
		digitalWrite(LEDR, LOW);
		digitalWrite(LEDG, HIGH);
		delay(2000);
		digitalWrite(LEDG, LOW);
		digitalWrite(LEDB, HIGH);
		delay(2000);
		digitalWrite(LEDB, LOW);
	}
	Serial.println("Pins initialized");
}


long int g_i = 0;
int g_color = 0;

void loop() 
{
	mqttclient.loop();

	g_i++;
}
