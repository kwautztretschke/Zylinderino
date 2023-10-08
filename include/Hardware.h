#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include <Arduino.h>
#include <FastLED.h>
#include "ZylOsConfig.h"

namespace Hardware{

int 		init();
void		display(CRGB fb[X_RES][Y_RES], uint8_t brightness);
void		turnOff();
int			getDipSwitch(int num);

}

#endif // __HARDWARE_H__