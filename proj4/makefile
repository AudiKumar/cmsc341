cmds = g++ -Wall -ansi -g -std=c++11

test1: test1.cpp TypedHeap.o
	$(cmds) TypedHeap.o test1.cpp -o test1

test0: test0.cpp SkewHeap.o
	$(cmds) SkewHeap.o test0.cpp -o test0

TypedHeap.o: SkewHeap.o TypedHeap.cpp
	$(cmds) -c TypedHeap.cpp

SkewHeap.o: SkewHeap.h SkewHeap.cpp
	$(cmds) -c SkewHeap.cpp