//
//  main.cpp
//  DatalogParser
//
//  Created by Ellie Van De Graaff on 10/1/18.
//  Copyright © 2018 Ellie Van De Graaff. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "Scanner.h"
#include "Token.h"

int main(int argc, char * argv[]) {
    
    /*std::vector<std::string> inputFiles = {"input1.txt", "input2.txt", "input3.txt", "input4.txt", "input5.txt", "input6.txt", "input7.txt", "input8.txt", "input9.txt", "input10.txt"};
    for(std::string fileName : inputFiles){
        Scanner scans;
        scans.main(fileName);
        DatalogProgram tokenPass(scans.returnToken());
        try{
            tokenPass.main();
        }
        catch(Token fail){
            std::cout << "Failure!" << std::endl;
            std::cout <<  "  " << fail << std::endl;
        }
    }
     */
    Scanner scans;
    scans.main("input5.txt");
    DatalogProgram tokenPass(scans.returnToken());
    try{
        tokenPass.main();
    }
    catch(Token fail){
        std::cout << "Failure!" << std::endl;
        std::cout <<  "  " << fail << std::endl;
    }
    return 0;
}
