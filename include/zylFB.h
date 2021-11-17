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


#include <FastLED.h>

struct pelClass : CRGB {
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
	/// allow assignment from one ARGB struct to another
	//inline pelClass& operator= (const pelClass& rhs) __attribute__((always_inline)) = default;

    /// allow assignment from 32-bit 0xAARRGGBB color code
	inline pelClass& operator= (const uint32_t colorcode) __attribute__((always_inline))
    {
		a = (colorcode >> 24) & 0xFF;
        r = (colorcode >> 16) & 0xFF;
        g = (colorcode >>  8) & 0xFF;
        b = (colorcode >>  0) & 0xFF;
        return *this;
    }
    /// allow assignment from Alpha, R, G, and B
	inline pelClass& setARGB (uint8_t na, uint8_t nr, uint8_t ng, uint8_t nb) __attribute__((always_inline))
    {
		a = na;
        r = nr;
        g = ng;
        b = nb;
        return *this;
    }

};