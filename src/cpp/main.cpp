#include "Calculator.h"
#include <iostream>
using namespace std;

int main() {

    cout << "Welcome to Liam Wood's Computer-Based Symbolic Math System V0.9\n"
         << "Enter an expression or 'help' to get started\n";

    Calculator* calculator  = new Calculator();

    calculator->run();

    return 0;
}
// Work Cited
// WhatsACreel. "C# Windows 8 Tutorial 6: Final." YouTube. YouTube, 16 Dec. 2013. Web. 03 Mar. 2017.