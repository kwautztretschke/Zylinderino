/**
 * @file zylPel.h
 * @author Bernhard Stoeffler
 * @brief 
 * @version 0.1
 * @date 2021-11-17
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef __ZYLPEL_H_
#define __ZYLPEL_H_

#include "shared/config.h"


struct zylPel {
public:
	// color bytes unionized to be accessible via array or member syntax
			//? why tho, is this ever used? all it does is throw warnings
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
	//****** constructors  *********************************************************
	zylPel() = default;
	zylPel(const zylPel& rhs) = default;
	zylPel(uint8_t ir, uint8_t ig, uint8_t ib) : a(255), r(ir), g(ig), b(ib) {}
	zylPel(uint8_t ia, uint8_t ir, uint8_t ig, uint8_t ib) : a(ia), r(ir), g(ig), b(ib) {}

	//***** operators *************************************************************
	zylPel& operator=  (const zylPel& rhs) = default;
	zylPel& operator+= (const zylPel& rhs);

	//***** methods (mostly stolen from FastLED) **********************************
	zylPel& 		setARGB(uint8_t na, uint8_t nr, uint8_t ng, uint8_t nb); 
	zylPel& 		setAlpha(uint8_t na);
	zylPel& 		setHue(uint8_t h);
	zylPel& 		setHSV(uint8_t h, uint8_t s, uint8_t v);
	zylPel& 		addToRGB(uint8_t d);
	zylPel& 		subtractFromRGB(uint8_t d);
	zylPel& 		nscale8(uint8_t scaledown);
	static zylPel 	blend(const zylPel from, const zylPel to, const uint8_t amount);
};

#endif