//
// Created by Liam Wood on 3/3/17.
//

#ifndef CP3503PROJECT_TOKEN_H
#define CP3503PROJECT_TOKEN_H
#include <string>
#include <vector>
using namespace std;
class Token {
public:
    // constructor
    Token();

    enum TokenType {Nothing, Number, Operator, LeftParenthesis, RightParenthesis,Expression};
    enum Associativity {Left, Right};

    // variables
    double val = 0.0;
    string symbol = " ";
    Associativity assoc  = Left;
    int precedence = 0;
    TokenType type = Nothing;
    int paramCount = 0;
    //Token Methods
    vector<Token*> Tokenize(string str);
    vector<Token*> theAlgorithm(string);
    Token* stringToToken(string str);
    vector<string> eliminateWhiteSpace(string str);

    //getter methods
    TokenType getType();
    string getSymbol();
    double getValue();
    int getPrecedence();
    Associativity getAssoc();


    //setter methods
    void setValues(string symbol, Associativity assoc, int prec, int param);


};


#endif //CP3503PROJECT_TOKEN_H
