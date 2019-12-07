// CMSC 341 - Fall 2019 - Project 5
// hash.h

// Templated, hash table implementation.  Each buckets is a heap.  A
// bucket contains objects with the same key values stored as a
// max-heap based on priority.  Collisions are resolved by linear
// probing.

// To work with Heap and HashTable, the template class T must provide
// the following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) key function (string key())
//  (d) overloaded insertion operator

#ifndef _HASH_H
#define _HASH_H

#include <string>
#include "heap.h"

using std::string;

// Hash function typedef.  The hash function must return an 'unsigned
// int' value.  Reduction mod N is the responsiblity of the caller,
// not the hash function.
typedef unsigned (*hash_fn)(string);

class Grader;

template <class T>
class HashTable {

  friend Grader;
  
 public:
  // Constructor.  Requires table size and hash function.
  HashTable(unsigned size, hash_fn hash);

  // Destructor, copy, and assignment
  ~HashTable();
  HashTable(const HashTable<T>& ht);
  const HashTable<T>& operator=(const HashTable<T>& ht);

  // In-line functions
  
  // Table size; set by constructor
  unsigned tableSize() const { return _N; }
  // Number of entries in the table
  unsigned numEntries() const { return _n; }
  // Load factor
  float lambda() const { return ((float) _n) / _N; }

  // Main hash table functions
  
  // insert returns 'true' if successful; 'false' otherwise
  bool insert(const T& object);
  // getNext retrieves **and removes** the highest priority order of
  // type indicated by key.  It returns 'true' if successful; 'false'
  // otherwise.
  bool getNext(string key, T& obj);

  // Dump the entire hash table
  void dump() const;
  
 private:
  unsigned _N;       // hash table size
  unsigned _n;       // current number of entries
  hash_fn _hash;     // hash function
  Heap<T> *_table;   // array of heaps

  // ***********************************************
  // Private helper function declarations go here! *
  // ***********************************************
  //int modCompresion(const T& obj); // not sure what will be needed for this tbh in terms of parameters
};


// *****************************************
// Templated function definitions go here! *
// *****************************************
template <class T>
HashTable<T> :: HashTable(unsigned size, hash_fn hash){
  _N = size;
  _hash = hash;
  _table = new Heap<T>[_N];
  cout << "sadfasdfads" << endl;
}

template <class T>
HashTable<T> ::  ~HashTable(){
  delete [] _table;
}

template <class T>
HashTable<T> :: HashTable(const HashTable<T>& ht){
  
  //copies all of the static memebers
  _N = ht._N;
  _n = ht._n;
  _hash = ht._hash;
  
  //deletes old table if needed
  if (_table != nullptr)
    delete [] _table;
  
  //creates new table based off new size
  _table = new Heap<T>[_N];

  //deep copies entries of ht
  for (unsigned int x = 0; x < _N; x++){
    _table[x] = ht._table[x];
  }
    
}

template <class T>
const HashTable<T>& HashTable<T> :: operator=(const HashTable<T>& ht){
  
  //checks to see if you are trying to operator= the same thing
  if(this == &ht)
    return *this;
  
  //deletes old table if needed
  if (_table != nullptr)
    delete [] _table;
  
  //copies all of the static memebers  
  _N = ht._N;
  _n = ht._n;
  _hash = ht._hash;

  //creates new table based off new size
  _table = new Heap<T>[_N];
  
  //deep copies contents of ht
  for (unsigned int x = 0; x < _N; x++){
    _table[x] = ht._table[x];
  }
  return *this;
}

template <class T>
bool HashTable<T> :: insert(const T& object){
  unsigned hashVal = _hash(object.key());
  unsigned int ogIndex = hashVal % tableSize();
  

  if ( _table[ogIndex].empty() || _table[ogIndex].readTop().key() == object.key()  ){
    _table[ogIndex].insert(object);
  }

  else{
    unsigned int copyOG = ( (unsigned) ogIndex )  + 1;
    bool keepProbing = true;

    while(keepProbing == true){
      if (copyOG  >= tableSize()){
        copyOG = copyOG % tableSize();
      }
      if(copyOG == ogIndex){
        return false;
      }
      if( _table[copyOG].empty()  ){
        _table[copyOG].insert(object);
        keepProbing = false;
      }
    }
    
  }
  return true;
}

template <class T>
bool HashTable<T> :: getNext(string key, T& obj){

  //mod compresion
  unsigned hashVal = _hash(key);
  unsigned int ogIndex = hashVal % tableSize();

  if (  _table[ogIndex].readTop().key() == key  ){
    //cout << "before removeTop() call" << endl;
    _table[ogIndex].removeTop();
    return true; 
  }

  if (    _table[ogIndex].used()    ){
    unsigned int copyOG = ogIndex   + 1;
    bool keepProbing = true;

    while(keepProbing){
      if (copyOG  >= tableSize())
        copyOG = copyOG % tableSize();

      if(copyOG == ogIndex)
        return false;

      if(_table[copyOG].readTop().key() == key){
        keepProbing = false;
        _table[copyOG].removeTop();
        return true;
      }
    }
  }
  
  return false;
}

template <class T>
void HashTable<T> :: dump() const{

  for(unsigned int x = 0; x < tableSize(); x++){
    cout << "[" << x << "]:" << endl;
    _table[x].dump();
  }

}

#endif
