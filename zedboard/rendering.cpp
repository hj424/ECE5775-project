//======================================================================= 
// Rendering
//========================================================================
#include <iostream>
#include <fstream>
#include "rendering.h"
// global counter: number of rendering 3D triangles
bit16 counter = 0;
bit16 end = NUM_3D_TRI;
// static output: frame_buffer
static bit8 frame_buffer[MAX_X][MAX_Y];
// dut: top function
void dut (
    hls::stream<bit32> &strm_in,
    hls::stream<bit32> &strm_out
)
{
  // variables
  bit32 out_FB = 0;
  bit32 extra;
  bit16 num_3d_triangles;
  bit2 angle;

  // input extra values: number_3d_triangle and angle
  if ( counter == 0) 
  {
    extra = strm_in.read();
    num_3d_triangles = extra(15,0);
    angle = extra(17,16);
  }

  // 3D triangle;
  Triangle_3D triangle_3ds;

  // read all 3D triangles
  bit32 input_lo  = strm_in.read();
  bit32 input_mi  = strm_in.read();
  bit32 input_hi  = strm_in.read();

  triangle_3ds.x0 = input_lo(7,0);
  triangle_3ds.y0 = input_lo(15,8);
  triangle_3ds.z0 = input_lo(23,16);
  triangle_3ds.x1 = input_lo(31,24);
  triangle_3ds.y1 = input_mi(7,0);
  triangle_3ds.z1 = input_mi(15,8);
  triangle_3ds.x2 = input_mi(23,16);
  triangle_3ds.y2 = input_mi(31,24);
  triangle_3ds.z2 = input_hi(7,0);

  counter++;
  // call rendering function
  rendering (counter, triangle_3ds, angle); 
  // output frame buffer
  if (counter == end)
  {
    for ( int i = 0; i < MAX_X; i++)
    {
      for ( int j = 0; j < MAX_Y; j = j + 4)
      {
        out_FB(7,0)   = frame_buffer[i][j+0];
        out_FB(15,8)  = frame_buffer[i][j+1];
        out_FB(23,16) = frame_buffer[i][j+2];
        out_FB(31,24) = frame_buffer[i][j+3];
        strm_out.write(out_FB);
      }  
    }
    // clear counter for rendering next image
    counter = 0;   
  }
}
// rendering function
void rendering( bit16 counter, Triangle_3D triangle_3ds, bit2 angle ) 
{
  // variables
  Triangle_2D triangle_2ds;
  bit16 size_fragment;

  CandidatePixel fragment[500];
  bit16 size_pixels;

  Pixel pixels[500];

    /////////////////////////////////////////////////////////////////
    // 1st Stage Projection
    ///////////////////////////////////////////////////////////////////
    projection( triangle_3ds, &triangle_2ds, angle );

    ////////////////////////////////////////////////////////////////
    // 2nd Stage Rasterization
    // ////////////////////////////////////////////////////////////
    size_fragment = rasterization( triangle_2ds, fragment );

    /////////////////////////////////////////////////////////////////
    // 3rd Stage Z-culling
    // /////////////////////////////////////////////////////////////
    size_pixels = zculling( counter, fragment, pixels, size_fragment );

    //////////////////////////////////////////////////////////////
    // coloring frame buffer
    //////////////////////////////////////////////////////////////
    coloringFB ( counter, size_pixels, pixels, frame_buffer);
}
