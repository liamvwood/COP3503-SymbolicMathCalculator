//
// Created by Liam Wood on 4/24/17.
//

#include "ErrorException.h"
#include <iostream>

ErrorException::ErrorException(string str) {
    exception = str;
}
void ErrorException::setType(){
    type = "errorexception";
}
void ErrorException::setIsSimplified(){

}
Expression* ErrorException::simplify(){
    return 0;
}
void ErrorException::printExpression(){
    cout << exception;
}
int ErrorException::getValue(){
    return 0;
}
string ErrorException::toString(){
return nullptr;
}