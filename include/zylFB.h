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
	/// allow assignment from one ARGB struct to another //? probably inheritable from CRGB?
	//inline zylPel& operator= (const zylPel& rhs) __attribute__((always_inline)) = default;

	/// constructor to set Alpha to max
	inline zylPel() : CRGB(){
		m_Alpha = 255;
	}

    /// allow assignment from 32-bit 0xAARRGGBB color code
	inline zylPel& operator= (const uint32_t colorcode) __attribute__((always_inline))
    {
		a = (colorcode >> 24) & 0xFF;
        r = (colorcode >> 16) & 0xFF;
        g = (colorcode >>  8) & 0xFF;
        b = (colorcode >>  0) & 0xFF;
        return *this;
    }
    /// allow assignment from Alpha, R, G, and B
	inline zylPel& setARGB (uint8_t na, uint8_t nr, uint8_t ng, uint8_t nb) __attribute__((always_inline))
    {
		a = na;
        r = nr;
        g = ng;
        b = nb;
        return *this;
    }

};

class zylFB {
private:
	zylPel				m_FB[X_RES][Y_RES];
public:
	zylPel&				xy(int x, int y){
		return m_FB[x][y];
	}
	void				setAll(zylPel c){
		for(int x=0;x<X_RES;x++)
			for(int y=0;y<X_RES;y++)
				m_FB[x][y]=c;
	}

	zylPel&				operator()(int x, int y)	{return xy(x,y);}
	void				operator=(zylPel c)			{setAll(c);}
	#if 0
	class _all{
		public:
		void operator= (zylPel c){
			setAll(c);
		}
	}; _all all;
	#endif
};

#endif