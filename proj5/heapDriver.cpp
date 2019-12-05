#include <iostream>
#include "heap.h"
#include "donut.h"
#include <vector>

int main(){
    
    vector <Donut> donuts;    
    Heap <Donut> h;
    
    donuts.push_back(Donut("glazed", 5, "super donut"));
    donuts.push_back(Donut("glazed", 12, "mega donut"));
    donuts.push_back(Donut("glazed", 4, "shack of donuts"));
    donuts.push_back(Donut("boston cream", 10, "mega donut"));
    donuts.push_back(Donut("boston cream", 5, "donut world"));
    donuts.push_back(Donut("sprinkle", 7, "donut world"));
    donuts.push_back(Donut("sprinkle", 15, "super donut"));
    donuts.push_back(Donut("sprinkle", 8, "shack of donuts"));
    donuts.push_back(Donut("boston cream", 3, "donut joint"));
    donuts.push_back(Donut("cinnamon", 3, "shack of donuts"));
    donuts.push_back(Donut("bavarian cream", 28, "mega donut"));
    donuts.push_back(Donut("cinnamon", 11, "super donut"));

    cout << "first insert" << endl;
    //h.insert(donuts.at(0));
    //cout << "asdf" << endl;
    //h.dump();
    

    //cout << "second insert " << endl;
    //h.insert(donuts.at(1));
    h.dump();
}//end of main