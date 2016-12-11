//========================================================================
// Rendering_test
//========================================================================
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
// header files
#include "rendering.h"
#include "timer.h"
// 3D triangles 
#include "input.dat"
// number of values in frame buffer: 32 bits
#define NUM_FB MAX_X*MAX_Y/4

// main function
int main( int argc, char* argv[] )
{
  // input variables
  bit32 extra;
  bit32 input[3*num_3d_triangles];  
  // output values
  bit32 output;

  // output results
  std::ofstream outfile;
  outfile.open("out.dat");

  // HLS streams for commincation
  hls::stream<bit32> rendering_in;
  hls::stream<bit32> rendering_out;

  // frame buffer
  bit8 frame_buffer_print[MAX_X][MAX_Y];
  bit32 frame_buffer[NUM_FB];

  // initialize timer 
  Timer timer("Teapot FPGA");
  //------------------------------------------------------------------------
  // Test Single Triangle
  //------------------------------------------------------------------------

  printf("\nTest Start\n");
  
  //////////////////////////////////////////////////////////////////////////////////////////////////////
  // build input array
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  extra(15,0)  = num_3d_triangles;
  extra(17,16) = angle;
  for ( int i = 0; i < num_3d_triangles; i++)
  {
    input[3*i](7,0)     = triangle_3ds[i].x0;
    input[3*i](15,8)    = triangle_3ds[i].y0;
    input[3*i](23,16)   = triangle_3ds[i].z0;
    input[3*i](31,24)   = triangle_3ds[i].x1;
    input[3*i+1](7,0)   = triangle_3ds[i].y1;
    input[3*i+1](15,8)  = triangle_3ds[i].z1;
    input[3*i+1](23,16) = triangle_3ds[i].x2;
    input[3*i+1](31,24) = triangle_3ds[i].y2;
    input[3*i+2](7,0)   = triangle_3ds[i].z2;
    input[3*i+2](31,8)  = 0;
  }

  timer.start();
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  // send data to rendering
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  rendering_in.write ( extra );
  for ( int i = 0; i < 3*num_3d_triangles; i++)
  {
    rendering_in.write ( input[i] );
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////
  // Execute the rendering sim and receive data
  /////////////////////////////////////////////////////////////////////////////////////////////////
  bit32 temp;
  for (int k = 0; k < num_3d_triangles; k++)
  {
      dut ( rendering_in, rendering_out );  
  }
  // read result
  int i = 0,j = 0;
  for ( int n = 0; n < NUM_FB; n++)
  {
     temp = rendering_out.read();
     frame_buffer_print[i][j++] = temp(7,0);
     frame_buffer_print[i][j++] = temp(15,8);
     frame_buffer_print[i][j++] = temp(23,16);
     frame_buffer_print[i][j++] = temp(31,24);
     if(j == MAX_Y) i++;
  }

  timer.stop();

  // print result
  for ( int j = MAX_X-1; j >= 0; j--)
  {
    for ( int i = 0; i < MAX_Y; i++)
    {
      if (frame_buffer_print[i][j] < 10)
        std::cout << frame_buffer_print[i][j] << "  ";
      else if (frame_buffer_print[i][j] < 100)
        std::cout << frame_buffer_print[i][j] << " ";
      else if (frame_buffer_print[i][j] < 1000)
        std::cout << frame_buffer_print[i][j] << "";
    }
    std::cout << "\n";
  }

  return 0;   
}

