#ifndef __INC_HSV2RGB_H
#define __INC_HSV2RGB_H

#include "lib8tion/lib8tion.h"
#include "shared/zylPel.h"

// dont ask why these are defines. I have no idea.
#define K255 255
#define K171 171
#define K170 170
#define K85  85

void hsv2rgb_rainbow(zylPel *rgb, const uint8_t hue, uint8_t sat, uint8_t val);

#endif