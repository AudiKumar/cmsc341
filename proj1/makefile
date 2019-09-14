GXX = g++
flags = -Wall -ansi -g -std=c++11


test0: maze.o test00.cpp
	$(GXX) $(flags) maze.o test00.cpp -o test0

maze.o: maze.cpp maze.h 
	$(GXX) $(flags) -c maze.cpp 
