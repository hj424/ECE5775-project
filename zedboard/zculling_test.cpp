//========================================================================
// zculling_test
//========================================================================

#include <stdio.h>
#include <stdlib.h>

#include "zculling.h"

//------------------------------------------------------------------------
// verify_results
//------------------------------------------------------------------------
void test_fail (int n, bit8 val, bit8 ref){
   if(val != ref) printf("test fail\n");
}

void test_pass() {
   printf("test pass\n");
}

void verify_results( Pixel pixel, Pixel pixel_ref )
{

  if ( pixel.x != pixel_ref.x )
    test_fail( 0, pixel.x, pixel_ref.x );
  if ( pixel.y != pixel_ref.y )
    test_fail( 1, pixel.y, pixel_ref.y );
  if ( pixel.color != pixel_ref.color )
    test_fail( 2, pixel.color, pixel_ref.color );

}

//------------------------------------------------------------------------
// Test Harness
//------------------------------------------------------------------------


int main( int argc, char* argv[] )
{

  // z_buffer global variable
  bit8 z_buffer[MAX_X][MAX_Y];

  CandidatePixel fragments[] = {
  {0, 0, 20, 100},
  {1, 0, 20, 100},
  {2, 0, 20, 100},
  {3, 0, 20, 100},
  {4, 0, 20, 100},
  {5, 0, 20, 100},
  {6, 0, 20, 100},
  {7, 0, 20, 100},
  {1, 1, 20, 100},
  {2, 1, 20, 100},
  {3, 1, 20, 100},
  {4, 1, 20, 100},
  {5, 1, 20, 100},
  {6, 1, 20, 100},
  {7, 1, 20, 100},
  {2, 2, 20, 100},
  {3, 2, 20, 100},
  {4, 2, 20, 100},
  {5, 2, 20, 100},
  {6, 2, 20, 100},
  {7, 2, 20, 100},
  {3, 3, 20, 100},
  {4, 3, 20, 100},
  {5, 3, 20, 100},
  {6, 3, 20, 100},
  {7, 3, 20, 100},
  {4, 4, 20, 100},
  {5, 4, 20, 100},
  {6, 4, 20, 100},
  {7, 4, 20, 100},
  {5, 5, 20, 100},
  {6, 5, 20, 100},
  {7, 5, 20, 100},
  {6, 6, 20, 100},
  {7, 6, 20, 100},
  {7, 7, 20, 100},
  {0, 0, 30, 200},
  {1, 0, 30, 200},
  {2, 0, 30, 200},
  {3, 0, 30, 200},
  {4, 0, 30, 200},
  {5, 0, 30, 200},
  {6, 0, 30, 200},
  {7, 0, 30, 200},
  {0, 1, 30, 200},
  {1, 1, 30, 200},
  {2, 1, 30, 200},
  {3, 1, 30, 200},
  {4, 1, 30, 200},
  {5, 1, 30, 200},
  {6, 1, 30, 200},
  {0, 2, 30, 200},
  {1, 2, 30, 200},
  {2, 2, 30, 200},
  {3, 2, 30, 200},
  {4, 2, 30, 200},
  {5, 2, 30, 200},
  {0, 3, 30, 200},
  {1, 3, 30, 200},
  {2, 3, 30, 200},
  {3, 3, 30, 200},
  {4, 3, 30, 200},
  {0, 4, 30, 200},
  {1, 4, 30, 200},
  {2, 4, 30, 200},
  {3, 4, 30, 200},
  {0, 5, 30, 200},
  {1, 5, 30, 200},
  {2, 5, 30, 200},
  {0, 6, 30, 200},
  {1, 6, 30, 200},
  {0, 7, 30, 200},
};


  Pixel pixels[100];

  Pixel pixels_ref[] = {
  {0, 0, 100},
  {1, 0, 100},
  {2, 0, 100},
  {3, 0, 100},
  {4, 0, 100},
  {5, 0, 100},
  {6, 0, 100},
  {7, 0, 100},
  {1, 1, 100},
  {2, 1, 100},
  {3, 1, 100},
  {4, 1, 100},
  {5, 1, 100},
  {6, 1, 100},
  {7, 1, 100},
  {2, 2, 100},
  {3, 2, 100},
  {4, 2, 100},
  {5, 2, 100},
  {6, 2, 100},
  {7, 2, 100},
  {3, 3, 100},
  {4, 3, 100},
  {5, 3, 100},
  {6, 3, 100},
  {7, 3, 100},
  {4, 4, 100},
  {5, 4, 100},
  {6, 4, 100},
  {7, 4, 100},
  {5, 5, 100},
  {6, 5, 100},
  {7, 5, 100},
  {6, 6, 100},
  {7, 6, 100},
  {7, 7, 100},
  {0, 1, 200},
  {0, 2, 200},
  {1, 2, 200},
  {0, 3, 200},
  {1, 3, 200},
  {2, 3, 200},
  {0, 4, 200},
  {1, 4, 200},
  {2, 4, 200},
  {3, 4, 200},
  {0, 5, 200},
  {1, 5, 200},
  {2, 5, 200},
  {0, 6, 200},
  {1, 6, 200},
  {0, 7, 200}
};

  //z-buffer init
  for ( int y = 0; y < MAX_Y; y++ ) {
    for ( int x = 0; x < MAX_X; x++ ) { 
      z_buffer[y][x] = 255;
    }
  }


  bit16 size;
  size = zculling( z_buffer, fragments, pixels, 72 );

  printf("size: %d\n", (int)size );

  for ( int i = 0; i < size; ++i ) {

//    printf("{%d, %d, %d},\n", pixels[i].x, pixels[i].y, pixels[i].color );  
    verify_results( pixels[i], pixels_ref[i] );

  }

  test_pass();

  return 0;
}
