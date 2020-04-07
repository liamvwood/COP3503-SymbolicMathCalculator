//
// Created by Liam Wood on 4/18/17.
//

#ifndef CP3503PROJECT_CALCULATOR_H
#define CP3503PROJECT_CALCULATOR_H
#include <vector>
#include "Expression.h"
#include <string>
using namespace std;

class Calculator {
public:
    string input;
    vector<Expression*> prevAns;
    vector<double> prevAnsFP;
    bool showFloatingPoint;
    bool isRunning = true;
    Token* evaluate(Token*, vector<Token*>);
    double calculateFP(vector<Token*>);
    void help();
    void quit();
    void run();
    void memory();
    void operations();
    void togFP();
    void checkInput(string);
    vector <Token*> checkForAns(string);
    Expression* simplifyExpression(vector<Token*>);
};


#endif //CP3503PROJECT_CALCULATOR_H
