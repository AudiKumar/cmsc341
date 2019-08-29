# [Project 0: Memory Management and Using GL](https://userpages.umbc.edu/~cmarron/cs341.f19/projects/proj0.shtml)

## Objectives
- Reviews the following
    - memory management, and the rule of three
    - valgrind, and gl along with how to use them
    - creating the link submit for the other projects

## Assignment
- Description
    - complete the myarray class by adding the rule of three to it. You will test it and check for memory leaks along with that 
    - there are two tests, the code will run but you need to check to see if the output is correct

### what valgrind should say
```
   ==8613== 
   ==8613== HEAP SUMMARY:
   ==8613==     in use at exit: 0 bytes in 0 blocks
   ==8613==   total heap usage: 6 allocs, 6 frees, 74,048 bytes allocated
   ==8613== 
   ==8613== All heap blocks were freed -- no leaks are possible
   ==8613== 
   ==8613== For lists of detected and suppressed errors, rerun with: -s
   ==8613== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
