#include <iostream>
#include "ansi/color/color.hpp"

int main(){

    std::cout << Color(ColorCode::RED) << "Hello World in style" << std::endl;
    return 0;
}