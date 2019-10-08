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
  //loop through the data and if the index is divisable by the size then you 
  //(size % i == 0) you treat that is the block and average the range (size / i 
  // = the ammount of variables in the block)
  blockSize = (int) sqrt((float) data.size());
  copyData = data; 
  cout << "blockSize " << blockSize << endl;
  float sum = 0;
  
  for (int i = 0; i < data.size(); i++){
    sum += data.at(i);
    if(i > 0  && (i + 1) % blockSize == 0){
      blockRaqObject.push_back(sum / blockSize);
      sum = 0; 
    }
  }//end of for loop

}

float BlockRAQ :: query(int i, int j) const{



  //loop either through iteration or boolean flag.
  //check where i and j is in terms of blocks (helper?)
  float query = 0;
  bool isDone = false;
  int iBlock = i / blockSize;
  int jBlock = j / blockSize;
  int blockDiff = jBlock - iBlock;
  int diff = (j - i) + 1;


  //cout << "i: " << i << " j: "  << j << " blockDiff: " << blockDiff << endl;

  //if blockDiff is == 0: i and j are in the same block so just iterate from i 
  //to j and average them through dividing with diff
  if (blockDiff == 0){
    //returns the block is its a full block
    if(j + 1 % blockSize == 0){
      query = blockRaqObject.at(jBlock);
    }
    //if it's not a fufll block iterate through
    else{
      for (int x = i; x <= j; x++){
        //cout << "in loop" << endl;
        query += copyData.at(x);
  
      }
      query /= diff;
    }
    return query;
  }

  //if block loc is 1 they are in different blocks so check if its a full block
  //when its a full block add the full block and then i and j when it isn't a 
  //full block then you will want just iterate through it
  else if(blockDiff == 1){
    
    //checks if i and j are just two full blocks
    if (i == (iBlock * blockSize) && (j + 1) % blockSize == 0){
      //cout << "\n\n test 1" << endl;
      query = query + (blockRaqObject.at(jBlock) * blockSize);
      query = query + (blockRaqObject.at(iBlock) * blockSize);
    }
    //checks if i starts at the begining of a block
    else if (i == (iBlock * blockSize)){
      //cout << "\n\n test 2" << endl;
      query = query + (blockRaqObject.at(iBlock) * blockSize);
      for (int x = (jBlock * blockSize); x <= j; x++){
        query += copyData.at(x);
      }
    }
    //if j is equal to the end of the block
    else if ((j + 1) % blockSize == 0){
      //cout << "\n\n test 3" << endl;
      query = query + (blockRaqObject.at(jBlock)* blockSize);
      //cout << "blockRAQObject at " << jBlock << " summed : " << query << endl;
      for (int x = i; x < ((iBlock*blockSize) + blockSize); x++){
      //for (int x = (iBlock * blockSize); x <= i; x++){ going up to i not from i
        //cout << "at index " << x << ": " << copyData.at(x) << endl;
        query += copyData.at(x);
      }
    }

    // if there isn't a full block of distance between it but they are in different blocks you just have to iterate through
    else{
      //cout << "test 4" << endl;
      for (int x = i; x <= j; x++){
        query += copyData.at(x);
      }
    }
    query /= diff;
    return query;
  }




  /*
  // if block loc is 0 (in the same block)
  if (blockLocDiff == 0){  //&& jBlockLoc != blockRaqObject.size() - 1){
    for (int x = i; x <= j; x++){
      query += copyData.at(x); 
    }

   //cout << "diff: " << diff << "\n\n\n"; 
   query = query/diff;
   return query;
  }

  else if(blockLocDiff == 1){
    //if the indexdiff is a mod of the block size then sum blocks
    if (diff % blockSize == 0){

    }
    return 

  }

  // if block locs are == 1 
  //if the block locs are greater than 1

  else if(blockLocDiff > 1){ //&& jBlockLoc != blockRaqObject.size() - 1){
    //cout << "jBlock: "<< jBlockLoc << "iBlock: " << iBlockLoc;
    //iterate over the blocks that are not iBlockLock and jBlockLoc and sum them
    for (int y = iBlockLoc + 1; y < jBlockLoc; y++){
      query += blockRaqObject.at(y) * blockSize;
    }

    for(int x = iBlockLoc * blockSize; x <= i; x++){
      query += copyData.at(x);
    }

    for(int z = jBlockLoc * blockSize; z <= j; z++){
      query += copyData.at(z); 
    }
    query = query / ((j - i) - 1);
  }
  */

  return query ;
}

void BlockRAQ :: dump () const{
  for (int x = 0; x < blockRaqObject.size(); x++){
    cout << blockRaqObject.at(x) << "  ";
  }
  cout << endl;
}

// helpers for BlockRAQ
