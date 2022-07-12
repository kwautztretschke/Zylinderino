#ifndef __INC_LIB8TION_H
#define __INC_LIB8TION_H

#include <stdint.h>

// unspecified architecture, so
// no ASM, everything in C
#define QADD8_C 1
#define QADD7_C 1
#define QSUB8_C 1
#define SCALE8_C 1
#define SCALE16BY8_C 1
#define SCALE16_C 1
#define ABS8_C 1
#define MUL8_C 1
#define QMUL8_C 1
#define ADD8_C 1
#define SUB8_C 1
#define EASE8_C 1
#define AVG8_C 1
#define AVG7_C 1
#define AVG16_C 1
#define AVG15_C 1
#define BLEND8_C 1

///////////////////////////////////////////////////////////////////////
//
// typdefs for fixed-point fractional types.
//
// sfract7 should be interpreted as signed 128ths.
// fract8 should be interpreted as unsigned 256ths.
// sfract15 should be interpreted as signed 32768ths.
// fract16 should be interpreted as unsigned 65536ths.
//
// Example: if a fract8 has the value "64", that should be interpreted
//          as 64/256ths, or one-quarter.
//
//
//  fract8   range is 0 to 0.99609375
//                 in steps of 0.00390625
//
//  sfract7  range is -0.9921875 to 0.9921875
//                 in steps of 0.0078125
//
//  fract16  range is 0 to 0.99998474121
//                 in steps of 0.00001525878
//
//  sfract15 range is -0.99996948242 to 0.99996948242
//                 in steps of 0.00003051757
//

/// ANSI unsigned short _Fract.  range is 0 to 0.99609375
///                 in steps of 0.00390625
typedef uint8_t   fract8;   ///< ANSI: unsigned short _Fract

///  ANSI: signed short _Fract.  range is -0.9921875 to 0.9921875
///                 in steps of 0.0078125
typedef int8_t    sfract7;  ///< ANSI: signed   short _Fract

///  ANSI: unsigned _Fract.  range is 0 to 0.99998474121
///                 in steps of 0.00001525878
typedef uint16_t  fract16;  ///< ANSI: unsigned       _Fract

///  ANSI: signed _Fract.  range is -0.99996948242 to 0.99996948242
///                 in steps of 0.00003051757
typedef int16_t   sfract15; ///< ANSI: signed         _Fract


// accumXY types should be interpreted as X bits of integer,
//         and Y bits of fraction.
//         E.g., accum88 has 8 bits of int, 8 bits of fraction

typedef uint16_t  accum88;  ///< ANSI: unsigned short _Accum.  8 bits int, 8 bits fraction
typedef int16_t   saccum78; ///< ANSI: signed   short _Accum.  7 bits int, 8 bits fraction
typedef uint32_t  accum1616;///< ANSI: signed         _Accum. 16 bits int, 16 bits fraction
typedef int32_t   saccum1516;///< ANSI: signed         _Accum. 15 bits int, 16 bits fraction
typedef uint16_t  accum124; ///< no direct ANSI counterpart. 12 bits int, 4 bits fraction
typedef int32_t   saccum114;///< no direct ANSI counterpart. 1 bit int, 14 bits fraction


/// typedef for IEEE754 "binary32" float type internals
typedef union {
    uint32_t i;
    float    f;
    struct {
        uint32_t mantissa: 23;
        uint32_t exponent:  8;
        uint32_t signbit:   1;
    };
    struct {
        uint32_t mant7 :  7;
        uint32_t mant16: 16;
        uint32_t exp_  :  8;
        uint32_t sb_   :  1;
    };
    struct {
        uint32_t mant_lo8 : 8;
        uint32_t mant_hi16_exp_lo1 : 16;
        uint32_t sb_exphi7 : 8;
    };
} IEEE754binary32_t;


/// sfract15ToFloat: conversion from sfract15 fixed point to
///                  IEEE754 32-bit float.
float sfract15ToFloat( sfract15 y);

