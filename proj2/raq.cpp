#include "raq.h"
using namespace std;
/*
 * Name: Aditya Krishna Yerraguntla Kumar
 * File: raq.cpp 
 * Description:  
 *              implement the Dynamic Programming and Block Decomposition 
 *              methods for Range Average Queries. You have a lot of 
 *              freedom in how to implement your solution — you get to decide 
 *              what the private class variables should be — but you must 
 *              implement the specified functions, and you must use Dynamic 
 *              Programming and Block Decomposition.
 *
 *              YOU'RE MAKEFILE HAS -Wall which will give a warning about test0
 *              JUST IGNORE IT or remove the issue that is causing the error 
 */


// ######################################################
// RAQ 
// #####################################################


//Creates a RAQ object from a data vector. Performs precomputation for the Dynamic Programming solution.
RAQ :: RAQ(std::vector<float> data){

}

//Performs a Range Average Query from index i to index j. i and j must be in the range 
//0 ... n - 1 where n is the length of the data vector
float RAQ :: query(int i, int j) const{
  float ans = 0;
  return ans;
} 


void RAQ :: dump() const{

}

//helpers for RAQ



// ######################################################
// BlockRAQ
// #####################################################
BlockRAQ :: BlockRAQ(std::vector<float> data){

}

float BlockRAQ :: query(int i, int j) const{
  float ans = 0;
  return ans;
}

void BlockRAQ :: dump () const{

}

// helpers for BlockRAQ
