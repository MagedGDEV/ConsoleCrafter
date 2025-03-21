#ifndef _COLOR_H_
#define _COLOR_H_

#include "../ansi_formatter/ansi_formatter.hpp"


struct RGB{
    int r, g, b;
};

struct ColorCode {
    inline static const std::string RED = "31";
};

class Color : public AnsiFormatter {

public:
    Color(RGB color);
    Color(std::string code);
private:
    friend std::ostream& operator<<(std::ostream &os, const Color &obj);
};


#endif