#include "raq.h"

//custom includes to make the code work
#include <cmath>
#include <iostream>
#include <iomanip>
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
//precomputation = doing all of the possible ranges and storing in the raqObj
RAQ :: RAQ(std::vector<float> data){

  //loops through data and inserts it
  //b/c you are working with floats you will want to cast to float for your rows and cols
  for (unsigned int i = 0; i < data.size(); i++){
    vector<float> rowVector; 
    //rowVector.push_back(data.at(i));
    float sum  = data.at(i);
    //cout << "sum   " << sum;
    rowVector.push_back(sum);
    for(unsigned int j = i + 1; j < data.size(); j++){
      float diff = (float) (j - i) + 1.0;
      sum = sum + data.at(j);
      float ans = sum / diff;
      rowVector.push_back(ans);
    }
    raqObject.push_back(rowVector); 
  }
}

//Performs a Range Average Query from index i to index j. i and j must be in the range 
//0 ... n - 1 where n is the length of the data vector
float RAQ :: query(int i, int j) const{
  int diff = (j - i);
  return raqObject[i][diff];
} 

//Print the contents of the precomputation data structure. Must be formatted to be easily 
//read, at least for small data sizes  n ≤ 15.
void RAQ :: dump() const{
  for (unsigned int i = 0; i < raqObject.size(); i++){
    for(unsigned int j = 0; j < raqObject.at(i).size(); j++){
      cout << raqObject.at(i).at(j) << "  ";
    }
    cout << endl;
   }
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
