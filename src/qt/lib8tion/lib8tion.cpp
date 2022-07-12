#include "qt/lib8tion/lib8tion.h"
#include "qt/lib8tion/scale8.h"

#include <string.h>

/// sfract15ToFloat: conversion from sfract15 fixed point to
///                  IEEE754 32-bit float.
float sfract15ToFloat( sfract15 y)
{
    return y / 32768.0;
}

/// conversion from IEEE754 float in the range (-1,1)
///                  to 16-bit fixed point.  Note that the extremes of
///                  one and negative one are NOT representable.  The
///                  representable range is basically
sfract15 floatToSfract15( float f)
{
    return f * 32768.0;
}


///////////////////////////////////////////////////////////////////////
//
// linear interpolation, such as could be used for Perlin noise, etc.
//

// A note on the structure of the lerp functions:
// The cases for b>a and b<=a are handled separately for
// speed: without knowing the relative order of a and b,
// the value (a-b) might be overflow the width of a or b,
// and have to be promoted to a wider, slower type.
// To avoid that, we separate the two cases, and are able
// to do all the math in the same width as the arguments,
// which is much faster and smaller on AVR.

/// linear interpolation between two unsigned 8-bit values,
/// with 8-bit fraction
uint8_t lerp8by8( uint8_t a, uint8_t b, fract8 frac)
{
    uint8_t result;
    if( b > a) {
        uint8_t delta = b - a;
        uint8_t scaled = scale8( delta, frac);
        result = a + scaled;
    } else {
        uint8_t delta = a - b;
        uint8_t scaled = scale8( delta, frac);
        result = a - scaled;
    }
    return result;
}

/// linear interpolation between two unsigned 16-bit values,
/// with 16-bit fraction
uint16_t lerp16by16( uint16_t a, uint16_t b, fract16 frac)
{
    uint16_t result;
    if( b > a ) {
        uint16_t delta = b - a;
        uint16_t scaled = scale16(delta, frac);
        result = a + scaled;
    } else {
        uint16_t delta = a - b;
        uint16_t scaled = scale16( delta, frac);
        result = a - scaled;
    }
    return result;
}

/// linear interpolation between two unsigned 16-bit values,
/// with 8-bit fraction
uint16_t lerp16by8( uint16_t a, uint16_t b, fract8 frac)
{
    uint16_t result;
    if( b > a) {
        uint16_t delta = b - a;
        uint16_t scaled = scale16by8( delta, frac);
        result = a + scaled;
    } else {
        uint16_t delta = a - b;
        uint16_t scaled = scale16by8( delta, frac);
        result = a - scaled;
    }
    return result;
}

/// linear interpolation between two signed 15-bit values,
/// with 8-bit fraction
int16_t lerp15by8( int16_t a, int16_t b, fract8 frac)
{
    int16_t result;
    if( b > a) {
        uint16_t delta = b - a;
        uint16_t scaled = scale16by8( delta, frac);
        result = a + scaled;
    } else {
        uint16_t delta = a - b;
        uint16_t scaled = scale16by8( delta, frac);
        result = a - scaled;
    }
    return result;
}

/// linear interpolation between two signed 15-bit values,
/// with 8-bit fraction
int16_t lerp15by16( int16_t a, int16_t b, fract16 frac)
{
    int16_t result;
    if( b > a) {
        uint16_t delta = b - a;
        uint16_t scaled = scale16( delta, frac);
        result = a + scaled;
    } else {
        uint16_t delta = a - b;
        uint16_t scaled = scale16( delta, frac);
        result = a - scaled;
    }
    return result;
}

///  map8: map from one full-range 8-bit value into a narrower
/// range of 8-bit values, possibly a range of hues.
///
/// E.g. map myValue into a hue in the range blue..purple..pink..red
/// hue = map8( myValue, HUE_BLUE, HUE_RED);
///
/// Combines nicely with the waveform functions (like sin8, etc)
/// to produce continuous hue gradients back and forth:
///
///          hue = map8( sin8( myValue), HUE_BLUE, HUE_RED);
///
/// Mathematically simiar to lerp8by8, but arguments are more
/// like Arduino's "map"; this function is similar to
///
///          map( in, 0, 255, rangeStart, rangeEnd)
///
/// but faster and specifically designed for 8-bit values.
uint8_t map8( uint8_t in, uint8_t rangeStart, uint8_t rangeEnd)
{
    uint8_t rangeWidth = rangeEnd - rangeStart;
    uint8_t out = scale8( in, rangeWidth);
    out += rangeStart;
    return out;
}


///////////////////////////////////////////////////////////////////////
//
// easing functions; see http://easings.net
//

