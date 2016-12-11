#============================================================================
# Makefile
#===========================================================================
# @brief: A makefile the compiles and synthesizes the 3D rendering program
#
# @desc: 1. "make" runs csim by default
#        2. "make s" compliles & executes the top function - dut(rendering)
#        3. "make s1“ compiles & executes the first stage - projection
#        4. "make s2" compiles & executes the second stage - rasterization
#        5. "make s3" compiles & executes the third stage - zculling
#        6. "make clean" cleans up the direstory
#

#Extract Vivado HLS include path
VHLS_PATH := $(dir $(shell which vivado_hls))/..
VHLS_INC ?= ${VHLS_PATH}/include

all: s

s:      rendering.h rendering.cpp rendering_test.cpp projection.cpp rasterization.cpp zculling.cpp coloringFB.cpp
	@echo "Compiling & Executing rendering..."
	g++ -g -I${VHLS_INC} rendering.cpp rendering_test.cpp projection.cpp rasterization.cpp zculling.cpp coloringFB.cpp -o rendering
	./rendering

s1:     projection.h projection.cpp projection_test.cpp
	@echo "Compiling & Executing projection stage..."
	g++ -g -I${VHLS_INC} projection.cpp projection_test.cpp -o projection
	./projection

s2:     rasterization.h rasterization.cpp rasterization_test.cpp
	@echo "Compiling & Executing rasterization stage..."
	g++ -g -I${VHLS_INC} rasterization.cpp rasterization_test.cpp -o rasterization
	./rasterization

s3:     zculling.h zculling.cpp zculling_test.cpp
	@echo "Compiling & Executing zculling state..."
	g++ -g -I${VHLS_INC} zculling.cpp zculling_test.cpp -o zculling
	./zculling

#Clean up the directory
clean:
	@echo "Clean up output files"
	rm -rf result *.prj *.log out.dat projection rasterization zculling rendering

