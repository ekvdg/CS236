//
//  main.cpp
//  Lexical Analyzer
//
//  Created by Ellie Van De Graaff on 9/18/18.
//  Copyright © 2018 Ellie Van De Graaff. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "Token.h"


/*Token isComma(std::string input){
    return 1;
}
Token isPeriod(std::string input){
    return 1;
}
Token isQMark(std::string input){
    return 1;
}
Token isLeftParen(std::string input){
    return 1;
}
Token isRightParen(std::string input){
    return 1;
}
Token isColon(std::string input){
    return 1;
}
Token isColonDash(std::string input){
    return 1;
}
Token isMultiply(std::string input){
    return 1;
}
Token isAdd(std::string input){
    return 1;
}
Token isSchemes(std::string input){
    return 1;
}
Token isFacts(std::string input){
    return 1;
}
Token isRules(std::string input){
    return 1;
}
Token isQueries(std::string input){
    return 1;
}
Token isID(std::string input){
    return 1;
}
Token isString(std::string input){
    return 1;
}
Token isComment(std::string input){
    return 1;
}
Token isWhitespace(std::string input){
    return 1;
}
Token isUndefined(std::string input){
    return 1;
}
Token isEOF(std::string input){
    return 1;
}
 */


int main(int argc, char * argv[]) {
    if (argc < 3) {
        std::cerr << "Please provide name of input and output files";
        return 1;
    }
    std::cout << "Input file: " << argv[1] << std::endl;
    std::ifstream in(argv[1]);
    if (!in) {
        std::cerr << "Unable to open " << argv[1] << " for input";
        return 1;
    }
    std::cout << "Output file: " << argv[2] << std::endl;
    std::ofstream out(argv[2]);
    if (!out) {
        in.close();
        std::cerr << "Unable to open " << argv[2] << " for output";
    }
     
    
    
    
    
    
    return 0;
}
