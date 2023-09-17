#include <ArduinoOTA.h>
#include <PubSubClient.h>
#include <ArtnetWiFi.h>

#include "MqttClient.h"
#include "ProgramManager.h"
#include "Hardware.h"
#include "Fartnet.h"


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

	ArduinoOTA.setHostname(MqttClient.getDeviceName().c_str());
	ArduinoOTA.setPassword("swag");
	ArduinoOTA.begin();

	ProgramManager::init();
	ProgramManager::initPrograms();
	Hardware::init();

	Fartnet.setDmxCallback(ProgramManager::artnet);
	Fartnet.init(6454, 0);

	MqttClient.setPowerCallback(power);
	MqttClient.setBrightnessCallback(brightness);
	MqttClient.setColorCallback([](uint8_t *c){ProgramManager::setColor(CRGB(c[0], c[1], c[2]));});
	MqttClient.setInputCallback(ProgramManager::input);
	MqttClient.setFocusCallback(ProgramManager::focus);
	MqttClient.setRebootCallback(0);
	MqttClient.init();

	Serial.println("Setup complete!");
}

void loop(){
	MqttClient.loop();
	Fartnet.loop();
	ProgramManager::render(g_Tick);
	if (g_Power)
		Hardware::display(ProgramManager::getFB(), g_Brightness);
	else
		Hardware::turnOff();
	ArduinoOTA.handle();
	g_Tick++;
	delay(1);
}
