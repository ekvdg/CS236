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
    
    /*Relation myRel1;
    Parameter entry1("cat");
    Parameter entry2("dog");
    Parameter entry3("fish");
    std::vector<Parameter> fillHeader1 = {entry1, entry2, entry3};
    Header myHeader(fillHeader1);
    
    Parameter tuple1entry1("1");
    Parameter tuple1entry2("2");
    Parameter tuple1entry3("5");
    std::vector<Parameter> tuple1 = {tuple1entry1, tuple1entry2, tuple1entry3};
    Tuple first(tuple1);
    
    Parameter tuple2entry1("1");
    Parameter tuple2entry2("4");
    Parameter tuple2entry3("1");
    std::vector<Parameter> tuple2 = {tuple2entry1, tuple2entry2, tuple2entry3};
    Tuple second(tuple2);
    
    myRel1.setName("alpha");
    myRel1.setHeader(myHeader);
    myRel1.addTuple(first);
    myRel1.addTuple(second);
    
    
    Relation myRel2;
    Parameter rel2entry1("cat");
    Parameter rel2entry2("fish");
    Parameter rel2entry3("bunny");
    std::vector<Parameter> rel2fillHeader1 = {rel2entry1, rel2entry2, rel2entry3};
    Header rel2myHeader(rel2fillHeader1);
    
    Parameter rel2tuple1entry1("1");
    Parameter rel2tuple1entry2("5");
    Parameter rel2tuple1entry3("8");
    std::vector<Parameter> rel2tuple1 = {rel2tuple1entry1, rel2tuple1entry2, rel2tuple1entry3};
    Tuple rel2first(rel2tuple1);
    
    Parameter rel2tuple2entry1("1");
    Parameter rel2tuple2entry2("5");
    Parameter rel2tuple2entry3("2");
    std::vector<Parameter> rel2tuple2 = {rel2tuple2entry1, rel2tuple2entry2, rel2tuple2entry3};
    Tuple rel2second(rel2tuple2);
    
    myRel2.setName("beta");
    myRel2.setHeader(rel2myHeader);
    myRel2.addTuple(rel2first);
    myRel2.addTuple(rel2second);
    
    Relation joint = myRel1.join(myRel2);
    std::cout << "Joined Relation:" << std::endl;
    std::cout << joint.toString();
    
    Relation rel3;
    Parameter rel3e1("cat");
    Parameter rel3e2("dog");
    Parameter rel3e3("fish");
    Parameter rel3e4("bunny");
    std::vector<Parameter> rel3ffillHeader = {rel3e1, rel3e2, rel3e3, rel3e4};
    Header rel3myHeader(rel3ffillHeader);
    Parameter rel3t1e1("2");
    Parameter rel3t1e2("4");
    Parameter rel3t1e3("6");
    Parameter rel3t1e4("8");
    std::vector<Parameter> rel3tuple = {rel3t1e1, rel3t1e2, rel3t1e3, rel3t1e4};
    Tuple rel3onlytuple(rel3tuple);
    rel3.setName("zeta");
    rel3.setHeader(rel3myHeader);
    rel3.addTuple(rel3onlytuple);
    
    Relation unioned = rel3.unionize(joint);
    
    std::cout << "Unioned Relation:" << std::endl;
    std::cout << unioned.toString();
    
    Database myData;
    myData["only"] = unioned;
    std::cout << "Size: " << myData.dataBaseTupleSize() << std::endl;*/
    
    
    
    return 0;
}
