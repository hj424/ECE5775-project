//========================================================================
// zculling
//========================================================================

#include "zculling.h"

/*
  Input:  fragements, array of candidata pixels for multiple triangles
  Input:  size,  
  Output: pixels, array of pixel
*/
bit16 zculling ( bit16 counter, CandidatePixel fragments[], Pixel pixels[], bit16 size )
{
  
  // initilize the z-buffer in rendering first triangle for an image
  static bit8 z_buffer[MAX_X][MAX_Y];
  if (counter == 1)
  {
     for ( int i = 0; i < MAX_X; i++)
    {
      for ( int j = 0; j < MAX_Y; j++)
      {
        z_buffer[i][j] = 255;
      }
    }
  }

  // pixel counter
  bit16 pixel_cntr = 0;
  
ZL1:
  // update z-buffer and pixels
  for ( int n = 0; n < size; n++ ) {
    if( fragments[n].z < z_buffer[fragments[n].y][fragments[n].x] ){
      pixels[pixel_cntr].x     = fragments[n].x;
      pixels[pixel_cntr].y     = fragments[n].y;
      pixels[pixel_cntr].color = fragments[n].color;
      pixel_cntr++;
      z_buffer[fragments[n].y][fragments[n].x] = fragments[n].z;
    }
  }   
  return pixel_cntr;
}

