/**
 * @file config.h
 * @author Bernhard Stöffler
 * @brief 
 * @version 0.1
 * @date 2021-11-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __CONFIG_H_
#define __CONFIG_H_

#include "wificredentials.h"

#define DEBUG
#undef ARDUINO

#ifdef DEBUG
	#ifndef ARDUINO
		#include <stdio.h>
		#include <stdint.h>
  		#define DPRINT printf
	#else
		#define DPRINT Serial.printf
	#endif
#else
	#define DPRINT //
#endif

#define PUP_PORT 				26091				//UDP port for receiving PUP commands
#define TEXT_PORT 				26092				//UDP port for receiving plaintext
#define AP_NAME 				"Zylinder"			//SoftAP SSID name
#define AP_PSWD 				"papatastisch"		//SoftAP Password
#define RESCUE_SSID				"rescue"			//Open a Hotspot on your phone with these parameters
#define RESCUE_PSWD				"rescue"
#define MAX_COLORS				8					//available colors, if too low might cause crashes

#define ZPM_DEFAULT_PROGRAM 	1					//focuses this program after initing. uncomment this for default

#ifdef Z_LEO
  #define X_RES 				48                  //Resolution in x direction
  #define Y_RES 				7                   //Resolution in y direction
  #define NUM_LEDS 				(X_RES * Y_RES)     //Total number of Leds
  #define DATA_PIN 				13                  //Led data pin
  #define TARGET_FRAME_RATE 	60                  //global hat frame rate
  #define PUPBUFFER_SIZE		5					//PUP size, 5 -> with Signature
  #define OTA_HOSTNAME 			"Zylinderino-Leo"
  #define OTA_PASSWORDHASH		"a1d237e74e5ce5c1f4584da49afeb5f7"

#else
  #ifndef Z_BERNIE
    #define Z_BERNIE
  #endif
  #define X_RES 				35                  //Resolution in x direction (maximum)
  #define Y_RES 				8                   //Resolution in y direction
  #define HARDWAREBACKEND		zylHW_Bernie		//class derived from zylHW
  #define TARGET_FRAME_RATE 	60                  //global hat frame rate
  #define OTA_HOSTNAME 			"bernie-zylinder"
  #define OTA_PASSWORD			"swag"
#endif

#endif