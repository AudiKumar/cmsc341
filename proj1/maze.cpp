#include <stdexcept>
#include "maze.h"

using namespace std;
void Maze :: checkNeighbors(src_dest_t p){
  int src = p.first;
  int dest = p.second;

}


Maze::Maze(int ncell) {
  if (ncell < 1) {
    throw std::invalid_argument("Maze::Maze(): ncell must be >= 1");
  }

  _ncell = ncell;
  _maze = new cell_t[_ncell];
  _mazeCopy = new cell_t[_ncell];
}

Maze::~Maze() {
  delete [] _maze;
  delete [] _mazeCopy; 
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
  _mazeCopy = new cell_t[_ncell];
}

void Maze::insert(cell_t cell) {
  if (_maze == nullptr) {
    throw std::domain_error("Maze::insert(): attempt to insert into uninitialized Maze object");
  }
  if (cell.cellNum < 0 || cell.cellNum >= _ncell) {
    throw std::invalid_argument("Maze:insert(): invalid cell number");
  }
  _maze[cell.cellNum] = cell;
  _mazeCopy[cell.cellNum] = cell; //added copy so that you don't modfiy the og maze
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
    int n0, n1, n2, n3;
    if ( nbs[0] >= 0 ) std::cout << nbs[0] << " ";
    if ( nbs[1] >= 0 ) std::cout << nbs[1] << " ";
    if ( nbs[2] >= 0 ) std::cout << nbs[2] << " ";
    if ( nbs[3] >= 0 ) std::cout << nbs[3] << " ";
    std::cout << std::endl;
  }
}

std::vector<int> Maze::solve() const {
  vector <int> path;
  Maze :: SolveStack s;
  s.push(pair <int,int>(VACANT, 0));
  int mazeIndex = 0;
  bool isSolved = false;

  while (isSolved == false && s.empty() == false){
    
    int src = s.read().first;
    int dest = s.read().second;
    int newSrc = VACANT;
    int newDest = VACANT;
    int nIndex; //neighbors index 
    cell_t currentCell = _mazeCopy[mazeIndex];
    cout << currentCell << endl; 
    int cellNum = currentCell.cellNum;
    neighbor_t& n = currentCell.neighbors;

    if (n[0] > 0 && n[0] != src ){
      newDest = n[0];
      nIndex = 0;
      mazeIndex = newDest;
      newSrc = dest;
      s.push(pair <int, int>(newSrc, newDest));
    }
    
    else if (n[1] > 0 && n[1] != src ){
      nIndex = 1;
      newDest = n[1];
      mazeIndex = newDest;
      newSrc = dest;
      s.push(pair <int, int>(newSrc, newDest)); 
    }

    else if (n[2] > 0 && n[2] != src ){
      nIndex = 2;
      newDest = n[2];
      mazeIndex = newDest;
      newSrc = dest;
      s.push(pair <int, int>(newSrc, newDest)); 
    }

    else if  (n[3] > 0 && n[3] != src ){
      nIndex = 3; 
      newDest = n[3];
      mazeIndex = newDest;
      newSrc = dest;
      s.push(pair <int, int>(newSrc, newDest));
    }

    //treached when you need to pop stacks
    else{
      cout << "\n\n\n\n\n";      
      cout << "before _mazeCopy being changed\n" << _mazeCopy[mazeIndex]  << endl;
      cout << nIndex << endl; 


      _mazeCopy[mazeIndex].neighbors[nIndex - 1] = VACANT; 

      cout << "after _mazeCopy being changed\n" << _mazeCopy[mazeIndex] << endl;
      
      src_dest_t popVal = s.pop();


      mazeIndex = popVal.first; //src becomes the new mazeIndex
      cout << "stack is now poped\n" << popVal.first << "      " << popVal.second << endl; 
      src = popVal.second; 
      src_dest_t p = s.read();
      
      cout << "new top of the stack\n" << p.first << "         " << p.second << endl;
      /* OLD STUFF THAT YOU TRIED THAT DIDN'T WORK OR THAT YOU DON"T NEED FOR NOW
      
      //currentCell.neighbors[nIndex - 1] = VACANT; 
      //n[nIndex - 1] = VACANT;
      //_mazeCopy[] = VACANT;

      
      //cout << "CONDITION WHERE YOU POP\n" << endl;
      mazeIndex = popVal.first;
      newDest = popVal.first;
      newSrc = popVal.second;
      cout << "src: " << src << endl;
      */
     
    }
    
  }

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
