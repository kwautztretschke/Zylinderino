#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include <Arduino.h>

#define LEDR 12
#define LEDG 14
#define LEDB 13

namespace Hardware{

int 		init();
void		display(uint8_t* fb);

}

#endif // __HARDWARE_H__