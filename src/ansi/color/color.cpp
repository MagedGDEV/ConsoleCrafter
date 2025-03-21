#include "color.hpp"
#include <iostream>

Color::Color(RGB color){
    ANSI_CODE = "\033[38;2;" + std::to_string(color.r);
    ANSI_CODE += ";" + std::to_string(color.g);
    ANSI_CODE += ";" + std::to_string(color.b);
    ANSI_CODE += "m";
}

Color::Color(std::string code){
    ANSI_CODE += "\033[" + code;
    ANSI_CODE += "m";
}




std::ostream& operator<<(std::ostream &os, const Color &obj) {
    os << obj.ANSI_CODE;
    return os;
}