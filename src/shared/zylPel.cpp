/**
 * @file zylPel.cpp
 * @author  Bernhard Stoeffler
 * @brief 
 * @version 0.1
 * @date 2021-11-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "shared/zylPel.h"

#include "lib8tion/lib8tion.h"
#include "lib8tion/math8.h"
#include "lib8tion/scale8.h"
#include "lib8tion/hsv2rgb.h"

zylPel& zylPel::operator+= (const zylPel& rhs )
{
	r = qadd8( r, rhs.r);
	g = qadd8( g, rhs.g);
	b = qadd8( b, rhs.b);
	return *this;
}

zylPel& zylPel::setARGB (uint8_t na, uint8_t nr, uint8_t ng, uint8_t nb){
	a = na; r = nr; g = ng; b = nb; 
	return *this;
}

zylPel& zylPel::setAlpha (uint8_t na){
	a = na; 
	return *this;
}

zylPel& zylPel::setHue(uint8_t h){
	hsv2rgb_rainbow(this, h, 255, 255);
	return *this;
}

zylPel& zylPel::setHSV(uint8_t h, uint8_t s, uint8_t v){
	hsv2rgb_rainbow(this, h, s, v);
	return *this;
}

zylPel& zylPel::addToRGB(uint8_t d){
	r = qadd8(r, d);
	g = qadd8(g, d);
	b = qadd8(b, d);
	return *this;
}

zylPel& zylPel::subtractFromRGB(uint8_t d){
	r = qsub8(r, d);
	g = qsub8(g, d);
	b = qsub8(b, d);
	return *this;
}

zylPel& zylPel::nscale8(uint8_t scaledown){
	nscale8x3(r, g, b, scaledown);
	return *this;
}

zylPel zylPel::blend(const zylPel from, const zylPel to, uint8_t amount){
	if(amount == 0)
		return from;
	if(amount == 255)
		return to;
	return zylPel(
		scale8(from.r, 255-amount) + scale8(to.r, amount),
		scale8(from.g, 255-amount) + scale8(to.g, amount),
		scale8(from.b, 255-amount) + scale8(to.b, amount)
	);
}