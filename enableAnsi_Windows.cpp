#include <iostream>
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

int main() {
    enableANSI();

    // Now ANSI escape codes should work
    std::cout << "\033[31mThis is red text.\033[0m" << std::endl;
    std::cout << "\033[42;97mThis has a green background and white text.\033[0m" << std::endl;

    return 0;
}