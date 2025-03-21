#ifndef _ANSI_FORMATTER_H_
#define _ANSI_FORMATTER_H_

#include <string>

class AnsiFormatter{

protected:
    std::string ANSI_CODE;
public:
    virtual ~AnsiFormatter() = 0;
};

#endif