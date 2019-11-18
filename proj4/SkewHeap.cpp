#include "SkewHeap.h"

// Constructor.  Must specify priority function.
  SkewHeap :: SkewHeap(pri_fn pri){
      priority = pri;
      m_heap = nullptr;
  }
  // Destructor, copy constructor, assignment operator  WAIT ON IT MIGHT HAVE TO 
  // DO MORE THAN JUST DELETE THE m_heap 
  SkewHeap :: ~SkewHeap(){
      while(m_heap != nullptr){
          removeTop();
      }
  }

  SkewHeap :: SkewHeap(const SkewHeap& rhs){
      priority = rhs.priority;
      m_heap = copyHelper(rhs.m_heap);
  }
  
  const  SkewHeap& SkewHeap :: operator=(const SkewHeap& rhs){
    if( this != &rhs){
        if(m_heap != nullptr){
            while(m_heap != nullptr){
                removeTop();
            }
        }
        priority = rhs.priority;
        m_heap = copyHelper(rhs.m_heap);
    }
    return *this;
    
  }

  // Priority function get and set
  pri_fn SkewHeap :: getPriFn() const{
      return priority;
  }

  void SkewHeap :: setPriFn (pri_fn pri){
      SkewHeap temp(pri);
      while(m_heap != nullptr){
        if (m_heap->tagged_union == ISINT){
            temp.insert(m_heap->data_int);
        }
        if (m_heap->tagged_union == ISSTRING){
            temp.insert(m_heap->data_int);
        }
        removeTop();
      }

      m_heap = temp.m_heap; 
      //this is gonna be annoying too
  }

  // Return true if the skew heap is empty
  bool SkewHeap :: empty() const{
      return m_heap == nullptr;
  }

  // Overloaded insertion operators.  One for string data, one for
  // integer data.
  void SkewHeap :: insert(string data){
      Node* newNode = new Node(data);
      m_heap = mergeHelper(m_heap, newNode);  
      //cout << "sadfads" << endl; 
  }
  void SkewHeap :: insert(int data){
      //make a new node for data, merge m_heap and newNode
      Node* newNode = new Node(data);
      m_heap = mergeHelper(m_heap, newNode);
      //cout << "asdfsadf" << endl; 
  }

  // Access highest priority element in the skew heap.
  Node* SkewHeap :: front() const{
      return m_heap;
  }

  // Remove the highest priority element from the skew heap.
  void SkewHeap :: removeTop(){
      if( !empty() ){
        Node* leftSubtree = m_heap->left;
        Node* rightSubtree = m_heap->right;
        delete m_heap;
        m_heap = mergeHelper(leftSubtree, rightSubtree); 
      }
  }

  // Merge two heaps.  Merged heap in *this; sh is empty afterwards.
  void SkewHeap :: skewHeapMerge(SkewHeap& sh){
      if(priority != sh.priority){
          throw domain_error("different priority functions.");
      }

      else{
          m_heap = mergeHelper(m_heap, sh.m_heap);
          sh.m_heap = nullptr;
      }
  }

  // Print inorder traversal.
  void SkewHeap :: inorder() const{
    
      cout << "SKEW HEAP: IN ORDER" << endl;
      if (m_heap)
      inOrderHelper(m_heap);
  }
  
  // Dump the contents of the heap in decreasing priority order.
  void SkewHeap :: dump() const{
      //make a copy of the heap you havea
      SkewHeap copy = *this;  
      //read off the top and keep removing
      while( !copy.empty() ){
          
         if (copy.m_heap->tagged_union == ISINT){
             cout << "Data Is: " << copy.m_heap->data_int; 
             cout << "    Priority Is: " << priority(copy.m_heap); 
        }

        if (copy.m_heap->tagged_union == ISSTRING){
             cout << "Data Is: " << copy.m_heap->data_string; 
             cout << "   Priority Is:" << priority(copy.m_heap); 
        } 
        cout << endl;
         copy.removeTop(); 
      }
      //until the copy is empty
      
  }


  /*
  ########################################################################
   HELPER 
  ########################################################################
  */




 void SkewHeap :: inOrderHelper(Node* n) const{
    if ( n == nullptr ) return;

    if (n->tagged_union == ISINT){
        cout << "(" ;
        inOrderHelper(n->left);
        cout << n->data_int;
        inOrderHelper(n->right);
        cout << ")" ;
    }

    if (n->tagged_union == ISSTRING){
        cout << "(" ;
        inOrderHelper(n->left);
        cout << n->data_string;  
        inOrderHelper(n->right);
        cout << ")" ;
    }
 }


 Node* SkewHeap :: mergeHelper(Node* p1, Node* p2){

    //cout << "MERGE HELPER" << endl;
    // If either heap is empty, return the other
    if (p1 == nullptr) return p2;     
    if (p2 == nullptr) return p1;

    // Ensure p1 has higher priority root
    if(priority(p1) < priority(p2)) swap(p1, p2);

    // Swap the left and right children of p1  
    swap(p1->left, p2->right);

    // Recursively merge p1's left child with p2; make the
    // merged heap the new left child of p1		       
    p1->left = mergeHelper( p1->left, p2 );

    return p1; 
 } 

/*
 void SkewHeap :: swap(Node* p1, Node* p2){
    swap(p1, p2);
 }
*/

Node* SkewHeap :: copyHelper(Node* n){
    if (n == nullptr) return nullptr;

    else{
        Node* t;
        if(n->tagged_union == ISSTRING){
            t = new Node(n->data_string);  
        }

        if(n->tagged_union == ISINT){
            t = new Node(n->data_int);
        }

        t->left = copyHelper(n->left);
        t->right = copyHelper(n->right);
        return t;
    }
}
