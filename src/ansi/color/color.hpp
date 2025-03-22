#ifndef _COLOR_H_
#define _COLOR_H_

#include "../ansi_formatter/ansi_formatter.hpp"
#include "ColorCode.hpp"

struct RGB{
    int r, g, b;
    RGB(int red, int green, int blue): r{red}, g{green}, b{blue} {}
};


class Color : public AnsiFormatter {
    friend std::ostream& operator<<(std::ostream &os, const Color &obj);
public:
    Color(RGB color, bool isBackground = false);
    Color(int code, bool isBackground = false);
    void setColor(RGB color, bool isBackground = false);
    void setColor(int code, bool isBackground = false);
    
};

#endif