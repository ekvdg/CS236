//
//  Scanner.h
//  LAnalyzer
//
//  Created by Ellie Van De Graaff on 9/20/18.
//  Copyright � 2018 Ellie Van De Graaff. All rights reserved.
//

#ifndef Scanner_h
#define Scanner_h
#include <string>
#include <vector>
#include <fstream>
#include "Token.h"
//#include "DatalogProgram.h"
class Scanner {
private:
    std::vector<Token> storedTokens;
    std::string file;
    int lineNum = 1;
    std::ifstream in;
    
public:
    std::vector<Token> returnToken();
    void checker(char input);
    bool openFile(std::string file);
    int main(std::string fileName);
    bool isSymbol(char input);
    bool otherSymbol(char input);
    bool isComma(char input);
    bool isPeriod(char input);
    bool isQMark(char input);
    bool isLeftParen(char input);
    bool isRightParen(char input);
    bool isColon(char input);
    bool isColonDash(char input);
    bool isMultiply(char input);
    bool isAdd(char input);
    bool isKeyword(std::string input);
    bool isID(char input);
    bool isString(char input);
    bool isLineComment(char input);
    bool isMultiLineComment(char input);
    bool isWhitespace(char input);
    bool isUndefined(char input);
    bool isUndefined(std::string input, int lineNum);
    void isEOF();
    
};


#endif
