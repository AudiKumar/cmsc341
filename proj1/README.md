# Project 1: [Maze Solving using Arrays & Stacks](https://userpages.umbc.edu/~cmarron/cs341.f19/projects/proj1.shtml)

## Objectives
To review basic linked data structurs by implementing a stack using a linked list. This stack will be used in a maze solving program.


## Introduction

We are going to be writing a program to solve a maze


- How can a maze be encoded?
    -a cell-neighbor representation
    -if there are n squares in the maze, the labels go from 0 to n - 1 
    -start of the maze is 0 and the end is at cell n - 1

    -Consider the following Example

    ```
   +--+--+--+--+--+
   |0  5  10|15 20|
   +  +--+--+  +  +
   |1  6  11 16|21|
   +  +--+--+--+  +
   |2  7 |12 17 22|
   +--+--+  +--+  +
   |3  8 |13|18 23|
   +  +--+  +  +--+
   |4  9  14|19 24|
   +--+--+--+--+--+
    
   to encode this maze you will want to the have reachable neighbors be associated
   with the square itself 

   EX: 
        In Sqaure 0 the reachable squares are 5 and 0 therefore square 0 would be encoded as
        (0, 1, 5) 
        
        encoding the maze in the date file might begin as follows
            
            0, 1, 5
            1, 0, 2, 6
            2, 1, 7
            3, 8, 4
            4, 3, 9
            5, 0, 10 
    ```
 
