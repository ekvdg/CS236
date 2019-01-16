//
//  main.cpp
//  DatalogParser
//
//  Created by Ellie Van De Graaff on 10/1/18.
//  Copyright � 2018 Ellie Van De Graaff. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "Scanner.h"
#include "Token.h"
#include "Predicate.h"
#include "Rule.h"
#include "Interpreter.h"
#include "Checker.h"
#include "Header.h"

int main(int argc, char * argv[]) {
    /*
    std::vector<std::string> inputFiles = {"input1.txt", "input2.txt", "input3.txt", "input4.txt", "input5.txt", "input6.txt", "input7.txt", "input8.txt", "input9.txt", "input10.txt"};
    for(unsigned int i = 0; i < inputFiles.size(); i++){
        Scanner scans;
        scans.main(inputFiles.at(i));
        DatalogProgram tokenPass(scans.returnToken());
        try{
            tokenPass.main();
        }
        catch(Token fail){
            std::cout << "Failure!" << std::endl;
            std::cout <<  "  " << fail << std::endl;
        }
        std::string output;
        Interpreter interpret(tokenPass);
        output = interpret.interpretMain();
        Checker myChecker;
        
        std::vector<std::string> strings =myChecker.inputs();
        if(output == strings.at(i)){
            std::cout << "Success!" << std::endl;
        }
        else{
            std::cout << "Failure"<< std::endl;
            std::cout << strings.at(i) << std::endl << std::endl;
            std::cout << output;
        }
    }*/
    
    
    std::string fileName;
    fileName = argv[1];
    Scanner scans;
    scans.main(fileName);
    DatalogProgram tokenPass(scans.returnToken());
    try {
        tokenPass.main();
    }
    catch (Token fail) {
        std::cout << "Failure!" << std::endl;
        std::cout << "  " << fail << std::endl;
    }
    
    Interpreter interpret(tokenPass);
    interpret.interpretMain();
    
    
    return 0;
}
