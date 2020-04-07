//
// Created by Liam Wood on 4/20/17.
//

#ifndef CP3503PROJECT_ADDITION_H
#define CP3503PROJECT_ADDITION_H


#include "Expression.h"
#include <typeinfo>

class Addition: public Expression {
public:
    string toString();
    Expression* addFractions();
    void setIsSimplified();
    void setType();
    Expression* simplify();
    int getValue();
    void printExpression();
};


#endif //CP3503PROJECT_ADDITION_H