/// ease8InOutQuad: 8-bit quadratic ease-in / ease-out function
///                Takes around 13 cycles on AVR
uint8_t ease8InOutQuad( uint8_t i)
{
    uint8_t j = i;
    if( j & 0x80 ) {
        j = 255 - j;
    }
    uint8_t jj  = scale8(  j, j);
    uint8_t jj2 = jj << 1;
    if( i & 0x80 ) {
        jj2 = 255 - jj2;
    }
    return jj2;
}

/// ease16InOutQuad: 16-bit quadratic ease-in / ease-out function
// C implementation at this point
uint16_t ease16InOutQuad( uint16_t i)
{
    uint16_t j = i;
    if( j & 0x8000 ) {
        j = 65535 - j;
    }
    uint16_t jj  = scale16( j, j);
    uint16_t jj2 = jj << 1;
    if( i & 0x8000 ) {
        jj2 = 65535 - jj2;
    }
    return jj2;
}


/// ease8InOutCubic: 8-bit cubic ease-in / ease-out function
///                 Takes around 18 cycles on AVR
fract8 ease8InOutCubic( fract8 i)
{
    uint8_t ii  = scale8(  i, i);
    uint8_t iii = scale8( ii, i);

    uint16_t r1 = (3 * (uint16_t)(ii)) - ( 2 * (uint16_t)(iii));

    /* the code generated for the above *'s automatically
       cleans up R1, so there's no need to explicitily call
       cleanup_R1(); */

    uint8_t result = r1;

    // if we got "256", return 255:
    if( r1 & 0x100 ) {
        result = 255;
    }
    return result;
}

/// ease8InOutApprox: fast, rough 8-bit ease-in/ease-out function
///                   shaped approximately like 'ease8InOutCubic',
///                   it's never off by more than a couple of percent
///                   from the actual cubic S-curve, and it executes
///                   more than twice as fast.  Use when the cycles
///                   are more important than visual smoothness.
///                   Asm version takes around 7 cycles on AVR.

fract8 ease8InOutApprox( fract8 i)
{
    if( i < 64) {
        // start with slope 0.5
        i /= 2;
    } else if( i > (255 - 64)) {
        // end with slope 0.5
        i = 255 - i;
        i /= 2;
        i = 255 - i;
    } else {
        // in the middle, use slope 192/128 = 1.5
        i -= 64;
        i += (i / 2);
        i += 32;
    }

    return i;
}

/// triwave8: triangle (sawtooth) wave generator.  Useful for
///           turning a one-byte ever-increasing value into a
///           one-byte value that oscillates up and down.
///
///           input         output
///           0..127        0..254 (positive slope)
///           128..255      254..0 (negative slope)
///
/// On AVR this function takes just three cycles.
///
uint8_t triwave8(uint8_t in)
{
    if( in & 0x80) {
        in = 255 - in;
    }
    uint8_t out = in << 1;
    return out;
}


// quadwave8 and cubicwave8: S-shaped wave generators (like 'sine').
//           Useful for turning a one-byte 'counter' value into a
//           one-byte oscillating value that moves smoothly up and down,
//           with an 'acceleration' and 'deceleration' curve.
//
//           These are even faster than 'sin8', and have
//           slightly different curve shapes.
//

/// quadwave8: quadratic waveform generator.  Spends just a little more
///            time at the limits than 'sine' does.
uint8_t quadwave8(uint8_t in)
{
    return ease8InOutQuad( triwave8( in));
}

/// cubicwave8: cubic waveform generator.  Spends visibly more time
///             at the limits than 'sine' does.
uint8_t cubicwave8(uint8_t in)
{
    return ease8InOutCubic( triwave8( in));
}

/// squarewave8: square wave generator.  Useful for
///           turning a one-byte ever-increasing value
///           into a one-byte value that is either 0 or 255.
///           The width of the output 'pulse' is
///           determined by the pulsewidth argument:
///
///~~~
///           If pulsewidth is 255, output is always 255.
///           If pulsewidth < 255, then
///             if input < pulsewidth  then output is 255
///             if input >= pulsewidth then output is 0
///~~~
///
/// the output looking like:
///
///~~~
///     255   +--pulsewidth--+
///      .    |              |
///      0    0              +--------(256-pulsewidth)--------
///~~~
///
/// @param in
/// @param pulsewidth
/// @returns square wave output
uint8_t squarewave8( uint8_t in, uint8_t pulsewidth)
{
    if( in < pulsewidth || (pulsewidth == 255)) {
        return 255;
    } else {
        return 0;
    }
}

