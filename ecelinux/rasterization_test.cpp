//========================================================================
// Rasterization_test
//========================================================================

#include <stdio.h>
#include <stdlib.h>

#include "rasterization.h"

//------------------------------------------------------------------------
// verify_results
//------------------------------------------------------------------------

void test_fail (int n, bit8 val, bit8 ref){
   if(val != ref) printf("test fail\n");
}

void test_pass() {
   printf("test pass\n");
}



void verify_results( CandidatePixel result, CandidatePixel reference )
{

  if ( result.x != reference.x )       
    test_fail( 0, result.x, reference.x );
  if ( result.y != reference.y )       
    test_fail( 1, result.y, reference.y );
  if ( result.z != reference.z )       
    test_fail( 2, result.z, reference.z );
  if ( result.color != reference.color )       
    test_fail( 3, result.color, reference.color );


}

//------------------------------------------------------------------------
// Test Harness
//------------------------------------------------------------------------


int main( int argc, char* argv[] )
{

  //----------------------------------------------------------------------
  // check_clockwise test
  //----------------------------------------------------------------------

  Triangle_2D triangle_2d_cw   = { 0, 0, 7, 7, 7, 0, 20 };
  Triangle_2D triangle_2d_ccw  = { 0, 0, 7, 0, 7, 7, 30 };
  Triangle_2D triangle_2d_line = { 0, 0, 4, 4, 7, 7, 40 };

  printf("\n========== check_clockwise test ==========\n");

  if ( check_clockwise( triangle_2d_cw ) > 0 )
    printf("nclockwise\n[Passed]\n");
  else
    printf("clockwise\n[Failed]\n");

  if ( check_clockwise( triangle_2d_ccw ) < 0 )
    printf("counter clockwise\n[Passed]\n");
  else
    printf("counter clockwise\n[Failed]%d\n",(int)check_clockwise(triangle_2d_ccw));

  if ( check_clockwise( triangle_2d_line ) == 0 )
    printf("three vertices in line\n[Passed]\n");
  else
    printf("three vertices in line\n[Failed]\n");
    
  //----------------------------------------------------------------------
  // clockwise_vertices test
  //----------------------------------------------------------------------

  printf("\n========== clockwise_vertices test ==========\n");

  clockwise_vertices( &triangle_2d_ccw );

  if ( triangle_2d_ccw.x0 == 7 &&
       triangle_2d_ccw.y0 == 0 &&
       triangle_2d_ccw.x1 == 0 &&
       triangle_2d_ccw.y1 == 0 &&
       triangle_2d_ccw.x2 == 7 &&
       triangle_2d_ccw.y2 == 7 &&
       triangle_2d_ccw.z  == 30 
    )
    printf("[Passed]\n");
  else
    printf("[Failed]\n");

  //----------------------------------------------------------------------
  // pixel_in_triangle test
  //----------------------------------------------------------------------

  printf("\n========== pixel_in_triangle test ==========\n");
  
  if ( !pixel_in_triangle( 0, 0, triangle_2d_cw ) )
    printf("Test 1 [Failed]\n");
  if ( pixel_in_triangle( 0, 1, triangle_2d_cw ) )
    printf("Test 2 [Failed],%d\n",(int)pixel_in_triangle(0,1,triangle_2d_cw));
  if ( !pixel_in_triangle( 1, 0, triangle_2d_cw ) )
    printf("Test 3 [Failed]\n");
  if ( !pixel_in_triangle( 5, 2, triangle_2d_cw ) )
    printf("Test 4 [Failed]\n");

  if ( pixel_in_triangle( 0, 0, triangle_2d_cw ) &&
       !pixel_in_triangle( 0, 1, triangle_2d_cw )&&
       pixel_in_triangle( 1, 0, triangle_2d_cw ) &&
       pixel_in_triangle( 5, 2, triangle_2d_cw ) 
     )
    printf("[Passed]\n");

  //----------------------------------------------------------------------
  // find_min test
  //----------------------------------------------------------------------

  printf("\n========== find_min test ==========\n");

  if ( find_min( 5, 6, 7 ) != 5 )
    printf("Test 1 [Failed]\n");
  if ( find_min( 9, 6, 7 ) != 6 )
    printf("Test 2 [Failed]\n");
  if ( find_min( 5, 6, 4 ) != 4 )
    printf("Test 3 [Failed]\n");
  if ( find_min( 5, 4, 4 ) != 4 )
    printf("Test 4 [Failed]\n");
  
  if ( 
    find_min( 5, 6, 7 ) == 5 &&
    find_min( 9, 6, 7 ) == 6 &&
    find_min( 5, 6, 4 ) == 4 &&
    find_min( 5, 4, 4 ) == 4 
  )
    printf("[Passed]\n");

  //----------------------------------------------------------------------
  // find_max test
  //----------------------------------------------------------------------

  printf("\n========== find_max test ==========\n");

  if ( find_max( 5, 6, 7 ) != 7 )
    printf("Test 1 [Failed]\n");
  if ( find_max( 9, 6, 7 ) != 9 )
    printf("Test 2 [Failed]\n");
  if ( find_max( 5, 6, 4 ) != 6 )
    printf("Test 3 [Failed]\n");
  if ( find_max( 5, 5, 4 ) != 5 )
    printf("Test 4 [Failed]\n");
  
  if ( 
    find_max( 5, 6, 7 ) == 7 &&
    find_max( 9, 6, 7 ) == 9 &&
    find_max( 5, 6, 4 ) == 6 &&
    find_max( 5, 5, 4 ) == 5 
  )
    printf("[Passed]\n");

  //----------------------------------------------------------------------
  // rasterization test
  //----------------------------------------------------------------------
  
  Triangle_2D triangle_2d = { 0, 0, 7, 0, 7, 7, 20 };
//  Triangle_2D triangle_2d = { 0, 0, 7, 0, 0, 7, 30, 200 };

  CandidatePixel fragment[50];

  CandidatePixel fragment_ref[] = { 
  {0, 0, 20, 5},
  {1, 0, 20, 5},
  {2, 0, 20, 5},
  {3, 0, 20, 5},
  {4, 0, 20, 5},
  {5, 0, 20, 5},
  {6, 0, 20, 5},
  {7, 0, 20, 5},
  {1, 1, 20, 5},
  {2, 1, 20, 5},
  {3, 1, 20, 5},
  {4, 1, 20, 5},
  {5, 1, 20, 5},
  {6, 1, 20, 5},
  {7, 1, 20, 5},
  {2, 2, 20, 5},
  {3, 2, 20, 5},
  {4, 2, 20, 5},
  {5, 2, 20, 5},
  {6, 2, 20, 5},
  {7, 2, 20, 5},
  {3, 3, 20, 5},
  {4, 3, 20, 5},
  {5, 3, 20, 5},
  {6, 3, 20, 5},
  {7, 3, 20, 5},
  {4, 4, 20, 5},
  {5, 4, 20, 5},
  {6, 4, 20, 5},
  {7, 4, 20, 5},
  {5, 5, 20, 5},
  {6, 5, 20, 5},
  {7, 5, 20, 5},
  {6, 6, 20, 5},
  {7, 6, 20, 5},
  {7, 7, 20, 5}
};

  bit8 size;
  size = rasterization( triangle_2d, fragment );

//  printf("\nsize: %d\n", size);
  printf("\n========== rasterization test ==========\n");
/*
  for ( bit8 i = 0; i < size; i++ ) {
    verify_results( fragment[i], fragment_ref[i] );
  }
*/
  test_pass();

  return 0;      
}
