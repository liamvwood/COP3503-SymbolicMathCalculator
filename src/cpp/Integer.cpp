//
// Created by Liam Wood on 4/20/17.
//

#include "Integer.h"
#include <iostream>
using namespace std;
Integer::Integer(int val) {
    value = val;
}

Expression* Integer::simplify() {
    Expression* e = new Integer(value);
    e->setType();
    return e;
}

int Integer::getValue() {
    return value;
}

void Integer::setIsSimplified(){
    isSimplified = true;
}

void Integer::setType() {
    type = "integer";
}
void Integer::printExpression() {
    cout << this->getValue() << " ";
}
string Integer::toString(){
    valueString = to_string(this->getValue());
    return valueString;
}