
//========================================================================
// z culling Header File
//========================================================================

#ifndef ZCULLING_H
#define ZCULLING_H

#ifndef MAX_X
#define MAX_X 256
#endif

#ifndef MAX_Y
#define MAX_Y 256
#endif

#include "typedefs.h"

/*
  Input: Fragment, which is an array of candidate pixels 
*/
typedef struct
{
  bit8   x;
  bit8   y;
  bit8   z;
  bit8   color;
} CandidatePixel;

/*
  Output: Colored pixel 
*/
typedef struct
{
  bit8   x;
  bit8   y;
  bit8   color;
} Pixel;

/*
  z_culling function
*/
bit16 zculling ( bit16 counter, CandidatePixel fragments[], Pixel pixels[], bit16 size );


#endif /* ZCULLING_H*/
