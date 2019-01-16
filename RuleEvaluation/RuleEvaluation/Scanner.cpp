//
//  Scanner.cpp
//  LAnalyzer
//
//  Created by Ellie Van De Graaff on 9/20/18.
//  Copyright � 2018 Ellie Van De Graaff. All rights reserved.
//

#include <stdio.h>
#include <string>
#include "Scanner.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cctype>



bool Scanner::isComma(char input) {
    Token returnVal;
    if (input == ',') {
        returnVal.setString(",");
        returnVal.setTokenType("COMMA");
        returnVal.setLine(lineNum);
        storedTokens.push_back(returnVal);
        return true;
    }
    return false;
}

bool Scanner::isPeriod(char input) {
    Token returnVal;
    if (input == '.') {
        returnVal.setString(".");
        returnVal.setTokenType("PERIOD");
        returnVal.setLine(lineNum);
        storedTokens.push_back(returnVal);
        return true;
    }
    return false;
}

bool Scanner::isQMark(char input) {
    Token returnVal;
    if (input == '?') {
        returnVal.setString("?");
        returnVal.setTokenType("Q_MARK");
        returnVal.setLine(lineNum);
        storedTokens.push_back(returnVal);
        return true;
    }
    return false;
}

bool Scanner::isLeftParen(char input) {
    Token returnVal;
    if (input == '(') {
        returnVal.setString("(");
        returnVal.setTokenType("LEFT_PAREN");
        returnVal.setLine(lineNum);
        storedTokens.push_back(returnVal);
        return true;
    }
    return false;
}
bool Scanner::isRightParen(char input) {
    Token returnVal;
    if (input == ')') {
        returnVal.setString(")");
        returnVal.setTokenType("RIGHT_PAREN");
        returnVal.setLine(lineNum);
        storedTokens.push_back(returnVal);
        return true;
    }
    return false;
}

bool Scanner::isColon(char input) {
    Token returnVal;
    if (input == ':') {
        returnVal.setString(":");
        returnVal.setTokenType("COLON");
        returnVal.setLine(lineNum);
        storedTokens.push_back(returnVal);
        return true;
    }
    return false;
}

bool Scanner::isColonDash(char input) {
    Token returnVal;
    char newInput;
    std::string finalString;
    if (input == ':' && in.peek() == '-') {
        finalString.push_back(input);
        in.get(newInput);
        finalString.push_back(newInput);
        returnVal.setString(finalString);
        returnVal.setTokenType("COLON_DASH");
        returnVal.setLine(lineNum);
        storedTokens.push_back(returnVal);
        return true;
    }
    return false;
}


bool Scanner::isMultiply(char input) {
    Token returnVal;
    if (input == '*') {
        returnVal.setString("*");
        returnVal.setTokenType("MULTIPLY");
        returnVal.setLine(lineNum);
        storedTokens.push_back(returnVal);
        return true;
    }
    return false;
    
}

bool Scanner::isAdd(char input) {
    Token returnVal;
    if (input == '+') {
        returnVal.setString("+");
        returnVal.setTokenType("ADD");
        returnVal.setLine(lineNum);
        storedTokens.push_back(returnVal);
        return true;
    }
    return false;
}

bool Scanner::isKeyword(std::string input) {
    Token returnVal;
    if (input == "Schemes") {
        returnVal.setString(input);
        returnVal.setTokenType("SCHEMES");
        returnVal.setLine(lineNum);
        storedTokens.push_back(returnVal);
        return true;
    }
    else if (input == "Rules") {
        returnVal.setString(input);
        returnVal.setTokenType("RULES");
        returnVal.setLine(lineNum);
        storedTokens.push_back(returnVal);
        return true;
    }
    else if (input == "Facts") {
        returnVal.setString(input);
        returnVal.setTokenType("FACTS");
        returnVal.setLine(lineNum);
        storedTokens.push_back(returnVal);
        return true;
    }
    else if (input == "Queries") {
        returnVal.setString(input);
        returnVal.setTokenType("QUERIES");
        returnVal.setLine(lineNum);
        storedTokens.push_back(returnVal);
        return true;
    }
    return false;
}

bool Scanner::isID(char input) {
    Token returnVal;
    char newInput;
    std::string finalString;
    if (isalpha(input)) {
        finalString.push_back(input);
        while (in.get(newInput)) {
            if ((isdigit(newInput) || isalpha(newInput))) {
                finalString.push_back(newInput);
            }
            else {
                break;
            }
        }
        if (!isKeyword(finalString)) {
            returnVal.setString(finalString);
            returnVal.setTokenType("ID");
            returnVal.setLine(lineNum);
            storedTokens.push_back(returnVal);
            //return true;
        }
        /*if(newInput == '\n'){
         lineNum++;
         }
         */
        checker(newInput);
        return true;
        
    }
    
    return false;
}


