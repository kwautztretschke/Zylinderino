#include <ArduinoOTA.h>
#include <PubSubClient.h>
#include <ArtnetWiFi.h>

#include "MqttClient.h"
#include "ProgramManager.h"
#include "Hardware.h"

ArtnetWiFiReceiver ArtNet;


long g_Tick = 0;

bool g_Power = true;
uint8_t g_Brightness = 255;

void power(bool power){
	g_Power = power;
}

void brightness(uint8_t brightness){
	g_Brightness = brightness;
}

void setup(){
	// start communication
	Serial.begin(115200);
	MqttClient.startWiFi();
	Serial.println("Wifi set up");

	// init other stuff
	ArduinoOTA.setHostname(MqttClient.getDeviceName().c_str());
	ArduinoOTA.setPassword("swag");
	ArduinoOTA.begin();
	ProgramManager::init();
	ProgramManager::initPrograms();
	Hardware::init();
	ArtNet.begin();
	Serial.println("OTA, zylOs, Artnet and Hardware initialized");

	// init MqttClient and set callbacks to ProgramManager
	MqttClient.setPowerCallback(power);
	MqttClient.setBrightnessCallback(brightness);
	MqttClient.setColorCallback(ProgramManager::setColor);
	MqttClient.setInputCallback(ProgramManager::input);
	MqttClient.setFocusCallback(ProgramManager::focus);
	MqttClient.setRebootCallback(0);
	MqttClient.init();
	ArtNet.subscribe(0, ProgramManager::artnet);
	Serial.println("Setup complete!");
}

void loop(){
	MqttClient.loop();
	ProgramManager::render(g_Tick);
	if (g_Power)
		Hardware::display(ProgramManager::getFB(), g_Brightness);
	else
		Hardware::turnOff();
	ArduinoOTA.handle();
	g_Tick++;
	delay(1);
}
