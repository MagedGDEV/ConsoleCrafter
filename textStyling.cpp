#include <iostream>
using std::cout;
using std::endl;

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

int main(){

    #ifdef _WIN32
        enableANSI();
    #endif

    // Text styling
    //  Bold
    cout << "\033[1m" << "Bold text" << "\033[0m" << endl;
    //  Dim
    cout << "\033[2m" << "Dim text - doesn't work on windows" << "\033[0m" << endl;
    // Light gray (simulating dim)
    cout << "\033[38;5;245m" << "Dim-like text for windows" << "\033[0m" << endl;
    // Italic
    cout << "\033[3m" << "Italic text" << "\033[0m" << endl;
    //  Underlined
    cout << "\033[4m" << "Underlined text" << "\033[0m" << endl;
    // Blink
    cout << "\033[5m" << "Blink text - doesnt work on windows" << "\033[0m" << endl;
    // Strike through
    cout << "\033[9m" << "Strike through text" << "\033[0m" << endl;
    // Overline
    cout << "\033[53m" << "Overline text" << "\033[0m" << endl;
    // invert colors
    cout << "\033[7m" << "Inverted text" << "\033[0m" << endl;
    // invisible text
    cout << "\033[8m" << "Invisible text" << "\033[0m" << endl;
    return 0;
}