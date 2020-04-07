//
// Created by Liam Wood on 4/20/17.
//

#ifndef CP3503PROJECT_DIVISION_H
#define CP3503PROJECT_DIVISION_H


#include "Expression.h"

class Division: public Expression {
public:
    int denominator, numerator;
    bool isNegative;
    void setType();
    string toString();
    void setIsSimplified();
    Expression* simplify();
    void printExpression();
    int getValue();
    Expression* reduce();

};


#endif //CP3503PROJECT_DIVISION_H
