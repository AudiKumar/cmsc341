#include "SkewHeap.h"

// Constructor.  Must specify priority function.
  SkewHeap :: SkewHeap(pri_fn pri){

  }
  // Destructor, copy constructor, assignment operator
  SkewHeap :: ~SkewHeap(){

  }

  SkewHeap :: SkewHeap(const SkewHeap& rhs){

  }
  
  const  SkewHeap& SkewHeap :: operator=(const SkewHeap& rhs){

  }

  // Priority function get and set
  pri_fn SkewHeap :: getPriFn() const{

  }

  void SkewHeap :: setPriFn (pri_fn pri){

  }

  // Return true if the skew heap is empty
  bool SkewHeap :: empty() const{
      bool result = true;

      return result;
  }

  // Overloaded insertion operators.  One for string data, one for
  // integer data.
  void SkewHeap :: insert(string data){

  }
  void SkewHeap :: insert(int data){

  }

  // Access highest priority element in the skew heap.
  Node* SkewHeap :: front() const{
      Node* temp;
      return temp;
  }

  // Remove the highest priority element from the skew heap.
  void SkewHeap :: removeTop(){}

  // Merge two heaps.  Merged heap in *this; sh is empty afterwards.
  void SkewHeap :: skewHeapMerge(SkewHeap& sh){}

  // Print inorder traversal.
  void SkewHeap :: inorder() const{}
  
  // Dump the contents of the heap in decreasing priority order.
  void SkewHeap :: dump() const{}