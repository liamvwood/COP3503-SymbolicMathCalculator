//
// Created by Liam Wood on 4/20/17.
//

#include "Exponentiation.h"
#include "Integer.h"
#include <cmath>
#include "Division.h"
#include <iostream>
#include "NthRoot.h"

Expression* Exponentiation::simplify() {
    if(this->leftSide->getValue() == 0){
        this->leftSide = this->leftSide->simplify();
    }
    if(this->rightSide->getValue() == 0){
        this->rightSide = this->rightSide->simplify();
    }
    this->leftSide->setType();
    this->rightSide->setType();

    if(this->leftSide->type == "integer" && this->rightSide->type == "integer" && this->rightSide->getValue() > 0)
        return new Integer(pow(this->leftSide->getValue(), this->rightSide->getValue()));
    if(this->leftSide->type == "integer" && this->rightSide->type == "integer" && this->rightSide->getValue() < 0){
        Division* div = new Division;
        div->leftSide = new Integer(1);
        div->rightSide = new Integer(pow(this->leftSide->getValue(), this->rightSide->getValue() * -1));
        Expression* e = div->reduce();
        return e;
    }
    if(this->leftSide->type == "division" && this->rightSide->getValue() > 0){

        Division* div = new Division;

        div->leftSide = new Integer(pow(this->leftSide->leftSide->getValue(), this->rightSide->getValue()));
        div->rightSide = new Integer(pow(this->leftSide->rightSide->getValue(), this->rightSide->getValue()));

        Expression* e = div->reduce();
        return e;

    }

    if(this->leftSide->type == "division" && this->rightSide->getValue() < 0){

        Division* div = new Division;

        div->rightSide = new Integer(pow(this->leftSide->leftSide->getValue(), this->rightSide->getValue() * -1));
        div->leftSide = new Integer(pow(this->leftSide->rightSide->getValue(), this->rightSide->getValue() * -1));

        Expression* e = div->reduce();
        return e;

    }

    if(this->rightSide->type == "division") {

        NthRoot* root = new NthRoot;
        Expression* exponent = new Exponentiation;

        exponent->leftSide = this->leftSide;
        exponent->rightSide = this->rightSide->leftSide;

        root->leftSide = this->rightSide->rightSide;
        root->rightSide = exponent;

        root->simplify();

        return root;
    }

    return 0;
}

int Exponentiation::getValue() {
    return 0;
}
void Exponentiation::setIsSimplified(){
    isSimplified = true;
}
void Exponentiation::setType() {
    type = "exponentiation";
}
void Exponentiation::printExpression() {
    this->leftSide->printExpression();
    cout << "^ ";
    this->rightSide->printExpression();
}
string Exponentiation::toString(){
    valueString = this->leftSide->toString() + " ^ " + this->rightSide->toString();
    return valueString;
}