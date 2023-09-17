#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include <Arduino.h>
#include <FastLED.h>

#define LEDR 12
#define LEDG 13
#define LEDB 14

namespace Hardware{

int 		init();
void		display(CRGB* fb, uint8_t brightness);
void		turnOff();

}

#endif // __HARDWARE_H__