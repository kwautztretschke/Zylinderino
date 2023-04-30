#ifndef __MQTTCLIENT_H__
#define __MQTTCLIENT_H__
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <cstring>

#include "wificredentials.h"

#ifndef __WIFICREDENTIALS_H__
	namespace wificredentials{
		const String 	ssid = 			"dummerhotspot";
		const String	password = 		"Amogus187";
		const IPAddress mqttServerIp = 	IPAddress(10,42,0,141);
		const String	deviceName = 	"tollerESP";
	}
#endif


class MqttClientClass{
private:
	WiFiClient		m_WifiClient;
	PubSubClient 	m_Client;
	const String	m_DeviceName = wificredentials::deviceName;
	static void 	mqttCallback(char* topic, uint8_t* payload, unsigned int length);
	void 			connectMqtt(); 
	// callbacks
	void			(*p_input)(char* key, char* value);
	int				(*p_focus)(char* program);
	void			(*p_reboot)();
public:
	const String 	getDeviceName() {return m_DeviceName;}
	void 			startWiFi();
	void 			init();
	void 			loop(); 
	// callbacks
	void			setInputCallback(void (*input)(char* key, char* value)) {p_input = input;}
	void			setFocusCallback(int (*focus)(char* program)) {p_focus = focus;}
	void			setRebootCallback(void (*reboot)()) {p_reboot = reboot;}
};

extern MqttClientClass MqttClient;

#endif //__MQTTCLIENT_H__