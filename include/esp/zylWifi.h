/**
 * @file zylWifi.h
 * @author Bernhard Stöffler
 * @brief 
 * @version 0.1
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __ZYLWIFI_H_
#define __ZYLWIFI_H_

#include <WiFi.h>
#include <WiFiUdp.h>
#include "WiFiAutoSelector.h"
#include <ArduinoOTA.h>
#include "config.h"

#define WIFI_CONNECT_TIMEOUT 		8000
#ifdef Z_LEO
  	#define PUPBUFFER_SIZE			5				//PUP size, 5 -> with Signature
	#define PUP_SIGNATURE			69				//5th PUP byte has to be this
#endif 
#ifdef Z_BERNIE
  	#define PUPBUFFER_SIZE			4				//PUP size, 4 -> no Signature
#endif

enum zylWifiMode{
	ZWM_HOST 	= 0,
	ZWM_CLIENT 	= 1
};

class zylWifi{
private:
	WiFiAutoSelector	m_WAS;
	zylWifiMode			m_Mode;
public:
	int		 			init(zylWifiMode mode);
	int					handle();
	;					zylWifi();
};

class zylUdp{
private:
	WiFiUDP				m_Udp;
	char				m_aPupBuffer[PUPBUFFER_SIZE];
public:
	int					init(int port);
	int					read(uint8_t* opcode, uint8_t* x, uint8_t* y, uint8_t* z);
	int					verifyPacket();
};

int initOTA();

#endif