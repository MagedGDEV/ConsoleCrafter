#ifndef _COLOR_H_
#define _COLOR_H_

#include "../ansi_formatter/ansi_formatter.hpp"

struct RGB{
    int r, g, b;
};

enum ColorCode {
    RED = 31,
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