#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoOTA.h>

namespace global{
	const char* wifiSsid = "testwlan";
	const char* wifiPassword = "amingus187";
	const char* mqttServerIp = "192.168.43.150";
	IPAddress staticIP(10,69,0,NETWORK_IP);
	IPAddress gateway(10,69,0,1);
	IPAddress subnet(255,255,255,0);
}

class MqttClientClass{
private:
	WiFiClient		m_wifi;
	PubSubClient 	m_client;
	static void callback(char* topic, uint8_t* payload, unsigned int length);
public:
	void startWiFi(){
		Serial.println();
		Serial.print("Connecting to ");
		Serial.println(global::wifiSsid);
		WiFi.mode(WIFI_STA);
		WiFi.begin(global::wifiSsid, global::wifiPassword);
		while (WiFi.status() != WL_CONNECTED) {
			Serial.print('.');
			delay(500);
		}
		Serial.print("Connected! IP address: ");
		Serial.println(WiFi.localIP());
		m_client.setClient(m_wifi);
		m_client.setServer(global::mqttServerIp, 1883);
	}
	String receiveNameFromMacAddress(String mac_address){
		String name;
		// set a temporary callback
		m_client.setCallback(
			[&name](char* topic, uint8_t* payload, unsigned int length){
				name = (char*)payload;
			}
		);
		String mac_topic = "mac/" + mac_address + "/name";
		m_client.subscribe((const char*)mac_topic.c_str());
		// wait until a name is received
		while(!name)
			m_client.loop();
		// name received!
		return name;
	}
	void initWithName(String name){
		m_client.setCallback(callback);
		m_client.setServer(global::mqttServerIp, 1883);
		String reactor_topic = "reactor/" + name + "/#";
		m_client.subscribe((const char*)reactor_topic.c_str());
	}
	void loop() {
		m_client.loop();
	}
} MqttClient;

class ProgramManagerClass{
public:
	static void init();
	static void renderProgram();
} ProgramManager;


void setup() {
	Serial.begin(115200);
	MqttClient.startWiFi();
	// receive our name via a retained message under mac/<address>/name
	String mac_address = "swag";
	String device_name = MqttClient.receiveNameFromMacAddress(mac_address);

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