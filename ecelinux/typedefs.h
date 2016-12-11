//===========================================================================
// typedefs.h
//===========================================================================
// @brief: This header defines the shorthand of several ap_uint data types.

#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include "ap_int.h"

typedef ap_uint<1> bit1;
typedef ap_uint<2> bit2;
typedef ap_uint<8> bit8;
typedef ap_int<16>  s_bit8;   
typedef ap_int<9>  bit9;
typedef ap_uint<16> bit16;
typedef ap_uint<32> bit32;

// number of triangles rendering in the hardware
#define NUM_3D_TRI 3192

#endif
