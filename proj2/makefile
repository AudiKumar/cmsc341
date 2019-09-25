GXX = g++
flags = -Wall -ansi -g -std=c++11




test0: test0.cpp raq.o
	$(GXX) $(flags) raq.o test0.cpp -o test0

raq.o: raq.h raq.cpp
	$(GXX) $(flags) -c raq.cpp
