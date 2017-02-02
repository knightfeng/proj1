# Project 1 Makefile
# ------------------
# Usage:
# - to build LQueue_driver: make LQueue_driver
# - to build LQueue_simulation: make LQueue_simulation
# - to clean up: make clean

# edit here if you need to change the C++ compiler flags
CXXFLAGS ?= -Wall -g --std=c++11
# this reminds make to link the C++ standard library
LDLIBS ?= -lstdc++

# by default, compile only the test driver
all: LQueue_driver

# compile the LQueue library
LQueue.o: LQueue.C LQueue.h

# compile the test driver
LQueue_driver: LQueue_driver.o LQueue.o

# compile the LQueue_simulation (LQueue_simulation.C has to exist)
LQueue_simulation: LQueue_simulation.o LQueue.o

clean:
	rm -f *.o LQueue_driver LQueue_simulation