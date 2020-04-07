//
// Created by Liam Wood on 4/20/17.
//

#include "Multiplication.h"
#include "Integer.h"
#include <iostream>
#include "Division.h"
#include "NthRoot.h"
#include "Calculator.h"
#include "ErrorException.h"

Expression* Multiplication::simplify() {

    this->rightSide->setType();
    this->leftSide->setType();

    if(this->rightSide->type == "nthroot" && this->leftSide->type == "nthroot" && this->leftSide->leftSide->getValue() != this->rightSide->leftSide->getValue()){
        return new ErrorException("ERROR: Cannot compute irrational exponents");
    }
    if(this->rightSide->type == "nthroot" && this->leftSide->type == "nthroot" && this->leftSide->leftSide->getValue() == this->rightSide->leftSide->getValue()){
        NthRoot* root = new NthRoot;
        root->leftSide = new Integer(this->leftSide->leftSide->getValue());
        root->rightSide = new Integer(this->leftSide->rightSide->getValue() * this->rightSide->rightSide->getValue());

        return root->simplify();
    }

    if(this->leftSide->getValue() == 0){
        this->leftSide = this->leftSide->simplify();
    }
    if(this->rightSide->getValue() == 0){
        this->rightSide = this->rightSide->simplify();
    }

    this->rightSide->setType();
    this->leftSide->setType();

    if(this->rightSide->type == this->leftSide->type) {
        if (this->rightSide->type == "integer")
            return new Integer(this->leftSide->getValue() * this->rightSide->getValue());
        if (this->rightSide->type == "division") {
            return multiplyFractions();
        }

    }
    if(this->leftSide->type == "integer" && this->rightSide->type == "multiplication"){
        this->rightSide->rightSide->setType();
        if(this->rightSide->rightSide->type == "nthroot"){
            Expression* multi = new Multiplication;
            Expression* root = new NthRoot;

            root->leftSide = new Integer(this->rightSide->rightSide->leftSide->getValue());
            root->rightSide = new Integer(this->rightSide->rightSide->rightSide->getValue());
            multi->leftSide = new Integer(this->leftSide->getValue() * this->rightSide->leftSide->getValue());
            multi->rightSide = root;
            return multi;
        }
    }
    if(this->rightSide->type == "integer" && this->leftSide->type == "multiplication"){
        this->leftSide->rightSide->setType();
        if(this->leftSide->rightSide->type == "nthroot"){
            Expression* multi = new Multiplication;
            Expression* root = new NthRoot;
            root->leftSide = new Integer(this->leftSide->rightSide->leftSide->getValue());
            root->rightSide = new Integer(this->leftSide->rightSide->rightSide->getValue());
            multi->leftSide = new Integer(this->rightSide->getValue() * this->leftSide->leftSide->getValue());
            multi->rightSide = root;
            return multi;
        }
    }
    if(this->leftSide->type == "division" && this->rightSide->type == "integer") {
        Division* div = new Division;
        div->leftSide = new Integer(this->leftSide->leftSide->getValue() * this->rightSide->getValue());
        div->rightSide = new Integer(this->leftSide->rightSide->getValue());
        Expression* e = div->reduce();
        return e;
    }
    if(this->leftSide->type == "integer" && this->rightSide->type == "division"){
        Division* div = new Division;
        div->leftSide = new Integer(this->rightSide->leftSide->getValue() * this->leftSide->getValue());
        div->rightSide = new Integer(this->rightSide->rightSide->getValue());
        Expression* e = div->reduce();
        return e;
    }
    if(this->leftSide->type == "integer" && this->rightSide->type == "nthroot"){
        return this;
    }
    if(this->leftSide->type == "nthroot" && this->rightSide->type == "integer"){
        Expression* multi = new Multiplication;
        multi->leftSide = this->rightSide;
        multi->rightSide = this->leftSide;
        return multi;
    }
    return 0;
}

Expression* Multiplication::multiplyFractions() {

    Division* div = new Division;

    div->leftSide = new Integer(this->leftSide->leftSide->getValue() * this->rightSide->leftSide->getValue());

    div->rightSide = new Integer(this->leftSide->rightSide->getValue() * this->rightSide->rightSide->getValue());

    Expression* e = div->reduce();

    return e;
}

int Multiplication::getValue() {
    return 0;
}
void Multiplication::setIsSimplified(){
    isSimplified = true;
}
void Multiplication::setType() {
    type = "multiplication";
}
void Multiplication::printExpression(){
    this->leftSide->printExpression();
    cout << "* ";
    this->rightSide->printExpression();
}
string Multiplication::toString(){
    valueString = this->leftSide->toString() + " * " + this->rightSide->toString();
    return valueString;
}