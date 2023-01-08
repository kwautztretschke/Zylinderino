#include <ArduinoOTA.h>

#include "MqttClient.h"


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