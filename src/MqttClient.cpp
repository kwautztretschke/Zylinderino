#include "MqttClient.h"

#include "wificredentials.h"

void MqttClientClass::callback(char* topic, uint8_t* payload, unsigned int length){
	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("] ");
	for (unsigned int i = 0; i < length; i++) {
		Serial.print((char)payload[i]);
	}
	Serial.println();
}

void MqttClientClass::connectMqtt() {
	// Loop until we're reconnected
	while (!m_Client.connected()) {
		Serial.print("Attempting MQTT connection...");
		// Attempt to connect
		if (m_Client.connect(m_DeviceName.c_str())) {
			Serial.println("connected");
			// Once connected, publish an announcement...
			String status_topic = "actor/" + m_DeviceName + "/status";
			m_Client.publish((const char*)status_topic.c_str(), "connected");
		} else {
			Serial.print("failed, rc=");
			Serial.print(m_Client.state());
			Serial.println(" try again in 5 seconds");
			// Wait 5 seconds before retrying
			delay(5000);
		}
	}
}

void MqttClientClass::startWiFi(){
	String mac_address = WiFi.macAddress();
	Serial.println();
	Serial.println(	"MAC-Address: " + mac_address + 
					", device name" + m_DeviceName);
	Serial.println("Connecting to " + wificredentials::ssid);
	WiFi.mode(WIFI_STA);
	WiFi.begin(wificredentials::ssid, wificredentials::password);
	while (WiFi.status() != WL_CONNECTED) {
		Serial.print('.');
		delay(500);
	}
	Serial.println("WiFi connected! IP address: " + WiFi.localIP().toString());
}


void MqttClientClass::init(){
	// connect to mqtt broker
	m_Client.setClient(m_WifiClient);
	m_Client.setServer(wificredentials::mqttServerIp, 1883);
	m_Client.setCallback(callback);
	connectMqtt();
	// Subscribe to all topics belonging to this reactor via
	// reactor/<name>/#
	String reactor_topic = "reactor/" + m_DeviceName + "/#";
	m_Client.subscribe((const char*)reactor_topic.c_str());
}

void MqttClientClass::loop() {
	m_Client.loop();
	if(!m_Client.connected())
		connectMqtt();
}


MqttClientClass MqttClient;