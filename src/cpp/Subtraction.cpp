//
// Created by Liam Wood on 4/20/17.
//

#include "Subtraction.h"
#include "Integer.h"
#include "Division.h"
#include "Multiplication.h"
#include "NthRoot.h"
#include <iostream>

Expression* Subtraction:: simplify(){
    if(this->leftSide->getValue() == 0){
        this->leftSide = this->leftSide->simplify();
    }
    if(this->rightSide->getValue() == 0){
        this->rightSide = this->rightSide->simplify();
    }

    this->rightSide->setType();
    this->leftSide->setType();

    if(this->rightSide->type == this->leftSide->type){
        if(this->rightSide->type == "integer"){
            return new Integer(this->leftSide->getValue() - this->rightSide->getValue());
        }
        if(this->rightSide->type == "division")
            return subtractFractions();
        if(this->leftSide->type == "nthroot" && this->leftSide->leftSide->getValue() != this->rightSide->leftSide->getValue()
           || this->leftSide->rightSide->getValue() != this->rightSide->rightSide->getValue()) {
            return this;
        }
        if(this->leftSide->type == "multiplication"){

            this->leftSide->leftSide->setType();
            this->leftSide->rightSide->setType();
            this->rightSide->leftSide->setType();
            this->rightSide->rightSide->setType();

            if(this->leftSide->rightSide->type == "nthroot" && this->rightSide->rightSide->type == "nthroot"
               && this->leftSide->rightSide->leftSide->getValue() == this->rightSide->rightSide->leftSide->getValue()
               && this->leftSide->rightSide->rightSide->getValue() == this->rightSide->rightSide->rightSide->getValue()){
                Expression* multi = new Multiplication;
                Expression* root = new NthRoot;
                root->leftSide = new Integer(this->leftSide->rightSide->leftSide->getValue());
                root->rightSide = new Integer(this->leftSide->rightSide->rightSide->getValue());
                if(this->leftSide->leftSide->getValue() - this->rightSide->leftSide->getValue() == 0)
                    return new Integer(0);
                multi->leftSide = new Integer(this->leftSide->leftSide->getValue() - this->rightSide->leftSide->getValue());
                multi->rightSide = root;

                return multi;
            }
        }
    }
    if(this->leftSide->type == "division" && this->rightSide->type == "integer") {
        Division* div = new Division;
        div->leftSide = new Integer((this->rightSide->getValue() * this->leftSide->rightSide->getValue()) - this->leftSide->leftSide->getValue());
        div->rightSide = new Integer(this->leftSide->rightSide->getValue());
        Expression* e = div->reduce();
        return e;
    }
    if(this->leftSide->type == "integer" && this->rightSide->type == "division") {
        Division* div = new Division;
        div->leftSide = new Integer((this->leftSide->getValue() * this->rightSide->rightSide->getValue()) - this->rightSide->leftSide->getValue());
        div->rightSide = new Integer(this->rightSide->rightSide->getValue());
        Expression* e = div->reduce();
        return e;
    }
    return 0;
}

Expression* Subtraction::subtractFractions() {

    if(this->leftSide->rightSide->getValue() == this->rightSide->rightSide->getValue()) {
        int numerator = this->leftSide->leftSide->getValue() - this->rightSide->leftSide->getValue();
        int denominator = this->leftSide->rightSide->getValue();
        if(numerator == 0){
            return new Integer(0);
        }
        Division* div = new Division;

        div->leftSide = new Integer(numerator);
        div->rightSide = new Integer(denominator);

        Expression* e = div->reduce();

        return e;
    }
    else {

        int numerator = (this->leftSide->leftSide->getValue() * this->rightSide->rightSide->getValue()) - (this->leftSide->rightSide->getValue() * this->rightSide->leftSide->getValue());
        int denominator = this->leftSide->rightSide->getValue() * this->rightSide->rightSide->getValue();

        if(numerator == 0){
            return new Integer(0);
        }

        Division* div = new Division;

        div->leftSide = new Integer(numerator);
        div->rightSide = new Integer(denominator);

        Expression* e = div->reduce();
        return e;
    }
}

int Subtraction::getValue() {
    return 0;
}

void Subtraction::setIsSimplified(){
    isSimplified = true;
}

void Subtraction::setType() {
    type = "subtraction";
}
void Subtraction::printExpression(){
    this->leftSide->printExpression();
    cout << "- ";
    this->rightSide->printExpression();
}
string Subtraction::toString(){
    valueString = this->leftSide->toString() + " - " + this->rightSide->toString();
    return valueString;
}