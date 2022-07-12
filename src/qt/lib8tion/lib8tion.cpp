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


