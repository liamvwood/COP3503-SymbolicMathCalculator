//
// Created by Liam Wood on 4/20/17.
//

#include "NthRoot.h"
#include "Integer.h"
#include <cmath>
#include <iostream>
#include "Multiplication.h"
#include "ErrorException.h"

Expression* NthRoot::simplify() {

    if(this->leftSide->getValue() == 0){
        this->leftSide = this->leftSide->simplify();
    }
    if(this->rightSide->getValue() == 0){
        this->rightSide = this->rightSide->simplify();
    }

    this->leftSide->setType();
    this->rightSide->setType();

    return reduce();
    //return new Integer(pow(this->rightSide->getValue(), (1 / this->leftSide->getValue())));

}

Expression* NthRoot::reduce() {

    coefficient = 1;
    radicand = this->rightSide->getValue();
    nth = this->leftSide->getValue();
    int d = 2;

    if(nth % 2 == 0 && radicand < 0){
        return new ErrorException("ERROR: Cannot take positive root of negative number");
    }

    while ((int)pow(d,nth) <= radicand) {

        if (radicand % (int)(pow(d,nth)) == 0) {
            radicand = radicand / (int)(pow(d,nth));
            coefficient = coefficient * d;

        } else {
            d = d + 1;
        }

    }
    if(coefficient == 1){
        NthRoot* root = new NthRoot;
        root->leftSide = new Integer(nth);
        root->rightSide = new Integer(radicand);
        return (Expression*) root;
    }
    if(radicand == 1) {
        return new Integer(coefficient);
    }
    else {
        Expression* multi = new Multiplication;
        Expression* root = new NthRoot;
        root->leftSide = new Integer(nth);
        root->rightSide = new Integer(radicand);
        multi->leftSide = new Integer(coefficient);
        multi->rightSide = root;

        return multi;
    }

}

int NthRoot::getValue() {
    return 0;
}
void NthRoot::setIsSimplified(){
    isSimplified = true;
}

void NthRoot::setType() {
    type = "nthroot";
}
void NthRoot::printExpression(){
    this->leftSide->printExpression();
    cout << "rt ";
    this->rightSide->printExpression();
}
string NthRoot::toString(){
    valueString = this->leftSide->toString() + " rt " + this->rightSide->toString();
    return valueString;
}