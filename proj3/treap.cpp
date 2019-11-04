// CMSC 341 - Fall 2019 - Project 3
// File: treap.cpp

using namespace std ;

#include "treap.h"

Treap::Treap() {
  _nptr = nullptr ;
}

Treap::Treap(const Treap& other) {
  //_nptr = new TreapNode();
  copyHelper(other);
}

Treap::~Treap() {
  // this implementations of the destructor assumes that the remove works
  // bassically will remove the root and rebalance until there's nothing 
  // there anymore
  //cout << "in desctrutor" << endl;
  //while(_nptr != nullptr){
   // remove(_nptr->_data);
  //}
  if(_nptr != nullptr){
    delete _nptr;
    _nptr = nullptr;
  }

}

const Treap& Treap::operator=(const Treap& rhs) {
  //
  // Implement assignment operator
  //
  if (this == &rhs)
    return *this;
  
  while(_nptr != nullptr){
    remove(_nptr->_data);
  }

  copyHelper(rhs);

  return *this;
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
  if ( x != _nptr->_data && isLeaf()){
    return nullptr;
  }

  //base case 3: if you found x return it
  if(x == _nptr->_data){
    return &_nptr->_data;
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
    _nptr->_right.insert(x, p);

    if(_nptr->_pri < p){
      roatateLeft(_nptr, _nptr->_right._nptr);
    }
      
    
  } else if (x < _nptr->_data ) {
    _nptr->_left.insert(x, p) ;

    if(_nptr->_pri < p){
      rotateRight(_nptr, _nptr->_left._nptr);
    }
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
  if (empty()){
    return false;
  }

  if (_nptr->_data < x){
    _nptr->_right.remove(x);
  }

  if (_nptr->_data > x){
    _nptr->_left.remove(x);
  }

  if(_nptr->_data == x){
    //simple case of remove being a lead node
    if(_nptr->_left.empty() && _nptr->_right.empty()){
      delete _nptr;
      _nptr = nullptr;
      return true;
    }

    //you have to do this whole rotate down thing
    else{
      //if there is a left but no right do a right rotation
      if( (_nptr->_right.empty()) && !(_nptr->_left.empty()) ){
        rotateRight(_nptr, _nptr->_left._nptr);
        remove(x);
      }

      
      //if there is a right but no left do a left rotation
      if ( !(_nptr->_right.empty()) && _nptr->_left.empty() ){
        roatateLeft(_nptr, _nptr->_right._nptr);
        remove(x);
      }
      
      //if both childern are present then compare to see which one has the highest
      //priority
      if(!(_nptr->_left.empty()) && !(_nptr->_right.empty())){
        if(_nptr->_right.priority() > _nptr->_left.priority()){
          roatateLeft(_nptr, _nptr->_right._nptr);
          remove(x);
        }

        else{
          rotateRight(_nptr, _nptr->_left._nptr);
          remove(x);
        }
      }
    }    
    /*
    do{
      cout <<"here" << endl;
      rotateDown(_nptr);
    }while(!(_nptr->_right.empty()) && !(_nptr->_left.empty()) );
    */
    delete _nptr;
    _nptr = nullptr;
    return true;
  }

  //if you get to a leaf not and remove is not found then you know the data 
  //is not in the tree therefore you don't 
  if(_nptr == nullptr){
    return false;
  }

}


// Treap::dump() just calls TreapNode::dump()
void Treap::dump() {
  if ( !empty() ) _nptr->dump() ;
}


//helper treaps fns
void Treap :: rotateDown(TreapNode* nodeToRotate){
  cout << "in rotate down" << endl;

  cout << endl;
  inorder();
  cout << endl;

  //if both childern present check both to see which one should be moved up
  if( !(nodeToRotate->_right.empty()) && !(nodeToRotate->_left.empty()) ){
    
    //if right is bigger than the left do a left rotation
    if (nodeToRotate->_right.priority() > nodeToRotate->_left.priority())
      roatateLeft(nodeToRotate, nodeToRotate->_right._nptr);
    //else do a right rotation
    else{
      rotateRight(nodeToRotate, nodeToRotate->_left._nptr);
    }
    return; 
  }
  //if it's just the right child there do a left rotation
  if (!(nodeToRotate->_right.empty()) && nodeToRotate->_left.empty()){
    roatateLeft(nodeToRotate, nodeToRotate->_right._nptr);
    return;
  }

  //if it's just the left child there do a right rotation
  if(!(nodeToRotate->_left.empty()) && nodeToRotate->_right.empty()  ){
    rotateRight(nodeToRotate, nodeToRotate->_left._nptr);
    return;
  }

}


bool Treap :: isLeaf(){
  if (_nptr->_data.empty() == false){
    if (_nptr->_left._nptr->_data.empty() && _nptr->_right.empty()){
      return true;
    }
    return false;
  }
  return false;  
}
//to get the right child as a TreapNode* 
void Treap :: rotateRight(TreapNode* parent, TreapNode* leftChild){
  //cout << "in rotate right" << endl;
  TreapNode* subtree = leftChild->_right._nptr; 
  leftChild->_right._nptr = parent;
  parent->_left._nptr = subtree;
  _nptr = leftChild;
  
  //left child (now the parent) goes up so subtract by 1
  _nptr->_height = _nptr->_height - 1;

  //parent (now the left child of the new parent (old left child)) goes down so add 1
  _nptr->_right._nptr->_height = _nptr->_right._nptr->_height + 1;
}

void Treap :: roatateLeft(TreapNode* parent, TreapNode* rightChild){
  //cout << "in roate left" << endl;
  //if()
  TreapNode* subtree= rightChild->_left._nptr;


  //cout << "subtree: " << subtree->_data << end;
  rightChild->_left._nptr = parent;
  parent->_right._nptr = subtree;
  _nptr = rightChild;


  //right child (now the parent) goes up so subtract by 1
  _nptr->_height = _nptr->_height - 1;

  //parent (now the left child of the new parent (old right child)) goes down so add 1
  _nptr->_left._nptr->_height = _nptr->_left._nptr->_height + 1;
}


TreapNode*  Treap :: copyHelper(const Treap& other){
  //base case:  
  if (other._nptr == nullptr){
    return nullptr; 
  }

  //recursive case
  else{
    if(other._nptr->_left.empty() == false){
      _nptr = new TreapNode(other._nptr->_data, other._nptr->_pri);
      return _nptr->_left._nptr =  copyHelper(other._nptr->_left);
    }
    if(other._nptr->_right.empty() == false){
       _nptr = new TreapNode(other._nptr->_data, other._nptr->_pri);
       return _nptr ->_right._nptr = copyHelper(other._nptr->_right);
    }
  }

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
