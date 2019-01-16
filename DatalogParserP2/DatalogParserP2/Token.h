//
//  Token.h
//  LAnalyzer
//
//  Created by Ellie Van De Graaff on 9/19/18.
//  Copyright © 2018 Ellie Van De Graaff. All rights reserved.
//

#ifndef Token_h
#define Token_h
#include <string>
#include <sstream>

class Token{
private:
    int line;
    std::string tokenStr;
    std::string tokenType;
public:
    Token(){
        line = 1;
        tokenStr = "";
        tokenType = "COMMA";
    }
    void setLine(int newLine){
        line = newLine;
    }
    void setString(std::string newStr){
        tokenStr = newStr;
    }
    std::string getString(){
        return tokenStr;
    }
    void setTokenType(std::string newTokenType){
        tokenType = newTokenType;
    }
    std::string getTokenType(){
        return tokenType;
    }
    
    std::string toString() const {
        std::ostringstream out;
        out << "("  << tokenType << "," << "\"" << tokenStr << "\"" << "," << line << ")" << std::endl;
        std::string outString;
        outString = out.str();
        return outString;
    }
    
    friend std::ostream& operator<< (std::ostream& os, const Token& tOutput)
    {
        os << tOutput.toString();
        return os;
    }
};


#endif /* Token_h */
