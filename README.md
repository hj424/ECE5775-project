# ECE5775-project
3D image rendering: software-hardware co-design

#=========================================================================================
# ecelinux
#=========================================================================================
all source file for 3D rendering system, including:
1. projection stage + projection_test bench + projection header file
2. rasterization stage + rasterization_test bench + rasterization header file
3. z-culling stage + z-culling_test bench + z-culling header file
4. frambuffer(coloringFB) stage + frambuffer(coloringFB)_test bench + frambuffer(coloringFB) header file
5. rendering (top fucntion) + rendering_test bench + rendering header file

6. input.dat - 3D triangle mesh
7. typedefs.h - defination of fixed point variable by ap_int
8. timer.h - timer for calculating rendering time
9. Makefile - commands of compiling and executing source files

10. run.tcl - tcl script for synthesizing the 3D image rendering system by vivado_hls
11. script/collect-result.tcl - tcl script for collecting results from csim and synthesis

12. run_bitstream.sh - file for generating bit file according to teh Verilog file generated during synthesis

commands:
1. simulation & synthesis
   # vivado_hls -f run.tcl
2. generate bit file
   # source run_bitstream.sh
   
#=========================================================================================
# zedboard
#=========================================================================================
files for running on fpga.
1. host.cpp - host file in batch mode
2. Makefile - make file for running program in fpga.

Tips:
1. When run the program on zedboard, put all the code in the same file folder EXPECT the Makefile in ecelinux
