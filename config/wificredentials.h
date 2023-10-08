#ifndef __WIFICREDENTIALS_H__
#define __WIFICREDENTIALS_H__

#include <WiFi.h>
#include "ZylOsConfig.h"

namespace wificredentials{
	const String 	ssid = 			"dummerhotspot";
	const String	password = 		"Amogus187";
	const IPAddress mqttServerIp = 	IPAddress(10,69,0,69);
	const String	deviceName = 	Z_DEVICE_NAME;
}


#endif // __WIFICREDENTIALS_H__