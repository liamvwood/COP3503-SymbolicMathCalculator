//
// Created by Liam Wood on 4/20/17.
//

#include "Division.h"
#include "Integer.h"
#include "Calculator.h"
#include "ErrorException.h"
#include <iostream>

Expression* Division::simplify() {

    if(this->leftSide->getValue() == 0){
        this->leftSide = this->leftSide->simplify();
    }
    if(this->rightSide->getValue() == 0){
        this->rightSide = this->rightSide->simplify();
    }

    this->rightSide->setType();
    this->leftSide->setType();


    if(this->rightSide->type == "integer" && this->leftSide->type == "integer"){
        int numerator = this->leftSide->getValue();
        int denominator = this->rightSide->getValue();
        if(denominator == 0){
            return new ErrorException("ERROR: Cannot divide by zero");

        }
        if(numerator % denominator == 0){
            return new Integer(numerator / denominator);
        }

    }

    if(this->rightSide->type == "division" && this->leftSide->type == "division"){

        Division* div = new Division;

        int numerator = this->leftSide->leftSide->getValue() * this->rightSide->rightSide->getValue();
        int denominator = this->leftSide->rightSide->getValue() * this->rightSide->leftSide->getValue();

        div->leftSide = new Integer(numerator);
        div->rightSide = new Integer(denominator);

        Expression* e = div->reduce();
        return e;
    }

    if(this->leftSide->type == "integer" && this->rightSide->type == "division"){

        Division* div = new Division;

        int numerator = this->leftSide->getValue() * this->rightSide->rightSide->getValue();

        int denominator = this->rightSide->leftSide->getValue();

        div->leftSide = new Integer(numerator);

        div->rightSide = new Integer(denominator);

        Expression* e = div->reduce();

        return e;
    }
    if(this->leftSide->type == "division" && this->rightSide->type == "integer"){
        Division* div = new Division;

        int numerator = this->leftSide->leftSide->getValue();
        int denominator = this->leftSide->rightSide->getValue() * this->rightSide->getValue();

        div->leftSide = new Integer(numerator);
        div->rightSide = new Integer(denominator);

        Expression* e = div->reduce();
        return e;
    }

    return reduce();

}

int Division::getValue(){
    return 0;
}

Expression* Division::reduce() {

    vector<int> denomFactors, numerFactors, comFactors;

    numerator = this->leftSide->getValue();
    denominator = this->rightSide->getValue();

    if(denominator < 0 && numerator < 0){
        isNegative = false;
        numerator *= -1;
        denominator *= -1;
    }
    if(numerator < 0){
        isNegative = true;
        numerator *= -1;
    }
    if(denominator < 0){
        isNegative = true;
        denominator *= -1;
    }

    for(int i = 1; i <= numerator; i++){
        if(numerator % i == 0){
            numerFactors.push_back(i);
        }
    }

    for(int i = 1; i <= denominator; i++){
        if(denominator % i == 0) {
            denomFactors.push_back(i);
        }
    }

    for(int i = 0; i < denomFactors.size(); i++){
        for(int j = 0; j < numerFactors.size(); j++){
            if(denomFactors.at(i) == numerFactors.at(j)) {
                comFactors.push_back((int &&) denomFactors.at(i));
            }
        }

    }

    int greatComFactor = 0;

    for(int i = 0; i < comFactors.size(); i++){

        if(comFactors.at(i) > greatComFactor) {
            greatComFactor = comFactors.at(i);
        }
    }

    numerator = numerator / greatComFactor;
    denominator = denominator / greatComFactor;
    if(denominator == 1){
        return new Integer(numerator);
    }
    Expression* divide = new Division;
    if(!isNegative) {
        divide->leftSide = new Integer(numerator);
        divide->rightSide = new Integer(denominator);
    }
    else {
        divide->leftSide = new Integer(numerator * -1);
        divide->rightSide = new Integer(denominator);
    }
    return divide;

}

void Division::setIsSimplified(){
    isSimplified = true;
}

void Division::setType() {
    type = "division";
}
void Division::printExpression(){
    this->leftSide->printExpression();
    cout << "/ ";
    this->rightSide->printExpression();
}
string Division::toString(){
    valueString = this->leftSide->toString() + " / " + this->rightSide->toString();
    return valueString;
}