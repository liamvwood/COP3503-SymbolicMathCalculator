//
// Created by Liam Wood on 4/20/17.
//

#ifndef CP3503PROJECT_INTEGER_H
#define CP3503PROJECT_INTEGER_H


#include "Expression.h"

class Integer: public Expression {
public:
    void setType();
    int getValue();
    void setIsSimplified();
    void printExpression();
    string toString();
    Integer(int val);
    Expression* simplify();
};


#endif //CP3503PROJECT_INTEGER_H
