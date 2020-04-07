//
// Created by Liam Wood on 3/3/17.
//

#include "Token.h"
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>

using namespace std;
Token::Token() {}

//Token Methods
vector<string> Token:: eliminateWhiteSpace(string str) {
        vector<string> v;
        istringstream iss(str);
        for(string temp; iss >> temp;)
            v.push_back(temp);
        return v;
    }

Token* Token::stringToToken(string inputString) {
    Token* t = new Token();
    double num;

        if (istringstream(inputString) >> num) {
            t->type = Number;
            t->val = num;
        } else if (inputString == "(")
            t->type = LeftParenthesis;
        else if (inputString == ")")
            t->type = RightParenthesis;
        else if (inputString == "+") {
            t->type = Operator;
            t->symbol = '+';
            t->assoc = Left;
            t->precedence = 1;
            t->paramCount = 2;
        } else if (inputString == "-") {
            t->type = Operator;
            t->symbol = '-';
            t->assoc = Left;
            t->precedence = 1;
            t->paramCount = 2;
        } else if (inputString == "*") {
            t->type = Operator;
            t->symbol = '*';
            t->assoc = Left;
            t->precedence = 2;
            t->paramCount = 2;
        } else if (inputString == "/") {
            t->type = Operator;
            t->symbol = '/';
            t->assoc = Left;
            t->precedence = 2;
            t->paramCount = 2;
        } else if (inputString == "rt") {
            t->type = Operator;
            t->symbol = "rt";
            t->assoc = Right;
            t->precedence = 3;
            t->paramCount = 2;
        } else if (inputString == "^") {
            t->type = Operator;
            t->symbol = "^";
            t->assoc = Left;
            t->precedence = 3;
            t->paramCount = 2;
        } else if (inputString == "ans") {
            t->type = Expression;
            t->symbol = "ans";

        }

        return t;

}

vector<Token*> Token::Tokenize(string str) {
    vector<string> v = eliminateWhiteSpace(str);
    vector<Token*> tokens;
    tokens.resize(v.size());
    for(int i = 0; i < tokens.size(); i++){
        tokens.at(i) = stringToToken(v.at(i));
    }
    return tokens;
}

vector<Token*> Token::theAlgorithm(string str) {
    vector<Token*> tokens = Tokenize(str);
    queue<Token*> outputQueue;
    stack<Token*> operatorStack;
    for(int i = 0; i < tokens.size(); i++){
        Token* t = tokens.at(i);
        if(t->getType() == Number)
            outputQueue.emplace(t);
        else if(t->getType() == Operator){
            while(operatorStack.size() != 0) {
                Token *o2 = operatorStack.top();
                if(o2->getType() != Operator)
                    break;
                else if((t->getAssoc() == Left) && ((t->getPrecedence() == o2->getPrecedence()) ||
                        (t->getPrecedence() < o2->getPrecedence()))){
                    outputQueue.emplace(operatorStack.top());
                    operatorStack.pop();
                }
                else break;
            }
            operatorStack.emplace(t);
        }
        else if(t->getType() == LeftParenthesis){
            operatorStack.emplace(t);
        }
        else if(t->getType() == RightParenthesis){
            while(operatorStack.top()->getType() != LeftParenthesis) {
                outputQueue.emplace(operatorStack.top());
                operatorStack.pop();

                if(operatorStack.size() == 0){
                    throw "Mismatched Parentheses";
                }
            }
            operatorStack.pop();
        }
    }
    while(operatorStack.size() != 0){
        if((operatorStack.top()->getType() == LeftParenthesis) || (operatorStack.top()->getType() == RightParenthesis))
            throw "Mismatched Parentheses";
        outputQueue.emplace(operatorStack.top());
        operatorStack.pop();
    }

    vector<Token*> v;
    v.resize(outputQueue.size());
    int index = 0;
    while(outputQueue.size() != 0) {
        v.at(index) = outputQueue.front();
        outputQueue.pop();
        index++;
    }

    return v;
}

//Getter methods
string Token::getSymbol() {
    return this->symbol;
}
Token::TokenType Token::getType() {
    return this->type;
}
double Token::getValue() {
    return this->val;
}
int Token::getPrecedence() {
    return this->precedence;
}
Token::Associativity Token::getAssoc() {
    return this->assoc;
}
//setter method
void Token::setValues(string symbol, Associativity assoc, int prec, int param) {
    this->symbol = symbol;
    this->assoc = assoc;
    this->precedence = prec;
    this->paramCount = param;
}