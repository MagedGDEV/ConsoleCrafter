#include <iostream>
#include <cstdlib>  
using std::cout;
using std::endl;
using std::cin;

// Example: Clearing console using ASCII Escape codes
// This should works Cross-Platfrom

int main (){

    cout << "Helllooo, I am maged" << endl;
    cout << "I am Computer Engineer" << endl;
    cout << "Age: 24" << endl;
    cout << "I am looking for a job" << endl;
    cout << "C++ Developer" << endl;
    
    int x;
    cin >> x;

    if (x == 5){
        cout << "\033[2J\033[H";
        cout << "Cleared" << endl;
    }

    return 0;
}