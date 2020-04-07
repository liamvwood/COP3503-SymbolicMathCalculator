//
// Created by Liam Wood on 4/24/17.
//

#ifndef CP3503PROJECT_ERROREXCEPTION_H
#define CP3503PROJECT_ERROREXCEPTION_H
#include "Expression.h"

class ErrorException: public Expression {
public:
    ErrorException(string str);
    string exception;
    void setType();
    string toString();
    void setIsSimplified();
    Expression* simplify();
    void printExpression();
    int getValue();

};


#endif //CP3503PROJECT_ERROREXCEPTION_H
