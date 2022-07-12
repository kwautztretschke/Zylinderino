#ifndef __INC_LIB8TION_RANDOM_H
#define __INC_LIB8TION_RANDOM_H

#include "lib8tion/lib8tion.h"

///@ingroup lib8tion

///@defgroup Random Fast random number generators
/// Fast 8- and 16- bit unsigned random numbers.
///  Significantly faster than Arduino random(), but
///  also somewhat less random.  You can add entropy.
///@{

// X(n+1) = (2053 * X(n)) + 13849)
#define FASTLED_RAND16_2053  ((uint16_t)(2053))
#define FASTLED_RAND16_13849 ((uint16_t)(13849))

#define APPLY_FASTLED_RAND16_2053(x) (x * FASTLED_RAND16_2053)

/// random number seed
#define RAND16_SEED  1337

/// Generate an 8-bit random number
uint8_t random8();

/// Generate a 16 bit random number
uint16_t random16();

/// Generate an 8-bit random number between 0 and lim
/// @param lim the upper bound for the result
uint8_t random8(uint8_t lim);

/// Generate an 8-bit random number in the given range
/// @param min the lower bound for the random number
/// @param lim the upper bound for the random number
uint8_t random8(uint8_t min, uint8_t lim);

/// Generate an 16-bit random number between 0 and lim
/// @param lim the upper bound for the result
uint16_t random16( uint16_t lim);

/// Generate an 16-bit random number in the given range
/// @param min the lower bound for the random number
/// @param lim the upper bound for the random number
uint16_t random16( uint16_t min, uint16_t lim);

/// Set the 16-bit seed used for the random number generator
void random16_set_seed( uint16_t seed);

/// Get the current seed value for the random number generator
uint16_t random16_get_seed();

/// Add entropy into the random number generator
void random16_add_entropy( uint16_t entropy);

#endif
