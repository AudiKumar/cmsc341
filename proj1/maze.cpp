#include <stdexcept>
#include "maze.h"

using namespace std;


Maze::Maze(int ncell) {
  if (ncell < 1) {
    throw std::invalid_argument("Maze::Maze(): ncell must be >= 1");
  }

  _ncell = ncell;
  _maze = new cell_t[_ncell];
  //_mazeCopy = new cell_t[_ncell];
}

Maze::~Maze() {
  delete [] _maze;
  //delete [] _mazeCopy; 
}

void Maze::readFile(std::string fileName) {
  int numCells;
  int cell, n1, n2, n3, n4; 
  std::ifstream dataFile;
  
  dataFile.open(fileName);

  if (dataFile.is_open()) {
    dataFile >> numCells;
    this->reset(numCells);

    for (int i = 0; i < numCells; i++) {
      dataFile >> cell >> n1 >> n2 >> n3 >> n4;
      this->insert(cell_t(cell, n1, n2, n3, n4));
    }
  }
}

int Maze::getNcell() const {
  return _ncell;
}

void Maze::reset(int ncell) {
  if (ncell < 1) {
    throw std::invalid_argument("Maze::reset(): ncell must be >= 1");
  }

  if (_maze != nullptr) {
    delete [] _maze;
  }
  
  _ncell = ncell;
  _maze = new cell_t[_ncell];
  //_mazeCopy = new cell_t[_ncell];
}

void Maze::insert(cell_t cell) {
  if (_maze == nullptr) {
    throw std::domain_error("Maze::insert(): attempt to insert into uninitialized Maze object");
  }
  if (cell.cellNum < 0 || cell.cellNum >= _ncell) {
    throw std::invalid_argument("Maze:insert(): invalid cell number");
  }
  _maze[cell.cellNum] = cell;
  //_mazeCopy[cell.cellNum] = cell; //added copy so that you don't modfiy the og maze
}
  
cell_t Maze::retrieve(int nc) const {
  if (_maze == nullptr) {
    throw std::domain_error("Maze::retrieve(): attempt to retrieve from an uninitialized Maze object");
  }
  if (nc < 0 || nc >= _ncell) {
    throw std::invalid_argument("Maze:retrieve(): invalid cell index");
  }
  
  return _maze[nc];
}

void Maze::dump() const {

  std::cout << "[*] Dumping the maze cells..." << std::endl;
  
  for (int i = 0; i < _ncell; i++) {
    int nc = _maze[i].cellNum;
    if (nc != i) {
      std::cerr << "Warning: maze cell at index " << i
		<<" has cellNum of " << nc << std::endl;
    }
    std::cout << "Cell " << i << " has neighbor cells: ";
    neighbor_t nbs = _maze[i].neighbors;
    //int n0, n1, n2, n3;
    if ( nbs[0] >= 0 ) std::cout << nbs[0] << " ";
    if ( nbs[1] >= 0 ) std::cout << nbs[1] << " ";
    if ( nbs[2] >= 0 ) std::cout << nbs[2] << " ";
    if ( nbs[3] >= 0 ) std::cout << nbs[3] << " ";
    std::cout << std::endl;
  }
}

std::vector<int> Maze::solve() const {
  //makes a local copy of the maze 
  cell_t _mazeCopy[getNcell()];
  for (int x = 0; x < getNcell(); x++){
    _mazeCopy[x] = _maze[x];
  }
  
  //declares the SolveStack, and pushes the (-1, 0) into the stack
  //also sets a local prev and curr variable to the first and second of the stack
  Maze :: SolveStack s;
  s.push(pair <int,int>(VACANT, 0));
  int prev = s.read().first;
  int curr = s.read().second;

  //while the current index is not equal to the end of the maze and
  //the stack is not empty keep looking for a solution 
  while (curr != getNcell() - 1 && s.empty() == false){

    //local neighbor var for making the code look better
    neighbor_t n = _mazeCopy[s.read().second].neighbors;
   
    //loops through all of the all of the neighbhors until an option is found
    //that is not the previous cell 
    for (unsigned int i = 0; i < n.size(); i++){ 
      if(n[i] != VACANT && n[i] != prev){
       prev = curr;
       curr = n[i];
       s.push(pair<int, int>(prev, curr));
       break; 
      }
   }
    
    //popping back conditional: while the bool flag hasOption is false
    //, the stack is not empty and the curr is not at the end the loop
    //will execute  
    bool hasOption = false;
    while(hasOption == false && s.empty() == false && curr != getNcell() - 1){
      neighbor_t n2 = _mazeCopy[s.read().second].neighbors; 
      
      //checks to see if the top of the stack has an option for a path
      //that isn't the prev if it does the has option flag is flipped 
      //which leads to nothing being popped 
      for (unsigned int x = 0; x < n2.size(); x++){
       if (n2[x] != VACANT && n2[x] != prev){
          hasOption = true;
          break;      
       }
      } 
      
      //if you are at a dead end and the stack is not empty
      //pop from the top of the stack and set the curr and prev
      //to the "new values" at the top and mark a path as vacant
      if (hasOption == false && s.empty() == false){
        src_dest_t popVal = s.pop();
        if (s.empty() == false){
          neighbor_t n2 = _mazeCopy[s.read().second].neighbors;
          for (unsigned int i = 0; i < n2.size(); i++){
          
            if (n2[i] == popVal.second){
              _mazeCopy[s.read().second].neighbors[i] = VACANT;
              curr = s.read().second;
              prev = s.read().first;
            }
          }
        }
      }
    }
  }//end of while loop  

  
  
  Maze :: SolveStack t;
  vector<int> path;


  

  //inserts into the path array 
  while(!s.empty()){
    t.push(s.pop()); 
  }  

  while (!t.empty()){
    path.push_back(t.pop().second);
  }
 

 // cout << path.size() << endl;
  return path; 

}

Maze::SolveStack::SolveStack() {
  _stack = nullptr;
}

Maze::SolveStack::~SolveStack(){
    //StackEntry temp = entry_t;
    while(_stack != nullptr){ // entry_t is the typedef name
        entry_t* temp = _stack;
        _stack = _stack->next;
        delete temp;
        
    }
}

bool Maze::SolveStack::empty() const {
  return _stack == nullptr;
}
				   
void Maze::SolveStack::push(src_dest_t src_dest) {
    if(_stack == nullptr){
       _stack = new StackEntry(src_dest);
    }

    else{
        StackEntry* temp = new StackEntry(src_dest);
        temp->next = _stack;
        _stack = temp;
    }
}

src_dest_t Maze::SolveStack::pop() {
  if (_stack == nullptr){
      throw std::domain_error("Maze::SolveStack:pop() attempt to retrieve from an uninitialized Stack object");
  }

  else{
    src_dest_t data = _stack->src_dest;
    StackEntry* front = _stack;
    _stack = _stack->next;
    delete front;
    return data;
  }
}

src_dest_t Maze::SolveStack::read() const {
    if (_stack == nullptr){ 
        //src_dest_t front = _stack->source_dest;
        throw std::domain_error("Maze::SolveStack:read() attempt to retrieve from an uninitialized Stack object");

    }
    else{
        return _stack->src_dest;
    }
    
}




