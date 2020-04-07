//
// Created by Liam Wood on 4/20/17.
//

#ifndef CP3503PROJECT_NTHROOT_H
#define CP3503PROJECT_NTHROOT_H


#include "Expression.h"

class NthRoot: public Expression {
public:
    int coefficient, radicand, nth;
    void setIsSimplified();
    void setType();
    string toString();
    void printExpression();
    Expression* simplify();
    Expression* reduce();
    int getValue();
};


#endif //CP3503PROJECT_NTHROOT_H
