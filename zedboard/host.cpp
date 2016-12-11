#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<math.h>
#include<assert.h>

#include<iostream>
#include<fstream>

#include "typedefs.h"
#include "timer.h"
// 3D triangles
#include "input.dat"
// number of values in framebuffer: 32 bits
#define NUM_FB MAX_X*MAX_Y

//--------------------------------------
// main function
//--------------------------------------
int main(int argc, char** argv)
{
  // Open channels to the FPGA board.
  // These channels appear as files to the Linux OS
  int fdr = open("/dev/xillybus_read_32", O_RDONLY);
  int fdw = open("/dev/xillybus_write_32", O_WRONLY);

  // Check that the channels are correctly opened
  if ((fdr < 0) || (fdw < 0)) {
    fprintf (stderr, "Failed to open Xillybus device channels\n");
    exit(-1);
  }
  
  // Number of 3D triangles
  const int N = num_3d_triangles;
  
  // Arrays to store test data and expected results
  bit32 extra;
  bit32 input[3*N];

  bit32 output;
  bit8 frame_buffer[NUM_FB];

  int nbytes;


  // Timer
  Timer timer("teapot FPGA");
    
  //////////////////////////////////////////////////////////////////////////////////////////////////////
  // build input array
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  extra(15,0)  = num_3d_triangles;
  extra(17,16) = angle;
  extra(31,18) = 0;
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

  //--------------------------------------------------------------------
  // send 3D triangles and read frambuffer
  //--------------------------------------------------------------------
    // send extra values: num_3d_triangles,angle
    nbytes = write (fdw, (void*)&extra, sizeof(extra));
    assert (nbytes == sizeof(extra));
    // send all 3D triangles to the module 
    for (int i=0; i < 3*N; i++ )
    {
      // send bytes through the write channel
      // and assert that the right number were sent
      nbytes = write (fdw, (void*)&input[i], sizeof(input[i]));
      assert (nbytes == sizeof(input[i]));
    }
    // read all results
    for (int i=0; i < NUM_FB/4; i++)
    {
      bit32 temp;
      // receive bytes through the read channel
      // and assert that the right number of ytes were received
      nbytes = read (fdr, (void*)&temp, sizeof(temp));
      assert (nbytes == sizeof(temp));
      frame_buffer[0+4*i] = temp(7,0);
      frame_buffer[1+4*i] = temp(15,8);
      frame_buffer[2+4*i] = temp(23,16);
      frame_buffer[3+4*i] = temp(31,24);
    }

    timer.stop();

    for(int i=MAX_X-1; i>=0; i--) {
      for(int j=0; j< MAX_Y; j++) {
        bit8 value = frame_buffer[MAX_X*j+i];
        if(value <10)
          std::cout << value << "  ";
        else if(value <100)
          std::cout << value  << " ";
        else if(value <1000)
          std::cout << value  << "";
      }
      std::cout << std::endl;
    }
    
    // Report overall error out of all testing instances
    std::cout << "Test finished.\n";
 
  return 0;
}
