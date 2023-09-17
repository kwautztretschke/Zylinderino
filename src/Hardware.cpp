#include "Hardware.h"
#include <ws2812_i2s.h>
#include "ZylOsConfig.h"

namespace Hardware{

static WS2812 leds;
static Pixel_t pixels[FB_SIZE];


int init(){
	leds.init(FB_SIZE);
	return 0;
}

void display(CRGB* fb, uint8_t brightness){
	for(int i=0;i<FB_SIZE;i++){
		pixels[i].R = fb[i].r;
		pixels[i].G = fb[i].g;
		pixels[i].B = fb[i].b;
	}
	leds.show(pixels);
}

void turnOff(){
	memset(pixels, 0, sizeof(Pixel_t)*FB_SIZE);
	leds.show(pixels);
}

}