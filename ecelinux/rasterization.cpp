//========================================================================
// Rasterization
//========================================================================

#include "rasterization.h"

/*
  Determine whether three vertices of a trianlge 
  (x0,y0) (x1,y1) (x2,y2) are in clockwise order by Pineda algorithm
  if so, return a number > 0
  else if three points are in line, return a number == 0
  else in counterclockwise order, return a number < 0
*/
int check_clockwise( Triangle_2D triangle_2d ){

  int cw;
  
  cw = (triangle_2d.x2 - triangle_2d.x0) * (triangle_2d.y1 - triangle_2d.y0) 
       - (triangle_2d.y2 - triangle_2d.y0) * (triangle_2d.x1 - triangle_2d.x0); 

 // std::cout << cw << std::endl;
  return cw;

}

/*
  swap (x0, y0) (x1, y1) of a Triangle_2D
*/
void clockwise_vertices( Triangle_2D *triangle_2d ){

  bit8 tmp_x, tmp_y;

  tmp_x = triangle_2d->x0;
  tmp_y = triangle_2d->y0;

  triangle_2d->x0 = triangle_2d->x1;
  triangle_2d->y0 = triangle_2d->y1;

  triangle_2d->x1 = tmp_x;
  triangle_2d->y1 = tmp_y;

}


/*
  Given a pixel, determine whether it is inside the triangle 
  by Pineda algorithm
  if so, return true
  else, return false
*/
bit1 pixel_in_triangle( bit8 x, bit8 y, Triangle_2D triangle_2d ){

  int pi0, pi1, pi2;

  pi0 = (x - triangle_2d.x0) * (triangle_2d.y1 - triangle_2d.y0) - (y - triangle_2d.y0) * (triangle_2d.x1 - triangle_2d.x0); 
  pi1 = (x - triangle_2d.x1) * (triangle_2d.y2 - triangle_2d.y1) - (y - triangle_2d.y1) * (triangle_2d.x2 - triangle_2d.x1); 
  pi2 = (x - triangle_2d.x2) * (triangle_2d.y0 - triangle_2d.y2) - (y - triangle_2d.y2) * (triangle_2d.x0 - triangle_2d.x2); 

  return (pi0 >= 0 && pi1 >= 0 && pi2 >= 0);
}

/*
  find the min from 3 integers
*/
bit8 find_min( bit8 in0, bit8 in1, bit8 in2 ){
  if (in0 < in1){
    if (in0 < in2){
      return in0;
    }
    else {
      return in2;
    }
  }
  else {
    if (in1 < in2) {
      return in1;
    }
    else {
      return in2;
    }
  }
}

/*
  find the max from 3 integers
*/
bit8 find_max( bit8 in0, bit8 in1, bit8 in2 ){
  if (in0 > in1){
    if (in0 > in2){
      return in0;
    }
    else {
      return in2;
    }
  }
  else {
    if (in1 > in2) {
      return in1;
    }
    else {
      return in2;
    }
  }
}

/*
  Raster a 2D triangle
*/

bit16 rasterization ( Triangle_2D triangle_2d, CandidatePixel fragment[] )
{
  
  // clockwise the vertices of input 2d triangle 
  if ( check_clockwise( triangle_2d ) == 0 )
    return 0;
  if ( check_clockwise( triangle_2d ) < 0 )
    clockwise_vertices( &triangle_2d );
  // find the bounds of the rectangle
  bit8 min_x, min_y, max_x, max_y, color;
  min_x = find_min( triangle_2d.x0, triangle_2d.x1, triangle_2d.x2 );
  max_x = find_max( triangle_2d.x0, triangle_2d.x1, triangle_2d.x2 );
  min_y = find_min( triangle_2d.y0, triangle_2d.y1, triangle_2d.y2 );
  max_y = find_max( triangle_2d.y0, triangle_2d.y1, triangle_2d.y2 );
  color = 100;
  // i: size_pixels
  bit16 i = 0;
RL1:
  for ( int y = min_y; y < max_y; y++ ) {
RL2:
    for ( int x = min_x; x < max_x; x++ ) {
      if( pixel_in_triangle( x, y, triangle_2d ) )
      { 
        fragment[i].x = x;
        fragment[i].y = y;
        fragment[i].z = triangle_2d.z;
        fragment[i].color = color;
        i++;
      }  

    }
  }
  return i; 
}


