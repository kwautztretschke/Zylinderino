#ifndef __MQTTCLIENT_H__
#define __MQTTCLIENT_H__
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <cstring>

class MqttClientClass{
private:
	WiFiClient		m_WifiClient;
	PubSubClient 	m_Client;
	const String	m_DeviceName = "tollerESP";
	static void 	callback(char* topic, uint8_t* payload, unsigned int length);
	void 			connectMqtt(); 
public:
	const String 	getDeviceName() {return m_DeviceName;}
	void startWiFi();
	void init();
	void loop(); 
};

extern MqttClientClass MqttClient;

#endif //__MQTTCLIENT_H__