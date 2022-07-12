#ifndef __INC_NOISE8_H
#define __INC_NOISE8_H

#include "lib8tion/lib8tion.h"

uint16_t inoise16(uint32_t x, uint32_t y, uint32_t z);
uint16_t inoise16(uint32_t x, uint32_t y);
uint16_t inoise16(uint32_t x);

int16_t inoise16_raw(uint32_t x, uint32_t y, uint32_t z);
int16_t inoise16_raw(uint32_t x, uint32_t y);
int16_t inoise16_raw(uint32_t x);

uint8_t inoise8(uint16_t x, uint16_t y, uint16_t z);
uint8_t inoise8(uint16_t x, uint16_t y);
uint8_t inoise8(uint16_t x);

int8_t inoise8_raw(uint16_t x, uint16_t y, uint16_t z);
int8_t inoise8_raw(uint16_t x, uint16_t y);
int8_t inoise8_raw(uint16_t x);


#endif