bool Scanner::isString(char input) {
    Token returnVal;
    char newInput;
    std::string finalString;
    int finalLineNum = lineNum;
    if (input == '\'') {
        finalString.push_back(input);
        while (in.get(newInput)) {
            if (newInput == '\n') {
                finalString.push_back(newInput);
                lineNum++;
            }
            else if (newInput == '\'' && in.peek() == '\'') {
                finalString.push_back(newInput);
                in.get(newInput);
                finalString.push_back(newInput);
            }
            else if (newInput == '\'') {
                finalString.push_back(newInput);
                returnVal.setString(finalString);
                returnVal.setTokenType("STRING");
                returnVal.setLine(finalLineNum);
                storedTokens.push_back(returnVal);
                return true;
            }
            else {
                finalString.push_back(newInput);
            }
        }
        isUndefined(finalString, finalLineNum);
        return true;
    }
    return false;
}

bool Scanner::isLineComment(char input) {
    Token returnVal;
    char newInput;
    std::string finalString;
    if (input == '#') {
        finalString.push_back(input);
        while (in.get(newInput)) {
            if (newInput == '\n') {
                returnVal.setString(finalString);
                returnVal.setTokenType("COMMENT");
                returnVal.setLine(lineNum);
                //storedTokens.push_back(returnVal);
                lineNum++;
                return true;
            }
            else {
                finalString.push_back(newInput);
            }
        }
    }
    return false;
}

bool Scanner::isMultiLineComment(char input) {
    Token returnVal;
    char newInput;
    int savedLineNum = lineNum;
    std::string finalString;
    if (input == '#' && in.peek() == '|') {
        finalString.push_back(input);
        in.get(newInput);
        finalString.push_back(newInput);
        while (in.get(newInput)) {
            if (newInput == '\n') {
                finalString.push_back(newInput);
                lineNum++;
            }
            else if (newInput == '|' && in.peek() == '#') {
                finalString.push_back(newInput);
                in.get(newInput);
                finalString.push_back(newInput);
                returnVal.setString(finalString);
                returnVal.setTokenType("COMMENT");
                returnVal.setLine(savedLineNum);
                //storedTokens.push_back(returnVal);
                return true;
            }
            else {
                finalString.push_back(newInput);
            }
        }
        isUndefined(finalString, savedLineNum);
        return true;
    }
    return false;
}

bool Scanner::isWhitespace(char input) {
    if (iswspace(input)) {
        return true;
    }
    else {
        return false;
    }
}

bool Scanner::isUndefined(char input) {
    Token returnVal;
    std::string strVal;
    strVal.push_back(input);
    returnVal.setString(strVal);
    returnVal.setTokenType("UNDEFINED");
    returnVal.setLine(lineNum);
    storedTokens.push_back(returnVal);
    return true;
}

bool Scanner::isUndefined(std::string input, int newLineNum) {
    Token returnVal;
    returnVal.setString(input);
    returnVal.setTokenType("UNDEFINED");
    returnVal.setLine(newLineNum);
    storedTokens.push_back(returnVal);
    return true;
}


void Scanner::isEOF() {
    Token returnVal;
    returnVal.setString("");
    returnVal.setTokenType("EOF");
    returnVal.setLine(lineNum);
    storedTokens.push_back(returnVal);
}

bool Scanner::openFile(std::string file) {
    in.open(file);
    if (!in) {
        std::cerr << "Unable to open " << file << " for input" << std::endl;
        return false;
    }
    else {
        return true;
    }
}
bool Scanner::otherSymbol(char input) {
    if (isColonDash(input) || isColon(input))
        return true;
    if (isMultiply(input) || isAdd(input))
        return true;
    return false;
}

bool Scanner::isSymbol(char input) {
    if (isComma(input) || isPeriod(input))
        return true;
    if (isQMark(input) || isLeftParen(input) || isRightParen(input))
        return true;
    if (otherSymbol(input))
        return true;
    return false;
}

void Scanner::checker(char input) {
    if (input == '\n')
        lineNum++;
    else if (isSymbol(input));
    else if (isMultiLineComment(input));
    else if (isLineComment(input));
    else if (isString(input));
    else if (isID(input));
    else if (isWhitespace(input));
    else
        isUndefined(input);
}

std::vector<Token> Scanner::returnToken() {
    return storedTokens;
}

int Scanner::main(std::string fileName) {
    if (!openFile(fileName)) {
        return 1;
    }
    
    Token returned;
    char input;
    while (in.get(input)) {
        checker(input);
    }
    isEOF();
    
    in.close();
    return 0;
}


