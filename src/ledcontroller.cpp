#include <ArduinoOTA.h>
#include <PubSubClient.h>

#include "MqttClient.h"
#include "ProgramManager.h"




void setup(){
	Serial.begin(115200);
	MqttClient.startWiFi();

	// init other stuff
	ArduinoOTA.setHostname(MqttClient.getDeviceName().c_str());
	ProgramManager.init();

	// subscribe to all our topics at reactor/<name>/#
	// (and begin handling the flood of retained messages)
	MqttClient.setInputCallback(ProgramManager.input);
	MqttClient.setFocusCallback(ProgramManager.focus);
	MqttClient.setRebootCallback(0);
	MqttClient.init();
}

void loop(){
	MqttClient.loop();
	ProgramManager.renderProgram();
	ArduinoOTA.handle();
}
