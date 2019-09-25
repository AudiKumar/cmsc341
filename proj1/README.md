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

    - we can assume that the encoded maze will probably be put into a vector and array 
    - you will want to try to go through the maze (backtracking is more of a laste option)
    - to prevent backtacking you will want to keep track of the current square and the previous
    - the stack will store our progress through the maze, for every new sqaure you will want to push it onto the tsakc
        - the stack will check the neighbhors of what is at the top and if possible visit them and will then visit a neighbhor and the process is reapted with the new square

        - if the stack has no unvisted neighbhors then you backtrack to a previous square and pop off the current 
        - IMPORTANT: if the stack is empty there is no solution

- What are the bookkeeping issues you will need to worry about?
    - when you are backtracking you have to you must mark the current square you are on as a "dead end"
    - YOU CAN DO THIS BY DELETING THE SQUARE FROM IT PREDECESSORS LIST OF NEIGHBHORS 


The provided .h file defines the constant VACANT to have the value of -1; you should use this constant to indicate deleted or empty neighbors as well as the predecessor to square 0.


## Assigmment

1. complete the maze class through your implementation of the stack, maze slover and other fns, these are your incomplete class files
    - maze.h: definition of the Maze and Maze :: SolverStack 
    - maze.cpp: incomplete implentation of the class itself

- the stack is the solver stack and it's nested within the maze class. The stack will also be implemented with a linked list instead of a list
- the solution the stack will be returning is a path from the start of the maze to the finish 
- you are also responsible for testing the program, no memory leaks or errors!

## Specifications
1. the STL vector and pair classes are needed in the project, but no other libraries or STL containers may be used.
2. A domain\_error exception should be thrown is an attempt is made to pop() or read() an empty SolverStack. A domain\_error exception should also be thrown if the solve() function is called on an empty Maze object. 
3. you may not make any changes to code provided in maze.h; however, you may add prototypes for private helper functions in the private: section of the Maze class.
4. the implemenation of the maze solver (solve() function in the Maze class) must use SolverStack and the stack-based algorithm outlined in the project description.
5. your code must compile and run with all provided test programs. Additional programs and data will be used for grading.

AND YOU MUST FOLLOW CODING STANDARDS and complie with just g++ and no compilation flags


## Functions You Will Be Implementing

### Functions for the Solver Stack Class
- ~SloveStack(); must delete all of the nodes in the linked list
- void push(sec\_dest\_t, src\_dest); the stack push, stack stores elements srcDestT which is a source destination pair
- src\_dest\_t pop(); must return srcDestT value @ the top of the stack and remove the item
- src\_dest\_t read() const; returns the top value but doesn't remove it 

### Functions for the Maze class 
- ~Maze(); desstructor
- std :: vector<int> solve() const; the maze solving fn, must implement the stack solver class if solution found int vector of the path, if no solution is found return an empty vector 