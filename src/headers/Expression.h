//
// Created by Liam Wood on 4/18/17.
//

#ifndef CP3503PROJECT_EXPRESSION_H
#define CP3503PROJECT_EXPRESSION_H
#include "Token.h"
#include <vector>
#include <string>

class Expression {
public:

    double value = 0;
    bool isSimplified;
    bool cannotSimplify;
    string type = "DEBUG";
    string valueString = "test";
    virtual string toString() = 0;
    virtual void printExpression() = 0;
    virtual int getValue() = 0;
    virtual void setIsSimplified() = 0;
    virtual void setType() = 0;

    Expression* leftSide;
    Expression* rightSide;

    Expression* getLeftSide();
    Expression* getRightSide();
    vector<Expression*> getNumeratorFactors();
    vector<Expression*> getDenominatorFactors();
    vector<Expression*> getAdditiveTerms();

    virtual Expression* simplify() = 0;
};


#endif //CP3503PROJECT_EXPRESSION_H