/// conversion from IEEE754 float in the range (-1,1)
///                  to 16-bit fixed point.  Note that the extremes of
///                  one and negative one are NOT representable.  The
///                  representable range is basically
sfract15 floatToSfract15( float f);

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
uint8_t lerp8by8( uint8_t a, uint8_t b, fract8 frac);

/// linear interpolation between two unsigned 16-bit values,
/// with 16-bit fraction
uint16_t lerp16by16( uint16_t a, uint16_t b, fract16 frac);

/// linear interpolation between two unsigned 16-bit values,
/// with 8-bit fraction
uint16_t lerp16by8( uint16_t a, uint16_t b, fract8 frac);

/// linear interpolation between two signed 15-bit values,
/// with 8-bit fraction
int16_t lerp15by8( int16_t a, int16_t b, fract8 frac);

/// linear interpolation between two signed 15-bit values,
/// with 8-bit fraction
int16_t lerp15by16( int16_t a, int16_t b, fract16 frac);

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
uint8_t map8( uint8_t in, uint8_t rangeStart, uint8_t rangeEnd);

///////////////////////////////////////////////////////////////////////
//
// easing functions; see http://easings.net
//

/// ease8InOutQuad: 8-bit quadratic ease-in / ease-out function
///                Takes around 13 cycles on AVR
uint8_t ease8InOutQuad( uint8_t i);

/// ease16InOutQuad: 16-bit quadratic ease-in / ease-out function
// C implementation at this point
uint16_t ease16InOutQuad( uint16_t i);

/// ease8InOutCubic: 8-bit cubic ease-in / ease-out function
///                 Takes around 18 cycles on AVR
fract8 ease8InOutCubic( fract8 i);

/// ease8InOutApprox: fast, rough 8-bit ease-in/ease-out function
///                   shaped approximately like 'ease8InOutCubic',
///                   it's never off by more than a couple of percent
///                   from the actual cubic S-curve, and it executes
///                   more than twice as fast.  Use when the cycles
///                   are more important than visual smoothness.
///                   Asm version takes around 7 cycles on AVR.

fract8 ease8InOutApprox( fract8 i);

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
uint8_t triwave8(uint8_t in);

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
uint8_t quadwave8(uint8_t in);

/// cubicwave8: cubic waveform generator.  Spends visibly more time
///             at the limits than 'sine' does.
uint8_t cubicwave8(uint8_t in);

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
uint8_t squarewave8( uint8_t in, uint8_t pulsewidth=128);

/// Template class for represneting fractional ints.
template<class T, int F, int I> class q {
    T i:I;
    T f:F;
public:
    q(float fx) { i = fx; f = (fx-i) * (1<<F); }
    q(uint8_t _i, uint8_t _f) {i=_i; f=_f; }
    uint32_t operator*(uint32_t v) { return (v*i) + ((v*f)>>F); }
    uint16_t operator*(uint16_t v) { return (v*i) + ((v*f)>>F); }
    int32_t operator*(int32_t v) { return (v*i) + ((v*f)>>F); }
    int16_t operator*(int16_t v) { return (v*i) + ((v*f)>>F); }
};

template<class T, int F, int I> uint32_t operator*(uint32_t v, q<T,F,I> & q) { return q * v; }
template<class T, int F, int I> uint16_t operator*(uint16_t v, q<T,F,I> & q) { return q * v; }
template<class T, int F, int I> int32_t operator*(int32_t v, q<T,F,I> & q) { return q * v; }
template<class T, int F, int I> int16_t operator*(int16_t v, q<T,F,I> & q) { return q * v; }

/// A 4.4 integer (4 bits integer, 4 bits fraction)
typedef q<uint8_t, 4,4> q44;
/// A 6.2 integer (6 bits integer, 2 bits fraction)
typedef q<uint8_t, 6,2> q62;
/// A 8.8 integer (8 bits integer, 8 bits fraction)
typedef q<uint16_t, 8,8> q88;
/// A 12.4 integer (12 bits integer, 4 bits fraction)
typedef q<uint16_t, 12,4> q124;


#endif
