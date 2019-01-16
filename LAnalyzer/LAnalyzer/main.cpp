//
//  main.cpp
//  LAnalyzer
//
//  Created by Ellie Van De Graaff on 9/19/18.
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
    std::string fileName;
    fileName = argv[1];
    Scanner scans;
    scans.main(fileName);
    
    return 0;
}
