#include "color.hpp"


Color::Color(RGB color, bool isBackground){
    setColor(color, isBackground);
}

Color::Color(int code, bool isBackground){
    setColor(code, isBackground);
}

void Color::setColor(RGB color, bool isBackground){
    ANSI_CODE = "\033[";
    ANSI_CODE += (isBackground ? "48;2;":"38;2;") + std::to_string(color.r);
    ANSI_CODE += ";" + std::to_string(color.g);
    ANSI_CODE += ";" + std::to_string(color.b);
    ANSI_CODE += "m";
}
void Color::setColor(int code, bool isBackground){
    ANSI_CODE = "\033[" + std::to_string(isBackground ? code + 10 : code);
    ANSI_CODE += "m";
}


std::ostream& operator<<(std::ostream &os, const Color &obj) {
    printf("%s", obj.ANSI_CODE.c_str());
    return os;
}