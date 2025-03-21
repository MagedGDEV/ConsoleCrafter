#include <iostream>
#include "ansi/color/color.hpp"

int main(){

    std::cout << "Hello World" << std::endl;
    std::cout << "\033[32m" << "Hello World" << std::endl;
    std::cout << Color(ColorCode::RED) << "Hello World in style" << std::endl;
    return 0;
}