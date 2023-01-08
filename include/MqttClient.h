#ifndef __MQTTCLIENT_H__
#define __MQTTCLIENT_H__
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <cstring>

class MqttClientClass{
private:
	WiFiClient		m_wifi;
	PubSubClient 	m_client;
	String			m_mac_address;
	static void callback(char* topic, uint8_t* payload, unsigned int length);
	void reconnect(String mac_address); 
public:
	void startWiFi();
	String receiveNameFromMacAddress();
	void initWithName(String name);
	void loop(); 
};

extern MqttClientClass MqttClient;

#endif //__MQTTCLIENT_H__