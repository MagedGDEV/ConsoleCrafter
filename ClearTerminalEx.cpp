#include <iostream>
#include <cstdlib>  
using std::cout;
using std::endl;
using std::cin;

#ifdef _WIN32

    #include <windows.h>
    // Define ENABLE_VIRTUAL_TERMINAL_PROCESSING if not already defined
    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
    #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
    #endif

    void enableANSI() {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut == INVALID_HANDLE_VALUE) return;

        DWORD dwMode = 0;
        if (!GetConsoleMode(hOut, &dwMode)) return;

        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        if (!SetConsoleMode(hOut, dwMode)) return;
    }

#endif

// Example: Clearing console using ASCII Escape codes
// This should works Cross-Platfrom

int main (){

    #ifdef _WIN32
        enableANSI();
    #endif

    cout << "Helllooo, I am maged" << endl;
    cout << "I am Computer Engineer" << endl;
    cout << "Age: 24" << endl;
    cout << "I am looking for a job" << endl;
    cout << "C++ Developer" << endl;
    
    int x;
    cin >> x;

    if (x == 5){
        cout << "\033[2J\033[3J\033[H";
        cout << "Cleared" << endl;
    }

    return 0;
}
