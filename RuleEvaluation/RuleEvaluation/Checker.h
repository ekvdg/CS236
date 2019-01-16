//
//  Checker.h
//  RelationalDatabase
//
//  Created by Ellie Van De Graaff on 10/25/18.
//  Copyright © 2018 Ellie Van De Graaff. All rights reserved.
//

#ifndef Checker_h
#define Checker_h
#include <string>

class Checker{
private:
    std::string input1 = "Dependency Graph\nR0:\n\nRule Evaluation\n1 passes: R0\n\nQuery Evaluation\ndance('Sparkly glove','Thriller')? No\nsong(X,'Rock')? Yes(1)\n  X='ACDC'\nsong('Reggae',Y)? No\ndance('Cowboy hat','Cotton Eye Joe')? Yes(1)\n";
    std::string input2 ="Dependency Graph\nR0:R0\n\nRule Evaluation\n1 passes: R0\n\nQuery Evaluation\nnacho('pepperjack',X)? Yes(1)\n  X='jalepeños'\nnacho(X,Y)? Yes(2)\n  X='cheddar', Y='guacamole'\n  X='pepperjack', Y='jalepeños'\n";
    std::string input3 = "Dependency Graph\nR0:R0\nR1:R0\n\nRule Evaluation\n1 passes: R0\n1 passes: R1\n\nQuery Evaluation\nSchedule('Goofy','CS240',X)? No\nSports('Max',X)? Yes(1)\n  X='skateboarding'\nSchedule(X,Y,'Mathematics')? Yes(1)\n  X='Raqis', Y='CS240'\n";
    std::string input4 = "Dependency Graph\nR0:R0\n\nRule Evaluation\n3 passes: R0\n\nQuery Evaluation\nwatermelon(Y,Y,Y,Y)? No\nwatermelon(X,Y,X,Y)? Yes(1)\n  X='so', Y='delicious'\nwatermelon('pink','fresh',X,Y)? Yes(1)\n  X='delicious', Y='summer'\n";
    std::string input5 = "Dependency Graph\nR0:R0\n\nRule Evaluation\n1 passes: R0\n\nQuery Evaluation\nSnap(A,A,A,A)? No\nSnap('1001','Sean','16','3.2')? Yes(1)\nSnap(X,Y,Z,X)? Yes(1)\n  X='4', Y='Miranda', Z='14'\nSnap(X,Y,X,Z)? Yes(1)\n  X='15', Y='Laney', Z='3.89'\n";
    std::string input6 = "Dependency Graph\nR0:R0\n\nRule Evaluation\n1 passes: R0\n\nQuery Evaluation\npancake(P)? No\n";
    std::string input7 = "Dependency Graph\nR0:R1,R2\nR1:R1,R2\nR2:R0,R1,R2\n\nRule Evaluation\n2 passes: R0,R1,R2\n\nQuery Evaluation\nmango(A)? Yes(2)\n  A='a'\n  A='b'\nmango('a')? Yes(1)\npineapple(X,X)? No\n";
    std::string input8 = "Dependency Graph\nR0:R0\n\nRule Evaluation\n1 passes: R0\n\nQuery Evaluation\ngoldfish(X)? Yes(1)\n  X='the snack that smiles back'\n";
    std::string input9 = "Dependency Graph\nR0:R0,R1\nR1:R0,R1\n\nRule Evaluation\n2 passes: R0,R1\n\nQuery Evaluation\nab('tyler','mark')? Yes(1)\nab(who,'liam')? Yes(3)\n  who='liam'\n  who='mark'\n  who='tyler'\nab('tyler',anyone)? Yes(3)\n  anyone='liam'\n  anyone='mark'\n  anyone='tyler'\nab(X,X)? Yes(3)\n  X='liam'\n  X='mark'\n  X='tyler'\nab(X,Y)? Yes(9)\n  X='liam', Y='liam'\n  X='liam', Y='mark'\n  X='liam', Y='tyler'\n  X='mark', Y='liam'\n  X='mark', Y='mark'\n  X='mark', Y='tyler'\n  X='tyler', Y='liam'\n  X='tyler', Y='mark'\n  X='tyler', Y='tyler'\n";
    std::string input10 = "Dependency Graph\nR0:R1,R2\nR1:R0\nR2:R0,R1\n\nRule Evaluation\n5 passes: R0,R1,R2\n\nQuery Evaluation\ns('3',Z)? Yes(4)\n  Z='1'\n  Z='3'\n  Z='4'\n  Z='5'\na(Y,'3')? Yes(4)\n  Y='1'\n  Y='3'\n  Y='4'\n  Y='5'\ns(W,X)? Yes(18)\n  W='1', X='1'\n  W='1', X='2'\n  W='1', X='3'\n  W='1', X='4'\n  W='1', X='5'\n  W='3', X='1'\n  W='3', X='3'\n  W='3', X='4'\n  W='3', X='5'\n  W='4', X='1'\n  W='4', X='3'\n  W='4', X='4'\n  W='4', X='5'\n  W='5', X='1'\n  W='5', X='2'\n  W='5', X='3'\n  W='5', X='4'\n  W='5', X='5'\n";
public:
    Checker(){}
    std::vector<std::string> inputs(){
        std::vector<std::string> returnVal = {input1, input2, input3, input4, input5, input6, input7, input8, input9, input10};
        return returnVal;
    }
    
    
    
    
    
};


#endif /* Checker_h */
