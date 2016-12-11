//========================================================================
// Projection Header File
//========================================================================

#ifndef PROJECTION_H
#define PROJECTION_H

#include "typedefs.h"
#include "rasterization.h"

/*
  Input: Three vertices of a 3D triangle and its color
*/
typedef struct
{
  bit8   x0;
  bit8   y0;
  bit8   z0;
  bit8   x1;
  bit8   y1;
  bit8   z1;
  bit8   x2;
  bit8   y2;
  bit8   z2;
} Triangle_3D;


/*
  projection function
*/
void projection ( Triangle_3D triangle_3d, Triangle_2D *triangle_2d, bit2 angle );


#endif /* PROJECTION_H*/
