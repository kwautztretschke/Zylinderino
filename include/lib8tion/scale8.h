#ifndef __INC_LIB8TION_SCALE_H
#define __INC_LIB8TION_SCALE_H

#include "lib8tion/lib8tion.h"

uint8_t scale8( uint8_t i, fract8 scale);

///  The "video" version of scale8 guarantees that the output will
///  be only be zero if one or both of the inputs are zero.  If both
///  inputs are non-zero, the output is guaranteed to be non-zero.
///  This makes for better 'video'/LED dimming, at the cost of
///  several additional cycles.
uint8_t scale8_video( uint8_t i, fract8 scale);

/// scale three one byte values by a fourth one, which is treated as
///         the numerator of a fraction whose demominator is 256
///         In other words, it computes r,g,b * (scale / 256)
///
///         THIS FUNCTION ALWAYS MODIFIES ITS ARGUMENTS IN PLACE

void nscale8x3( uint8_t& r, uint8_t& g, uint8_t& b, fract8 scale);

/// scale three one byte values by a fourth one, which is treated as
///         the numerator of a fraction whose demominator is 256
///         In other words, it computes r,g,b * (scale / 256), ensuring
/// that non-zero values passed in remain non zero, no matter how low the scale
/// argument.
///
///         THIS FUNCTION ALWAYS MODIFIES ITS ARGUMENTS IN PLACE
void nscale8x3_video( uint8_t& r, uint8_t& g, uint8_t& b, fract8 scale);

///  scale two one byte values by a third one, which is treated as
///         the numerator of a fraction whose demominator is 256
///         In other words, it computes i,j * (scale / 256)
///
///         THIS FUNCTION ALWAYS MODIFIES ITS ARGUMENTS IN PLACE

void nscale8x2( uint8_t& i, uint8_t& j, fract8 scale);

///  scale two one byte values by a third one, which is treated as
///         the numerator of a fraction whose demominator is 256
///         In other words, it computes i,j * (scale / 256), ensuring
/// that non-zero values passed in remain non zero, no matter how low the scale
/// argument.
///
///         THIS FUNCTION ALWAYS MODIFIES ITS ARGUMENTS IN PLACE


void nscale8x2_video( uint8_t& i, uint8_t& j, fract8 scale);

/// scale a 16-bit unsigned value by an 8-bit value,
///         considered as numerator of a fraction whose denominator
///         is 256. In other words, it computes i * (scale / 256)

uint16_t scale16by8( uint16_t i, fract8 scale );

/// scale a 16-bit unsigned value by a 16-bit value,
///         considered as numerator of a fraction whose denominator
///         is 65536. In other words, it computes i * (scale / 65536)

uint16_t scale16( uint16_t i, fract16 scale );

///@defgroup Dimming Dimming and brightening functions
///
/// Dimming and brightening functions
///
/// The eye does not respond in a linear way to light.
/// High speed PWM'd LEDs at 50% duty cycle appear far
/// brighter then the 'half as bright' you might expect.
///
/// If you want your midpoint brightness leve (128) to
/// appear half as bright as 'full' brightness (255), you
/// have to apply a 'dimming function'.
///@{

/// Adjust a scaling value for dimming
uint8_t dim8_raw( uint8_t x);

/// Adjust a scaling value for dimming for video (value will never go below 1)
uint8_t dim8_video( uint8_t x);

/// Linear version of the dimming function that halves for values < 128
uint8_t dim8_lin( uint8_t x );

/// inverse of the dimming function, brighten a value
uint8_t brighten8_raw( uint8_t x);

/// inverse of the dimming function, brighten a value
uint8_t brighten8_video( uint8_t x);

/// inverse of the dimming function, brighten a value
uint8_t brighten8_lin( uint8_t x );

#endif
