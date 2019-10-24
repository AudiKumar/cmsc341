GXX = g++
flags = -Wall -ansi -g -std=c++11

test4: test4.cpp treap.o
	$(GXX) $(flags) treap.o test4.cpp -o test4

test3: test0.cpp treap.o
	$(GXX) $(flags) treap.o test3.cpp -o test3

test2: test2.cpp treap.o
	$(GXX) $(flags) treap.o test2.cpp -o test2

test1: test1.cpp treap.o
	$(GXX) $(flags) treap.o test1.cpp -o test1

test0: test0.cpp treap.o
	$(GXX) $(flags) treap.o test0.cpp -o test0

treap.o: treap.h treap.cpp
	$(GXX) $(flags) -c treap.cpp