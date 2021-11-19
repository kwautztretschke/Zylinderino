/**
 * @file zylFB.h
 * @author Bernhard Stoeffler
 * @brief 
 * @version 0.1
 * @date 2021-11-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __ZYLFB_H_
#define __ZYLFB_H_

#include <FastLED.h>
#include "config.h"


//*************** Zylinder Pixel, inherited from FastLED *************************
//				  (Syntax is also inherited, hence the inline functions)
struct zylPel : CRGB {
    union {
		struct {
            union {
                uint8_t     r;
                uint8_t     red;
                uint8_t     m_Red;
            };
            union {
                uint8_t     g;
                uint8_t 	green;
                uint8_t 	m_Green;
            };
            union {
                uint8_t 	b;
                uint8_t 	blue;
                uint8_t 	m_Blue;
            };
            union{
                uint8_t     a;
                uint8_t     alpha;
                uint8_t     m_Alpha;
            };
        };
		uint8_t raw[4];
	};
    /// allow assignment from Alpha, R, G, and B
	inline zylPel& setARGB (uint8_t na, uint8_t nr, uint8_t ng, uint8_t nb) __attribute__((always_inline)){
		a = na; r = nr; g = ng; b = nb;
        return *this;
    }

	inline zylPel& setAlpha (uint8_t na) __attribute__((always_inline)){
		a = na;
		return *this;
	}

	//? Apparently operators and constructors dont get inherited so here we go
	inline zylPel(uint32_t colorcode) : CRGB(colorcode)
		{a = 255;}
	inline zylPel(CRGB c) : CRGB(c)
		{a = 255;}
	inline zylPel(uint8_t ir, uint8_t ig, uint8_t ib, uint8_t ia = 255) : CRGB(ir, ig, ib) 
		{a = ia;}
	inline zylPel(const zylPel& rhs) = default;

	inline zylPel& operator= (const zylPel& rhs) = default;
	inline zylPel& operator= (const uint32_t colorcode){*this = zylPel(colorcode);}
	inline zylPel& operator= (const CRGB rhs){*this = zylPel(rhs);}
};

class zylFB {
private:
	zylPel				m_FB[X_RES][Y_RES];
public:
	zylPel&				xy(int x, int y);
	void				setAll(CRGB c);
	void				setAlpha(uint8_t na);
	zylPel&				operator()(int x, int y);
	void				operator=(CRGB c);
	;					zylFB(CRGB c);
	;					zylFB();

	void				test(){
		xy(0, 0) = CRGB::Red;
		xy(0, 0).addToRGB(5);
	}

};

#endif