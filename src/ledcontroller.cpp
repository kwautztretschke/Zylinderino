#include <ArduinoOTA.h>
#include <PubSubClient.h>

#include "MqttClient.h"
#include "ProgramManager.h"
#include "Hardware.h"


long tick = 0;

void setup(){
	// start communication
	Serial.begin(115200);
	MqttClient.startWiFi();

	// init other stuff
	ArduinoOTA.setHostname(MqttClient.getDeviceName().c_str());
	ProgramManager::init();
	ProgramManager::initPrograms();
	Hardware::init();

	// init MqttClient and set callbacks to ProgramManager
	MqttClient.setInputCallback(ProgramManager::input);
	MqttClient.setFocusCallback(ProgramManager::focus);
	MqttClient.setRebootCallback(0);
	MqttClient.init();
}

void loop(){
	MqttClient.loop();
	ProgramManager::render(tick);
	Hardware::display(ProgramManager::getFB());
	ArduinoOTA.handle();
	tick++;
	delay(1);
}
