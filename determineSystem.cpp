#include <iostream>

int main() {
    #ifdef _WIN32 // win32 are used to define both windows_32 and windows_64
        std::cout << "Windows system detected." << std::endl;
    #elif __APPLE__
        std::cout << "macOS system detected." << std::endl;
    #elif __linux__
        std::cout << "Linux system detected." << std::endl;
    #else
        std::cout << "Unknown system detected." << std::endl;
    #endif

    return 0;
}