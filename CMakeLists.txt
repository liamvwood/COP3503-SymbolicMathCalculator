cmake_minimum_required(VERSION 3.6)
project(CP3503Project)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Token.cpp Token.h Calculator.cpp Calculator.h Expression.cpp Expression.h Multiplication.cpp Multiplication.h Addition.cpp Addition.h Subtraction.cpp Subtraction.h Division.cpp Division.h NthRoot.cpp NthRoot.h Exponentiation.cpp Exponentiation.h Integer.cpp Integer.h ErrorException.cpp ErrorException.h)
add_executable(CP3503Project ${SOURCE_FILES})