#include <iostream>
#include <string>
using namespace std;

int main(){

    string test = "     this is a test      ";

    cout << "before change: " << test << endl;

    const auto strBegin = test.find_first_not_of(" ");
    const auto strEnd = test.find_last_not_of(" "); 
    const auto strRange  = strEnd - strBegin + 1;

    test = test.substr(strBegin, strRange);

    cout << "after change: " << test << endl;

    return 0;
}