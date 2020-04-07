//
// Created by Liam Wood on 4/18/17.
//

#include "Calculator.h"
#include "Expression.h"
#include <iostream>
#include "Multiplication.h"
#include "Addition.h"
#include "Subtraction.h"
#include "Division.h"
#include "NthRoot.h"
#include "Exponentiation.h"
#include "Integer.h"
#include <stack>
#include <cmath>

using namespace std;

void Calculator::run() {

    string input;

    while(isRunning) {

        cout << "> ";
        getline(cin, input);

        // 67 + ( 32 / 8 ) * 3 rt 8

        checkInput(input);
        Expression* e = simplifyExpression(checkForAns(input));
        double d = 0.0;
        if(showFloatingPoint){
            d = calculateFP(checkForAns(input));
            cout << d;
            prevAnsFP.push_back(d);
        }else {
            e->printExpression();
        }
        e->setType();
        if(e->type != "errorexception") {
            prevAns.push_back(e);
        }
        cout << "\n";
    }
}

void Calculator::help() {

    cout << "'quit' -> exits the program" << endl;
    cout << "'memory' -> brings up previous expressions" << endl;
    cout << "'ans' -> recall answer to most recent expression" << endl;
    cout << "'operations' -> lists implemented operations and formats" << endl;
    cout << "'togfp' -> toggles floating point return values" << endl;
    cout << "Remember to use spaces!" << endl;

    run();
}

void Calculator::quit() {
    isRunning = false;
    cout << "Exiting program" << endl;

}

void Calculator::memory() {
    for(int i = 0; i < prevAns.size(); i++) {
        cout << i+1 << ": ";
        prevAns.at(prevAns.size() - i - 1)->printExpression();
        cout << '\n';
    }
    run();
}

void Calculator::operations() {

    cout << "'+' addition: '2 + 2'" << endl;
    cout << "'-' subtraction: '4 - 2'" << endl;
    cout << "'*' multiplication: '2 * 1'" << endl;
    cout << "'/' division: '4 / 2'" << endl;
    cout << "'rt' nth root: '2 rt 4'" << endl;
    cout << "'^' exponentiation: '2 ^ 1'" << endl;

    run();
}

void Calculator::togFP() {
    cout << "Toggled show floating point" << endl;
    if(!showFloatingPoint)
        showFloatingPoint = true;
    else showFloatingPoint = false;
    run();
}

double Calculator::calculateFP(vector<Token*> input) {
    int index = 0;
    stack<Token*> operStack;
    while(index < input.size()){
        Token* t = input.at(index);
        if(t->getType() == t->Number){
            operStack.push(t);
        }
        else {
            if(operStack.size() < t->paramCount){
                cout << "ERROR: Insufficient input" << endl;
                run();
            }
            vector<Token*> operands;
            for(int i = 0; i < t->paramCount; i++){
                Token* temp = operStack.top();
                operands.push_back(temp);
                operStack.pop();
            }
            operStack.emplace(evaluate(t, operands));
        }
        index++;
    }
    if(operStack.size() == 1){
        return operStack.top()->val;
    }
    else {
        cout << "ERROR: Input too many values" << endl;
        run();
    }
    return 0;
}

Token* Calculator::evaluate(Token* oper, vector<Token*> operands) {

    if (oper->getSymbol() == "+") {
        operands.at(0)->val += operands.at(1)->val;
    }
    else if (oper->getSymbol() == "-") {
        operands.at(0)->val = operands.at(1)->val - operands.at(0)->val;
    }
    else if (oper->getSymbol() == "*") {
        operands.at(0)->val *= operands.at(1)->val;
    }
    else if (oper->getSymbol() == "/") {
        operands.at(0)->val = operands.at(1)->val / operands.at(0)->val;
    }
    else if (oper->getSymbol() == "^") {
        operands.at(0)->val = pow(operands.at(1)->val, operands.at(0)->val);
    }
    else if (oper->getSymbol() == "rt") {
        operands.at(0)->val = pow(operands.at(0)->val, (1 / operands.at(1)->val));
    }
    else {
        cout << "ERROR: Unknown operator" << endl;
        run();
    }
    return operands.at(0);
}

void Calculator::checkInput(string str) {
    if (str == "help")
        help();
    if (str == "quit")
        quit();
    if (str == "operations")
        operations();
    if (str == "togfp")
        togFP();
    if(str == "memory"){
        memory();
    }
}

vector<Token*> Calculator::checkForAns(string str) {
    vector<Token*> tokens;
    Token* t;
    if(str.find("ans") == -1){
        tokens = t->theAlgorithm(str);
    }else {
        if(showFloatingPoint){
            int start = str.find("ans");
            int end = start + 3;

            string insert = str.substr(0, start) + "( " + to_string(prevAnsFP.at(prevAnsFP.size() - 1)) + " )" +
                            str.substr(end, str.length() - 1);
            tokens = t->theAlgorithm(insert);
        }else {


            int start = str.find("ans");
            int end = start + 3;

            string insert = str.substr(0, start) + "( " + prevAns.at(prevAns.size() - 1)->toString() + " )" +
                            str.substr(end, str.length() - 1);

            tokens = t->theAlgorithm(insert);
        }
    }
    return tokens;
}

Expression* Calculator::simplifyExpression(vector<Token *> tokenInput) {
    stack<Expression *> expStack;
    Token* t = new Token();
    for (int i = 0; i < tokenInput.size(); i++) {
        if (tokenInput.at((unsigned long) i)->getType() == t->Number) {
            Expression *integer = new Integer(tokenInput.at(i)->getValue());
            expStack.emplace(integer);

        } else {
            if (tokenInput.at(i)->paramCount > expStack.size()) {
                cout << "ERROR: insufficient input" << endl;
                run();
            }
            if (tokenInput.at(i)->getSymbol() == "+") {
                Expression *add = new Addition;
                add->rightSide = expStack.top();
                expStack.pop();
                add->leftSide = expStack.top();
                expStack.pop();
                expStack.emplace(add);
            }
            if (tokenInput.at(i)->getSymbol() == "-") {
                Expression *subtract = new Subtraction;
                subtract->rightSide = expStack.top();
                expStack.pop();
                subtract->leftSide = expStack.top();
                expStack.emplace(subtract);
            }
            if (tokenInput.at(i)->getSymbol() == "*") {
                Expression *multiply = new Multiplication;
                multiply->rightSide = expStack.top();
                expStack.pop();
                multiply->leftSide = expStack.top();
                expStack.pop();
                expStack.emplace(multiply);
            }
            if (tokenInput.at(i)->getSymbol() == "/") {
                Expression *divide = new Division;
                divide->rightSide = expStack.top();
                expStack.pop();
                divide->leftSide = expStack.top();
                expStack.pop();
                expStack.emplace(divide);
            }
            if (tokenInput.at((unsigned long) i)->getSymbol() == "^") {
                Expression *exponent = new Exponentiation;
                exponent->rightSide = expStack.top();
                expStack.pop();
                exponent->leftSide = expStack.top();
                expStack.pop();
                expStack.emplace(exponent);
            }
            if (tokenInput.at(i)->getSymbol() == "rt") {
                Expression *root = new NthRoot;
                root->rightSide = expStack.top();
                expStack.pop();
                root->leftSide = expStack.top();
                expStack.pop();
                expStack.emplace(root);
            }
        }
    }
    return expStack.top()->simplify();
}