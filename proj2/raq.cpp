#include "raq.h"

//custom includes to make the code work
#include <cmath>
#include <iostream>
#include <iomanip>
#include <stdexcept>

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
  copyData = data;
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
  if (i < 0 || i > copyData.size()){
    throw std::domain_error("RAQ: i is not in the range of the RAQ");
  }

  if (j < 0 || j > copyData.size()){
    throw std::domain_error("RAQ: i is not in the range of the RAQ");
  }
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

  if (i < 0 || i > copyData.size()){
    throw std::domain_error("RAQ: i is not in the range of the blockRAQ");
  }

  if (j < 0 || j > copyData.size()){
    throw std::domain_error("RAQ: i is not in the range of the blockRAQ");
  }

  //loop either through iteration or boolean flag.
  //check where i and j is in terms of blocks (helper?)
  float query = 0;
  bool isDone = false;
  int iBlock = i / blockSize;
  int jBlock = j / blockSize;
  int blockDiff = jBlock - iBlock;
  int diff = (j - i) + 1;


  //cout << "i: " << i << " j: "  << j << " SIZE: " << copyData.size() << endl;

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
      //query /= diff;
    }
    //return query;
  }

  //if block loc is 1 they are in different blocks so check if its a full block
  //when its a full block add the full block and then i and j when it isn't a 
  //full block then you will want just iterate through it
  else if(blockDiff == 1){
    
    //checks if i and j are just two full blocks
    if (i == (iBlock * blockSize) && (j + 1) % blockSize == 0 && (j + 1) != copyData.size()){
      //cout << "\n\n test 1" << endl;
      query = query + (blockRaqObject.at(jBlock) * blockSize);
      query = query + (blockRaqObject.at(iBlock) * blockSize);
    }
    //checks if i starts at the begining of a block
    else if (i == (iBlock * blockSize) && (j + 1)!= copyData.size()){ 
      //cout << "\n\n test 2" << endl;
      query = query + (blockRaqObject.at(iBlock) * blockSize);
      for (int x = (jBlock * blockSize); x <= j; x++){
        query += copyData.at(x);
      }
    }
    //if j is equal to the end of the block
    else if ((j + 1) % blockSize == 0 && (j + 1) != copyData.size()){
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
      // if the j block is normal then do all of the stuff that you did before
      if ((j + 1) % blockSize == 0){
        //cout << "test 5" << endl; 
        if (i == (iBlock * blockSize) && (j + 1) % blockSize == 0){
          //cout << "asdfasdfasd" << endl;
           query = query + (blockRaqObject.at(jBlock) * blockSize);
           query = query + (blockRaqObject.at(iBlock) * blockSize);
        }

        else if (i == (iBlock * blockSize)){
          query = query + (blockRaqObject.at(iBlock) * blockSize);
          for (int x = (jBlock * blockSize); x <= j; x++){
          query += copyData.at(x);
          }
        }

        else if ((j + 1) % blockSize == 0){
          query = query + (blockRaqObject.at(jBlock)* blockSize);
           for (int x = i; x < ((iBlock*blockSize) + blockSize); x++){
             query += copyData.at(x);
           }
        }

        else{
          for (int x = i; x <= j; x++){
            query += copyData.at(x);
          }
        }
      }// end or normal j block check

      //else just sum it up
      else{
          //cout << "asdfasdfasd" << endl;
          for (int x = i; x <= j; x++){
            query += copyData.at(x);
          }
      }
    }
    //query /= diff;
    //return query;
  }
  // if there is more than one block in between 
  else if (blockDiff > 1){
    if (i == (iBlock * blockSize) && (j + 1) % blockSize == 0 && (j + 1) != copyData.size()){
      for (int y = iBlock; y <= jBlock; y++){
        query += blockRaqObject.at(y) * blockSize;
      }
    }

    //checks if i starts at the begining of a block
    else if (i == (iBlock * blockSize) && (j + 1)!= copyData.size()){ 
      for (int y = iBlock; y < jBlock; y++){
        query += blockRaqObject.at(y) * blockSize;
      }

      //iterate through begining of j block to j
      for(int x = jBlock * blockSize; x <= j; x++){
        query += copyData.at(x);
      }
    }

    //checks if j is equal to the end of the block
    else if ((j + 1) % blockSize == 0 && (j + 1) != copyData.size()){
      //cout <<"asdfasdf" << endl;
      for (int y = iBlock + 1; y <= jBlock; y++){
        query += blockRaqObject.at(y) * blockSize;
      }

      //iterate through i to end of block i
      for(int x = i; x < ((iBlock*blockSize) + blockSize); x++){
        query += copyData.at(x);
      }
    }

    //if neither i or j is at the begining and end respectivly then you
    //you need to iterate everything in between i and j and then iter i 
    //and j
    else if (i != (iBlock * blockSize) && (j + 1) % blockSize != 0 && (j + 1) != copyData.size()){
      for (int y = iBlock + 1; y < jBlock; y++){
        query += blockRaqObject.at(y) * blockSize;
      }

      for(int x = i; x < ((iBlock*blockSize) + blockSize); x++){
        query += copyData.at(x);
      }

      //iterate through begining of j block to j
      for(int x = jBlock * blockSize; x <= j; x++){
        query += copyData.at(x);
      }
    }


    //if j is equal to the size the you will need to do what you did before 
    //do the checks for i first and add it to the query accordingly then 
    //check to see if j is normal if it is then add it via the block
    //otherwise iterate until you get to through the j block and add it
    //query  
    else{
      //if if the j block is normal and not werid proceed as normal
      if ((j + 1) % blockSize == 0){
        
        // if i is at the begining of a block
        if(i == (iBlock * blockSize)){
          for (int y = iBlock; y <= jBlock; y++){
            query += blockRaqObject.at(y) * blockSize;
          }
        }

        //else mean thats i is not as the begining of a block but j is so
        //get the blocks from i + 1 to j and then sum up the contents of i
        else{
          for (int y = iBlock + 1; y <= jBlock; y++){
            query += blockRaqObject.at(y) * blockSize;
          }

          //iterate through begining of i block to i
          for(int x = i; x < ((iBlock*blockSize) + blockSize); x++){
            query += copyData.at(x);
          }

        }

      }

      //this is when the block is werid
      else{
          //iterate through begining of i block to i
          for(int x = i; x <= j ; x++){
            query += copyData.at(x);
          }
      }

    }

  }

  query /= diff;
  return query ;
}

void BlockRAQ :: dump () const{
  for (int x = 0; x < blockRaqObject.size(); x++){
    cout << blockRaqObject.at(x) << "  ";
  }
  cout << endl;
}

// helpers for BlockRAQ
