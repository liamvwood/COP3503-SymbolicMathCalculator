//
// Created by Liam Wood on 4/20/17.
//

#ifndef CP3503PROJECT_EXPONENTIATION_H
#define CP3503PROJECT_EXPONENTIATION_H


#include "Expression.h"

class Exponentiation: public Expression{
public:
    void setIsSimplified();
    void setType();
    string toString();
    string type = "exponentiation";
    Expression* simplify();
    int getValue();
    void printExpression();
};


#endif //CP3503PROJECT_EXPONENTIATION_H
