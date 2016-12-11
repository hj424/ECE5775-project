//========================================================================
// Rasterizaton Header File
//========================================================================

#ifndef RASTERIZATION_H
#define RASTERIZATION_H


#include "typedefs.h"
#include "zculling.h"

/*
  Input: Three vertices x, y coordinates of a 2D triangle, its depth z and its color
*/
typedef struct 
{
  bit8   x0;
  bit8   y0;
  bit8   x1;
  bit8   y1;
  bit8   x2;
  bit8   y2;
  bit8   z;
} Triangle_2D;


bit8 find_max( bit8 in0, bit8 in1, bit8 in2 );

bit8 find_min( bit8 in0, bit8 in1, bit8 in2 );

bit1 pixel_in_triangle( bit8 x, bit8 y, Triangle_2D triangle_2d );

void clockwise_vertices( Triangle_2D *triangle_2d );

int check_clockwise( Triangle_2D triangle_2d );

/*
  rasterization function
*/

bit16 rasterization ( Triangle_2D triangle_2d, CandidatePixel fragment[] );

#endif /* RASTERIZATION_H*/
