// CMSC 341 - Fall 2019 - Project 3
// File: treap.cpp

using namespace std ;

#include "treap.h"

Treap::Treap() {
  _nptr = nullptr ;
}

Treap::Treap(const Treap& other) {
  //
  // Implement copy constructor
  //
}

Treap::~Treap() {
  // this implementations of the destructor assumes that the remove works
  // bassically will remove the root and rebalance until there's nothing 
  // there anymore
  while(_nptr != nullptr){
    remove(_nptr->_data);
  }

}

const Treap& Treap::operator=(const Treap& rhs) {
  //
  // Implement assignment operator
  //
}

// Return -1 if the treap is empty; otherwise, return value in _height.
int Treap::height() const {
  return _nptr ? _nptr->_height : -1 ;
}

// Return the priority of the root node of a Treap.
// Note: numeric_limits<priority_t>::min() returns the minimum value
// of the priority type.  We will only use int priorities, so this is
// the minimum integer value.
priority_t Treap::priority() const {
  return _nptr ? _nptr->_pri : numeric_limits<priority_t>::min() ;
}

//data_t is a typedef of string (a letter) so in order to check 
/*
If the data value x is found, find() returns a pointer to the corresponding 
data value; otherwise it returns nullptr. Your find() method must run in time 
proportional to the height of the tree.
*/ 
const data_t* Treap::find(const data_t& x) {

  //base case 1: if the tree is empty then it will return nullptr
  if ( empty() == true ){
    return nullptr;
  }
  
  //base case 2: at leaf and x is not the lead return nullptr
  if ( x != _nptr->_data && _nptr->_left._nptr->_data.empty() && _nptr->_right._nptr->_data.empty()){
    return nullptr;
  }

  //base case 3: if you found x return it
  if(x == _nptr->_data){
    return &x;
  }

  //recursive case 1: if x < the current data go to the left child
  if(_nptr->_data < x ){
    _nptr->_left.find(x);
  }

  //recursive case 2: if x > the current data go to the right child 
  if(_nptr->_data > x){
    _nptr->_right.find(x);
  }

}

// Inorder traversal.  Recommend you NOT change this!!!
void Treap::inorder() {

  if ( empty() ) return ;

  cout << "(" ;
  _nptr->_left.inorder() ;

  cout << _nptr->_data << ":" << priority() << ":" << height() ;

  _nptr->_right.inorder() ;
  cout << ")" ;

  return  ;
}

// Used for debugging and grading.  Interprets the characters in
// position[] as directions in the tree.  E.g., "RLR" means, "starting
// from root, go right, then left, then right."  If position[] is an
// empty string, then it just locats the value a the root.
// See project description for details.
bool Treap::locate (const char position[], data_t& x, priority_t& p, int& h, int offset) {

  if (_nptr == nullptr) return false ;

  if (position[offset] == '\0') {
    x = _nptr->_data ;
    p = _nptr->_pri ;
    h = _nptr->_height ;
    return true ;
  }

  if (position[offset] == 'L') {
    return _nptr->_left.locate(position, x, p, h, offset+1) ;
  }

  if (position[offset] == 'R') {
    return _nptr->_right.locate(position, x, p, h, offset+1) ;
  }

  cerr << "Bad position character!\n" ;
  exit(17) ;

  return false ; 
}


// Basic BST insertion.  Does not allow duplicate values.
//
// Complete this function to do Treap insertion.
//
void Treap::insert(const data_t& x, const priority_t& p) {
  if ( empty() ) {
    _nptr = new TreapNode(x, p) ;
  }

  if (_nptr->_data < x) { 
    _nptr->_right.insert(x, p) ;
    
  } else if (x < _nptr->_data ) {
    _nptr->_left.insert(x, p) ;

  }

  // Update height. Maybe this should be a helper function??
  int leftHeight = _nptr->_left.height();
  int rightHeight = _nptr->_right.height();
  _nptr->_height = 1 + ( leftHeight > rightHeight ? leftHeight : rightHeight );

}

bool Treap::remove(const data_t& x) {
  //
  // Implement treap element removal
  //
}


// Treap::dump() just calls TreapNode::dump()
void Treap::dump() {
  if ( !empty() ) _nptr->dump() ;
}

ostream& operator<< (ostream& os, const Treap& T) {
  os << T._nptr ; 
  return os ;
}


TreapNode::TreapNode() : _height(0) {
  // Empty constructor body
}

TreapNode::TreapNode(const data_t& x, const priority_t& p) 
  : _data(x), _pri(p), _height(0) { 
  // Empty constructor body
}

TreapNode::~TreapNode() {
  // Empty destructor
  // Retained for debugging
}

// Dump the contents of a node
void TreapNode::dump() {
  cout << "===== TreapNode::dump()\n" ;
  cout << "      this = " << this << endl ; 
  cout << "      left = " << _left << endl ; 
  cout << "      right= " << _right << endl ; 
  cout << "      data = " << _data << endl ;
  cout << "      height = " << _height << endl ;
  _left.dump() ;
  _right.dump() ;
}

