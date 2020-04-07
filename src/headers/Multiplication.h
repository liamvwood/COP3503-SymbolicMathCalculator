//
// Created by Liam Wood on 4/20/17.
//

#ifndef CP3503PROJECT_MULTIPLICATION_H
#define CP3503PROJECT_MULTIPLICATION_H


#include "Expression.h"

class Multiplication: public Expression {
public:
    Expression* multiplyFractions();
    void setIsSimplified();
    void setType();
    string toString();
    void printExpression();
    Expression* simplify();
    int getValue();
};


#endif //CP3503PROJECT_MULTIPLICATION_H
