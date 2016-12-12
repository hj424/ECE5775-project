//========================================================================
// projection_test
//========================================================================
#include <stdio.h>
#include <stdlib.h>
#include "projection.h"
//------------------------------------------------------------------------
// Test Harness
//------------------------------------------------------------------------


int main( int argc, char* argv[] )
{
  // test single 3D triangles 
  Triangle_3D triangle_3d = { 0, 0, 10, 7, 0, 20, 7, 7, 30 };

  Triangle_2D triangle_2d;

  Triangle_2D front_ref = { 0,  0, 7,  0, 7,  7, 19 };
  Triangle_2D side_ref  = { 0, 10, 7, 20, 7, 30, 2  };
  Triangle_2D top_ref   = { 10, 0, 20, 0, 30, 7, 4  };
  // front view test
  projection( triangle_3d, &triangle_2d, 0 ); 
  printf("\nFront Test\n");
  if(triangle_2d.x0 == front_ref.x0 &&
     triangle_2d.y0 == front_ref.y0 &&
     triangle_2d.x1 == front_ref.x1 &&
     triangle_2d.y1 == front_ref.y1 &&
     triangle_2d.x2 == front_ref.x2 &&
     triangle_2d.y2 == front_ref.y2 &&
     triangle_2d.z  == front_ref.z)

     printf(" [pass]\n\n");
  else
     printf(" [Fail]\n\n");
  // vertical view test
  projection( triangle_3d, &triangle_2d, 1 );
  printf("Side Test\n");
  if(triangle_2d.x0 == side_ref.x0 &&
     triangle_2d.y0 == side_ref.y0 &&
     triangle_2d.x1 == side_ref.x1 &&
     triangle_2d.y1 == side_ref.y1 &&
     triangle_2d.x2 == side_ref.x2 &&
     triangle_2d.y2 == side_ref.y2 &&
     triangle_2d.z  == side_ref.z)
     printf(" [pass]\n\n");
  else
     printf(" [Fail]\n\n");
  // side view test
  projection( triangle_3d, &triangle_2d, 2 );
  printf("Top Test\n");
  if(triangle_2d.x0 == top_ref.x0 &&
     triangle_2d.y0 == top_ref.y0 &&
     triangle_2d.x1 == top_ref.x1 &&
     triangle_2d.y1 == top_ref.y1 &&
     triangle_2d.x2 == top_ref.x2 &&
     triangle_2d.y2 == top_ref.y2 &&
     triangle_2d.z  == top_ref.z)
     printf(" [pass]\n\n");
  else
     printf(" [Fail]\n\n");

  return 0;      
}


