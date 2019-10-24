# Project 3: Treaps


## Objectives
1. Practice constructing and using binary trees
2. practice basic balancing

## Introduction
- What is a treap?
    - it's a combo of a bst and a heap
    - What elements of a heap do we need to know about?
        1. each node (along with the pointers) will also hold the data itself and a prioity value
        2. the "heap" part of this tree will be a max heap 
            - for any node w in the tree the priority of w must be greaters than the prioities of w's two children 
- The following is an exmaple of a treap
    - ![](/images/proj3ExampleTreap.png)

- What does a treap require?
    1. This is what the tree node holds
        - data
        - prority value 
        - teap left child
        - teap right child
        - *THE PRIOTIIY VALS ARE UNIQUE*
    2. the trep will have a max heap propertiy 
        - for any node w in the tree the proirity of w must be greater than the proities of its two childern 

    - both the bst and max heap propetiy will make this a treap

    - How are the inserstions and deletions effected by being a treap?
        - both of these functions of the treap must check to see if the min max property holds. If the property is broken then you must recursivly fix it
        - this fixing can be done through single rotations
- What is the algorithim of insert and delete
    - *let (v,p) be a value and priority value, and p is unique*
    - insertion
        - first perfrom a normal bst insertion, with all the stuff you would do for that. Afterwhich you will need to check to see if p > the parent of where it was inserted, if this is the case single rotate up the tree until max heap property is solved

    - deletetion
        - normal bst deletetion with the checks described in the insert

    - *when you recurse back up you will need to update the heights while going up (which will probably be confusing :( )*

- Things to avoid doing in the project
    - avoid both the copy constructor and the asignment operator (b/c the the recursion will fuck all the shit up)
        