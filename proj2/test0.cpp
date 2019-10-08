// CMSC 341 - Fall 2019 - Project 2
// test0.cpp is a simple test program

#include <iostream>
#include <vector>
#include <cassert>
#include "raq.h"

using namespace std;

// Function to compute a single query directly from the data.
// Implementation follows main().

float avg(vector<float> data, int i, int j);

int main() {

  // This is the data from the project description
  /* 
  vector<float> data = {34, 16, 58, -24, 53,
			7, 97, 92, -12, 45,
			9, 0, -1, 20, 77};
  */
    vector<float> data = { 16, 58, -24, 53, 7, 97, 92, -12, 45, 9, 0, -1, 20, 77};

  // Print the test data
  
  cout << "Test data:\n";
  for (int i = 0; i < data.size(); i++) {
    cout << data[i] << "  ";
  }
  cout << "\n\n";

  // Create the RAQ object (does precomputation) and dump the data
  // structure

  cout << "Building RAQ\n";
  RAQ raq(data);
  raq.dump();

  // Create the BlockRAQ object (does precomputation and dump the data
  // structure

  cout << "\nBuilding BlockRAQ\n";
  BlockRAQ braq(data);
  braq.dump();

  // Simple correctness test.  Loop over all (i, j) pairs; compute
  // query using avg() function, RAQ query, and BlockRAQ query;
  // compare results; print if there is a discrepancy
  
  cout << "\nCorrectness test:\n";

  bool err = false;

  for (int j = 1; j < data.size(); j++) {
    for (int i = 0; i < j; i++) {

      float x = avg(data, i, j) ;
      float y = raq.query(i, j) ;
      //float z = raq.query(i, j) ;
      float z = braq.query(i, j) ;

      // Print message if direct computation disagrees with either RAQ
      // or BlockRAQ.  Note: their can be rounding errors, which are
      // not really errors.
      
      if ( (x != y ) || (x != z) ) {
	      cout << "(" << i << ", " << j << "): ";
	      cout << x << "  " << y << "  " << z << endl;
	      err = true;
      }
    }
  }

  if (!err) {
    cout << "No errors.\n";
  }
  /*
  cout << "\n\n################################################################################" << endl;
  cout << "this is your own testing for braq you will need to remove this later" << endl;
  cout << "\t*************************************" << endl;
  cout << "\tblock diff > 1" << endl;

  cout << "\t\ttest 1: the full blocks testing " << endl;
  cout << "\t\t(0, 8): " << "\n\t\t\tavg: " << avg(data, 0, 8); 
  cout << "\n\t\t\traq: " << raq.query(0, 8) << "\n\t\t\tbraq: " << braq.query(0, 8) << endl; 

  cout << "\t\ttest 2: i is at the begining of a block and j is just somewhere in the other block" << endl;
  cout << "\t\t(0, 6): " << "\n\t\t\tavg: " << avg(data, 0, 6); 
  cout << "\n\t\t\traq: " << raq.query(0, 6) << "\n\t\t\tbraq: " << braq.query(0, 6) << endl;

  cout << "\t\ttest 3: j is at the end of a block and i is not at the end" << endl;
  cout << "\t\t(4, 11): " << "\n\t\t\tavg: " << avg(data, 4, 11); 
  cout << "\n\t\t\traq: " << raq.query(4, 11) << "\n\t\t\tbraq: " << braq.query(4, 11) << endl;

  
  cout << "\tin the same block testing" << endl;
  cout << "\t\ttest 1: first the full block testing " << endl; 
  cout << "\t\t(0, 2): " << "\n\t\t\tavg: " << avg(data, 0, 2); 
  cout << "\n\t\t\traq: " << raq.query(0, 2) << "\n\t\t\tbraq: " << braq.query(0, 2) << endl;
  
  cout << "\t\ttest 2: now unto in block testing" << endl;
  cout << "\t\t(0, 1): " << "\n\t\t\tavg: " << avg(data, 0, 1); 
  cout << "\n\t\t\traq: " << raq.query(0, 1) << "\n\t\t\tbraq: " << braq.query(0, 1) << endl; 

  cout << "\tblock diff of 1 (5 tests)" << endl;
  cout << "\t\ttest 1: i is at the begining of a block and j is at the end of a block" << endl;
  cout << "\t\t(3, 8): " << "\n\t\t\tavg: " << avg(data, 3, 8); 
  cout << "\n\t\t\traq: " << raq.query(3, 8) << "\n\t\t\tbraq: " << braq.query(3, 8) << endl;
  
  cout << "\t\ttest 2: i is at the begining of a block and j is just somewhere in the other block" << endl;
  cout << "\t\t(3, 7): " << "\n\t\t\tavg: " << avg(data, 3, 7); 
  cout << "\n\t\t\traq: " << raq.query(3, 7) << "\n\t\t\tbraq: " << braq.query(3, 7) << endl;


  cout << "\t\ttest 3: i is just somewhere in the block and j is at the end of a block" << endl;
  cout << "\t\t(4, 8): " << "\n\t\t\tavg: " << avg(data, 4, 8); 
  cout << "\n\t\t\traq: " << raq.query(4, 8) << "\n\t\t\tbraq: " << braq.query(4, 8) << endl;

  cout << "\t\ttest 4: i and j blocks next to each other" << endl;
  cout << "\t\t(4, 7): " << "\n\t\t\tavg: " << avg(data, 4, 7); 
  cout << "\n\t\t\traq: " << raq.query(4, 7) << "\n\t\t\tbraq: " << braq.query(4, 7) << endl;

  
  cout << "\t\ttest 5: when j at the end" << endl;
  cout << "\t\t(9, 14): " << "\n\t\t\tavg: " << avg(data, 9, 14); 
  cout << "\n\t\t\traq: " << raq.query(9, 14) << "\n\t\t\tbraq: " << braq.query(9, 14) << endl;

  */


  return 0;
}

float avg(vector<float> data, int i, int j) {
  assert( 0 <= i && i <= j && j < data.size() );
  float tmp = 0.0;
  for (int k = i; k <= j; k++) {
    tmp += data[k];
  }
  return tmp / (j - i + 1);
}
