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

#include "config.h"


//*************** Zylinder Pixel, mostly stolen from FastLED *************************
struct zylPel {
public:
	// color bytes unionized to be accessible via array or member syntax
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
	zylPel& operator= (const zylPel& rhs) = default;



	zylPel& setARGB (uint8_t na, uint8_t nr, uint8_t ng, uint8_t nb) {
		a = na; r = nr; g = ng; b = nb;}
	zylPel& setAlpha (uint8_t na) {a = na;}
};

class zylFB {
private:
	zylPel				m_FB[X_RES][Y_RES];
public:
	zylPel&				xy(int x, int y);
	void				setAll(zylPel c);
	void				setAlpha(uint8_t na);
	zylPel&				operator()(int x, int y);
	void				operator=(zylPel c);
	;					zylFB(zylPel c);
	;					zylFB();
};

#endif