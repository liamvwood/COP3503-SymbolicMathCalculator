//
// Created by Liam Wood on 4/20/17.
//

#ifndef CP3503PROJECT_SUBTRACTION_H
#define CP3503PROJECT_SUBTRACTION_H


#include "Expression.h"

class Subtraction: public Expression {
public:
    Expression* subtractFractions();
    string toString();
    void setIsSimplified();
    void setType();
    void printExpression();
    Expression* simplify();
    int getValue();
};


#endif //CP3503PROJECT_SUBTRACTION_H
