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
    std::string input1 = "dance('Sparkly glove','Thriller')? No\nsong(X,'Rock')? Yes(1)\n  X='ACDC'\nsong('Reggae',Y)? No\ndance('Cowboy hat','Cotton Eye Joe')? Yes(1)\n";
    std::string input2 ="nacho('pepperjack',X)? Yes(1)\n  X='jalepeños'\nnacho(X,Y)? Yes(2)\n  X='cheddar', Y='guacamole'\n  X='pepperjack', Y='jalepeños'\n";
    std::string input3 = "Schedule('Goofy','CS240',X)? No\nSports('Max',X)? Yes(1)\n  X='skateboarding'\nSchedule(X,Y,'Mathematics')? Yes(1)\n  X='Raqis', Y='CS240'\n";
    std::string input4 = "watermelon(Y,Y,Y,Y)? No\nwatermelon(X,Y,X,Y)? Yes(1)\n  X='so', Y='delicious'\nwatermelon('pink','fresh',X,Y)? Yes(1)\n  X='delicious', Y='summer'\n";
    std::string input5 = "Snap(A,A,A,A)? No\nSnap('1001','Sean','16','3.2')? Yes(1)\nSnap(X,Y,Z,X)? Yes(1)\n  X='4', Y='Miranda', Z='14'\nSnap(X,Y,X,Z)? Yes(1)\n  X='15', Y='Laney', Z='3.89'\n";
    std::string input6 = "pancake(P)? No\n";
    std::string input7 = "mango(A)? Yes(2)\n  A='a'\n  A='b'\nmango('a')? Yes(1)\npineapple(X,X)? No\n";
    std::string input8 = "goldfish(X)? Yes(1)\n  X='the snack that smiles back'\n";
    std::string input9 = "ab('tyler','mark')? Yes(1)\nab(who,'liam')? Yes(3)\n  who='liam'\n  who='mark'\n  who='tyler'\nab('tyler',anyone)? Yes(2)\n  anyone='liam'\n  anyone='mark'\nab(X,X)? Yes(1)\n  X='liam'\nab(X,Y)? Yes(4)\n  X='liam', Y='liam'\n  X='mark', Y='liam'\n  X='tyler', Y='liam'\n  X='tyler', Y='mark'\n";
    std::string input10 = "s('3',Z)? No\na(Y,'3')? No\ns(W,X)? Yes(2)\n  W='1', X='2'\n  W='4', X='3'\n";
public:
    Checker(){}
    std::vector<std::string> inputs(){
        std::vector<std::string> returnVal = {input1, input2, input3, input4, input5, input6, input7, input8, input9, input10};
        return returnVal;
    }
    
    
    
    
    
};


#endif /* Checker_h */
