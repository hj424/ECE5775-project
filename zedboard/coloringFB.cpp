////////////////////////////////////////////////////////
// coloring the frame buffer
///////////////////////////////////////////////////////
#include "zculling.h" 

void coloringFB(bit16 counter,  bit16 size_pixels, Pixel pixels[], bit8 frame_buffer[MAX_X][MAX_Y])
{
  if ( counter == 0 )
  {
    // initilize the  frame_buffer for a new image
    for ( int i = 0; i < MAX_X; i++)
    {
      for ( int j = 0; j < MAX_Y; j++)
        frame_buffer[i][j] = 0;
    }
  }
// update the framebuffer
CL1:
  for ( int i = 0; i < size_pixels; i++)
  {
    frame_buffer[ pixels[i].x ][ pixels[i].y ] = pixels[i].color;
  }
}
