
cmake_minimum_required(VERSION 3.10)
project(ConsoleCrafter VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable( console_crafter.out
    src/ansi/ansi_formatter/ansi_formatter.hpp
    src/ansi/color/color.hpp

    src/ansi/ansi_formatter/ansi_formatter.cpp
    src/ansi/color/color.cpp

    src/main.cpp
)