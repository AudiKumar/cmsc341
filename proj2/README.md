# Project 2:  Range Average Query

## Objective of this Project
to implement two different solutions for the Range Average Query Problem, each of these solutions will have different asymptotic running times

### Introduction 
The Range Average Query problem is as follows 
- ![](/images/proj2RangeAverageQueryProblem.png)

WHhat would the simple solution be?
- The Simple Solution in Psuedocode
    - ![](/images/proj2SimpleSolutionProof.png)
- below shows as to why the simple solution is n^3
    -![](/images/proj2SimpleSolution.png)

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


