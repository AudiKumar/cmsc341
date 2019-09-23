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

  //makes a local copy for the solve fn 
  cell_t _mazeCopy[getNcell()];
  for (int x = 0; x < getNcell(); x++){
    _mazeCopy[x] = _maze[x];
  }

  Maze :: SolveStack s;
   
  s.push(pair <int,int>(VACANT, 0));
  int src = s.read().first;
  int dest = s.read().second;

  cell_t currentCell = _mazeCopy[dest];
  int nIndex = 0;
  
  //FIGURE OUT THE N INDEX 

  //first in the pair is previous seccond in the path is curr
  while (dest != getNcell()-1 && s.empty() == false){
    
    //"src(prev)" << src << endl; 
    //currentCell = _mazeCopy[dest];
  //  cout << "src: " << src << "\ndest: " << dest << "\nNeighbhors: " << endl;
    //for (int i = 0; i < 4; i++){
     // cout << "Neighbhor " << i + 1 << _mazeCopy[dest].neighbors[i] << endl;  
    //}   
    neighbor_t n = currentCell.neighbors;
    //cout <<"in loop " << endl;

    if (n[0] >= 0 && n[0] != src ){
      src = dest;
      dest = n[0];
      nIndex = 0; // keeps track if the neighbor index to be used in the pop else
      s.push(pair <int, int>(src, dest));
      //cout << src << "     " << dest << endl;
      currentCell = _mazeCopy[dest]; 
    }

    else if (n[1] >= 0 && n[1] != src ){
      //cout <<"asdfasdf" <<endl;
      src = dest;
      dest = n[1];
      nIndex = 1; // keeps track if the neighbor index to be used in the pop else
      s.push(pair <int, int>(src, dest));
      //cout << src << "     " << dest << endl;
    //  if (!s.empty()){
      //    cout << "stack incremented" << endl;
     // }
      currentCell = _mazeCopy[dest]; 
  
    }

    else if (n[2] >= 0 && n[2] != src ){
      src = dest;
      dest = n[2];
      nIndex = 2; // keeps track if the neighbor index to be used in the pop else
      s.push(pair <int, int>(src, dest));
      currentCell = _mazeCopy[dest];
      //if (!s.empty()){
       //   cout << "stack incremented" << endl;
      //}  
    }

    else if  (n[3] >= 0 && n[3] != src ){
      src = dest;
      dest = n[3];
      nIndex = 3; // keeps track if the neighbor index to be used in the pop else
      s.push(pair <int, int>(src, dest));
      currentCell = _mazeCopy[dest];

      //if (!s.empty()){
      //    cout << "stack incremented" << endl;
      //} 
    }

    //treached when you need to pop stacks
    else{

      //cout << "nIndex: "<< nIndex << "    value:" << _mazeCopy[dest].neighbors[nIndex] << endl;
      bool hasOptions = false;

      do{          

        src_dest_t popVal = s.pop();
        src = popVal.first; //previous
        dest = popVal.second; //current

        int nIndex = getNIndex(dest, src, _mazeCopy);

        _mazeCopy[dest].neighbors[nIndex] = VACANT;

        //check all four spots and flip the boolean if you find an index 
        // that isn't -1 or equal to the dest's prev
        //keep going back until you have other options besides go back 
        if (s.empty() == false){

          src_dest_t otherVal = s.read();
          int newSrc = otherVal.first; // previous space
          int newDest = otherVal.second; // where you were headed

          if(_mazeCopy[newDest].neighbors[0] > VACANT && _mazeCopy[dest].neighbors[0] != newSrc ){
            nIndex = 0;
            hasOptions = true;
          }
          else if(_mazeCopy[newDest].neighbors[1] > VACANT && _mazeCopy[dest].neighbors[1] != newSrc){
            nIndex = 1;
            hasOptions = true;
          }
          else if(_mazeCopy[newDest].neighbors[2] > VACANT && _mazeCopy[dest].neighbors[2] != newSrc){
            nIndex = 2;
            hasOptions = true;
          }
          else if(_mazeCopy[newDest].neighbors[3] > VACANT && _mazeCopy[dest].neighbors[3] != newSrc){
            nIndex = 3;
            hasOptions = true;
          }
          else{
            cout << "ERROR IN do while for the solve function when popping back" << endl;
          }

          currentCell = _mazeCopy[dest]; 
        }


      }while(hasOptions == false && s.empty() == false);


    }// end of popback else
  }//end of solve stack while loop


  vector <int> path;
  vector <int> :: iterator it;

  it = path.begin();

  //inserts into the path array 
  while(!s.empty()){
    it = path.insert(it, s.pop().second);
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


int Maze :: getNIndex(int dest, int src, cell_t* _mazeCopy) const{
  int nIndex;
  
  //check all of the neighbhors and see if it it == to the current [dest]
  if (_mazeCopy[dest].neighbors[0] == src){
    nIndex = 0;
  }

  //check all of the neighbhors and see if it it == to the current [dest]
  if (_mazeCopy[dest].neighbors[1] == src){
    nIndex = 1;
  }

  //check all of the neighbhors and see if it it == to the current [dest]
  if (_mazeCopy[dest].neighbors[2] == src){
    nIndex = 2;
  }

  
  if (_mazeCopy[dest].neighbors[3] == src){
    nIndex = 3;
  } 

  return nIndex;
}



