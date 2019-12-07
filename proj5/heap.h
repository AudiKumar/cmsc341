// CMSC 341 - Fall 2019 - Project 5
// heap.h
// Templated, vector-based heap implementation

// To work with Heap, the template class T must provide the following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) overloaded insertion operator
// To work with Heap *and* HashTable, it also needs:
//  (d) key function (string key())

#ifndef _HEAP_H
#define _HEAP_H

#include <iostream>
#include <vector>
#include <exception>
#include <utility>   // swap

using std::vector;
using std::endl;
using std::cout;
using std::swap;
using std::range_error;

// To work with Heap and HashTable, class T must provide the
// following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) key function (string key())
//  (d) overloaded insertion operator

class Grader;

template <class T>
class Heap {

  friend Grader;
  
 public:
  // Constructor
  Heap();

  // Inline functions: size, empty, used 
  unsigned size() const { return _heap.size() - 1 ; }
  bool empty() const { return _heap.size() <= 1 ; }
  bool used() const { return _used ; }

  // Main heap operations: insert, read, remove
  void insert(const T& object);
  T readTop() const;
  void removeTop();

  // Dump the entire heap
  void dump() const;

  // Root node always has index 1
  static const unsigned ROOT = 1;
  
 private:
  vector<T> _heap;   // Vector-based heap
  bool _used;        // Has the heap ever been used?  Needed for linear probing.
  
  // *********************************************
  // Private helper function declarations go here!
  // *********************************************
  void upHeap(int index);
  void downHeap(int index);
  bool isRoot(int index);
  bool isLeaf(unsigned int index);
  bool maintainsHeapProperty(int index); // will be used for downHeap
  
  //checks if the left priority is greater than the parent and the right isn't 
  bool checkLeft(int parentIndex);

  //checks if the right priority is greater than the parent and the left isn't
  bool checkRight(int parentIndex);
};

// ***************************************
// Templated function definitions go here!
// ***************************************

/*
constructor: 
  Initializes the empty heap, which is already done when 
  vector<T> _heap is writen so don't do anything? cause 
  you alway insert at 1
*/
template <class T>
Heap<T> :: Heap(){
  _heap = vector<T>(ROOT); 
}

/*
insert:
  A function that inserts an object into the heap:
*/
template <class T>
void Heap<T> :: insert(const T& object){
  _used = true;

  //find the newest node in the heap 
  _heap.push_back(object);

  //upHeap the recursive part
  if(isRoot(size() + 1) == false)
    upHeap(size()); 
}

/*
*/
template <class T>
T Heap<T> :: readTop() const{
  if (empty()){
    throw range_error("There is nothing in the heap");
  }
  return _heap.at(ROOT);
}

/*
*/
template <class T>
void Heap<T> :: removeTop(){
    if (empty()){
      throw range_error("There is nothing in the heap");
    }
    //if(size() > ROOT + 1){
      swap(  _heap.at(ROOT), _heap.at(size() )   );
      _heap.pop_back();
      cout << "before downHeap" << endl; 
      downHeap(ROOT); 
    //}
    //else{
      //_heap.pop_back();
    //}
    
    //remove the root
    //heapify
}

/*

*/
template <class T>
void Heap<T> :: dump() const{
  for (unsigned int x = 1; x < size() + 1; x++){  
    cout << _heap.at(x) << endl;
  }
  //cout << endl;
}

// *****************************************
// HELPERS                                 *
// *****************************************

template <class T>
void Heap<T> :: upHeap (int index){
  T parent = _heap.at(index/2);
  T child = _heap.at(index);
  
  //if the parents priority is greater than the child stop homie (base case)
  if (isRoot(index) || parent.priority() > child.priority() ){
    //cout << "in upHeap base case" << endl;
    return;
  }

  else{
    swap(_heap.at(index/2), _heap.at(index));
    upHeap(index/2);
  }

}

template <class T>
void Heap<T> :: downHeap(int index){
  cout << "inDownHeap" << endl;
  
  int leftIndex = 2 * index;
  int rightIndex = (2 * index) + 1;
  T left;
  T right;
  T curr = _heap.at(index);

  //you need cases for the following
  
  //when you are at a leaf [base case 1]
  if(leftIndex > size() )
    return;
  
  //if both childern exist
  if (leftIndex < size() && rightIndex < size() ){
    left = _heap.at(leftIndex);
    right = _heap.at(rightIndex);

  }

  //when both children exist
  //left only
  //right only



}

template <class T>
bool Heap<T> :: isRoot(int index){
  return index == ROOT;
}


#endif
