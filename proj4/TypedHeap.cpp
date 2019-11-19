#include "TypedHeap.h"


  

  // Provide a vector of strings.  For each string, determine whether
  // it represents an integer; if so, insert it into the integer skew
  // heap.  Otherwise, insert it into the string skew heap.
  void TypedHeap :: insertToHeaps(vector<string> vec){
    
    for(unsigned int x = 0; x < vec.size(); x++){
      bool isNumber = true;

      //removes whitespace before the word
      const auto whiteSpaceFront = vec.at(x).find_first_not_of(" ");
      const auto whiteSpaceTail = vec.at(x).find_last_not_of(" ");
      const auto strRange = (whiteSpaceTail - whiteSpaceFront) + 1;
      vec.at(x) = vec.at(x).substr(whiteSpaceFront, strRange);
      string curr = vec.at(x);
      for (int y = 0; y < curr.size(); y++){
        if ( isdigit(curr[y]) == false  ){
          isNumber = false;
          break;
        }
      }

      if (isNumber) intHeap.insert(curr);

      if (!isNumber) stringHeap.insert(curr);
    } 
  }

  // Merge the integer and string heaps; save in totalHeap.
  void TypedHeap :: combineHeaps(){
    totalHeap.skewHeapMerge(intHeap);
    totalHeap.skewHeapMerge(stringHeap);

  }
  // Print all three heaps (integer, string, total).
  void TypedHeap :: printHeaps() const{
    intHeap.dump();
    stringHeap.dump(); 
    totalHeap.dump();
  }

  // Change the priority function.
  void TypedHeap :: changePriority(pri_fn pri){}