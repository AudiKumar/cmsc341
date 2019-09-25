# Project 2:  Range Average Query

## Objective of this Project
to implement two different solutions for the Range Average Query Problem, each of these solutions will have different asymptotic running times

### Introduction 
The Range Average Query problem is as follows 
- ![](/images/proj2RangeAverageQueryProblem.png)

WHhat would the simple solution be?
- The Simple Solution in Psuedocode
    - ![](/images/proj2SimpleSolutionPesudoCode.png)
- below shows as to why the simple solution is n^3
    - ![](/images/proj2SimpleSolutionProof.png)

O(n^3) sucks is there a way to make it faster?
-yes there is there are two solutions, one would be through dynamic programing and the other would be through block decompisition 

1. Dynamic Programing
    - what is dynamic programing? 
        - it is a way to make code go faster
        - this is done though precomputation of older value used
    - how would you use dynamic programing in the project?
        - lets say that you already got avg(i, j) if you want to get avg(i, j + 1) all you have to do is a calcuation which is O(1) and below
        - ![](/images/proj2Dynamic.png)
        - the reason this works is because all you are doing is geting the previous value and performing math on it :) 
    - what are the run times looking like for this?
        - in terms of doing the computation it is O(n^2)
        - retrival would be O(1) though
2. Block Decomposition
    - what is block decomposition?
        - it's easier to go over an example see below
        - ![](/images/proj2Block.png)
        - what does this table mean?
            - first row  : indexs of the array
            - second row : the values of the array
            - third row  : the sum avg of the block of three values
    - what should we do if the queries do not align with the block sturctures
        -  you get the avg of the full blocks, and then you add the rest of the non blocks to the end and then divide by the number of blocks + the edges 
    - how efficient is this method?
        - precomputing can be done in O(n)
        - retieval can be done in O(sqrt(n))


## Assignment
- Your assignment is to implement the Dynamic Programming and Block Decomposition methods for Range Average Queries. You have a lot of freedom in how to implement your solution — you get to decide what the private class variables should be — but you must implement the specified functions, and you must use Dynamic Programming and Block Decomposition 

- You are provided the following skeletons 
    1. raq.h — skeleton .h file for the RAQ and BlockRAQ classes.
    2. test0.cpp — a basic test program.
    3. test0.txt — sample output from test0.cpp using my implementation of RAQ and BlockRAQ. Your ouput may not be identical, depending on how you set-up the data structures.



