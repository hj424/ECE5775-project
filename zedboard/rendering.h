//========================================================================
// Rendering Header File
//========================================================================

#ifndef RENDERING_PROC_C
#define RENDERING_PROC_C

#include "projection.h"
#include "typedefs.h"
#include "coloringFB.h"
#include "hls_stream.h"

/*
  design under test: top function
*/
void dut(
    hls::stream<bit32> &strm_in,
    hls::stream<bit32> &strm_out
);

/*
  rendering function
*/
void rendering( bit16 counter, Triangle_3D triangle_3ds, bit2 angle ); 

#endif /* RENDERING_H */

