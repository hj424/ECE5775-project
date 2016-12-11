#=============================================================================
# run.tcl 
#=============================================================================
# @brief: A Tcl script for synthesizing the 3D image rendering design.
#

# Project name
set hls_prj rendering.prj

# Open/reset the project
open_project ${hls_prj} -reset

# Top function of the design is "dut"
set_top dut

# Add design and testbench files
add_files rendering.cpp 
add_files projection.cpp 
add_files rasterization.cpp 
add_files zculling.cpp 
add_files coloringFB.cpp 
add_files -tb rendering_test.cpp 
add_files -tb input.dat

# solution name
open_solution "solution1"

# Use Zynq device
set_part {xc7z020clg484-1}

# Target clock period is 10ns
create_clock -period 10

# array partition - worse overall performance than loop pipelining
#set_directive_array_partition -dim 2 -type cyclic -factor 2 rendering z_buffer
#set_directive_array_partition -dim 1 -type cyclic -factor 16 rendering fragment
#set_directive_array_partition -dim 1 -type cyclic -factor 2 rendering pixels

# loop unrolling - worse overall performance than loop pipelining
#set_directive_unroll -factor 4 rasterization/RL2
#set_directive_unroll -factor 2 zculling/ZL1
#set_directive_unroll -factor 2 coloringFB/CL1

# dataflow
#set_directive_dataflow dut
set_directive_dataflow rendering
#set_directive_dataflow rasterization/RL2

# pipeline
#set_directive_pipeline dut/TL2
set_directive_pipeline rasterization/RL2
#set_directive_pipeline rasterization/RL1
set_directive_pipeline zculling/ZL1
set_directive_pipeline coloringFB/CL1

# loop trip count
set_directive_loop_tripcount -min 1 -max 29 -avg 15 rasterization/RL2
set_directive_loop_tripcount -min 1 -max 25 -avg 13 rasterization/RL1

set_directive_loop_tripcount -min 0 -max 446 -avg 223 zculling/ZL1
set_directive_loop_tripcount -min 0 -max 446 -avg 223 coloringFB/CL1

# Simulate the C++ design
csim_design
# Synthesize the design
csynth_design
# Co-simulate the design
cosim_design

#---------------------------------------------
# Collect & dump out results from HLS reports
#---------------------------------------------
set filename "rendering_result.csv"
set argv [list $filename $hls_prj]
set argc 2
source "./script/collect_result.tcl"

