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


    cout << "###########################################################" << endl;
    cout << "TESTING insert and dump" << endl;
    cout << "###########################################################" << endl;
    for (unsigned int x = 0; x < donuts.size(); x++){
    //for (unsigned int x = 0; x < donuts.size(); x++){
        h.insert(donuts.at(x));
        h.dump();
    }

    cout << "\n\n\n\n###########################################################" << endl;
    cout << "TESTING read and removeTop" << endl;
    cout << "###########################################################" << endl;   
    cout << "The Top of the Heap is " << h.readTop() << endl;
    
    cout << "ABOUT TO REMOVE THE TOP" << endl;
    h.removeTop();
    //cout << "before the dump" << endl;
    h.dump();
}//end of main