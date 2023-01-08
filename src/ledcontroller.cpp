#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoOTA.h>
#include <cstring>

#include "wificredentials.h"

class MqttClientClass{
private:
	WiFiClient		m_wifi;
	PubSubClient 	m_client;
	String			m_mac_address;
	static void callback(char* topic, uint8_t* payload, unsigned int length){
		Serial.print("Message arrived [");
		Serial.print(topic);
		Serial.print("] ");
		for (unsigned int i = 0; i < length; i++) {
			Serial.print((char)payload[i]);
		}
		Serial.println();
	}
	void reconnect(String mac_address) {
		// Loop until we're reconnected
		while (!m_client.connected()) {
			Serial.print("Attempting MQTT connection...");
			// Create a random client ID
			String clientId = "ESP8266Client-";
			clientId += mac_address;
			// Attempt to connect
			if (m_client.connect(clientId.c_str())) {
			Serial.println("connected");
			// Once connected, publish an announcement...
			String mac_status_topic = "mac/" + mac_address + "/status";
			m_client.publish((const char*)mac_status_topic.c_str(), "connected");
			} else {
			Serial.print("failed, rc=");
			Serial.print(m_client.state());
			Serial.println(" try again in 5 seconds");
			// Wait 5 seconds before retrying
			delay(5000);
			}
		}
	}
public:
	void startWiFi(){
		m_mac_address = WiFi.macAddress();
		Serial.println();
		Serial.print("MAC-Address: ");
		Serial.println(m_mac_address);
		Serial.print("Connecting to ");
		Serial.println(wificredentials::ssid);
		WiFi.mode(WIFI_STA);
		WiFi.begin(wificredentials::ssid, wificredentials::password);
		while (WiFi.status() != WL_CONNECTED) {
			Serial.print('.');
			delay(500);
		}
		Serial.print("Connected! IP address: ");
		Serial.println(WiFi.localIP());
		m_client.setClient(m_wifi);
		m_client.setServer(wificredentials::mqttServerIp, 1883);
		reconnect(m_mac_address);
	}
	String receiveNameFromMacAddress(){
		char name[32] = {0};
		bool name_received = false;
		// set a temporary callback
		m_client.setCallback(
			[&name, &name_received](char* topic, uint8_t* payload, unsigned int length){
				strncpy(name, (char*)payload, length);
				name_received = true;
			}
		);
		// declare our status as searching
		String mac_status_topic = "mac/" + m_mac_address + "/status";
		m_client.publish((const char*)mac_status_topic.c_str(), "searching_name");
		// subscribe to the appropriate topic
		String mac_name_topic = "mac/" + m_mac_address + "/name";
		m_client.subscribe((const char*)mac_name_topic.c_str());
		Serial.print("Waiting to receive device name via ");
		Serial.print(mac_name_topic);
		// wait until a name is received
		while(!name_received){
			m_client.loop();
			Serial.print(".");
			delay(10);
		}
		// name received!
		m_client.publish((const char*)mac_status_topic.c_str(), "ready");
		Serial.println();
		Serial.print("My name is ");
		Serial.println(name);
		return String(name);
	}
	void initWithName(String name){
		m_client.setCallback(callback);
		m_client.setServer(wificredentials::mqttServerIp, 1883);
		String reactor_topic = "reactor/" + name + "/#";
		m_client.subscribe((const char*)reactor_topic.c_str());
	}
	void loop() {
		m_client.loop();
	}
} MqttClient;

class ProgramManagerClass{
public:
	static void init(){}
	static void renderProgram(){}
} ProgramManager;


void setup() {
	Serial.begin(115200);
	MqttClient.startWiFi();
	// receive our name via a retained message under mac/<address>/name
	String device_name = MqttClient.receiveNameFromMacAddress();

	// init other stuff
	ArduinoOTA.setHostname((const char*)device_name.c_str());
	ProgramManager.init();

	// subscribe to all our topics at reactor/<name>/#
	// (and begin handling the flood of retained messages)
	MqttClient.initWithName(device_name);
}

void loop() {
	MqttClient.loop();
	ProgramManager.renderProgram();
	ArduinoOTA.handle();
}