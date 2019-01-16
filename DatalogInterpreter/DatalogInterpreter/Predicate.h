//
//  Predicate.hpp
//  DatalogParserP2
//
//  Created by Ellie Van De Graaff on 10/8/18.
//  Copyright � 2018 Ellie Van De Graaff. All rights reserved.
//

#ifndef Predicate_hpp
#define Predicate_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "Parameter.h"

class Predicate {
private:
    std::string ID;
    std::vector<Parameter> parameters;
public:
    std::string toString();
    std::string rulesToString();
    std::string queriesToString();
    void addParam(Parameter newParam);
    void setID(std::string newID);
    void clear();
    std::string getID();
    std::vector<Parameter> getParam();
};

#endif /* Predicate_hpp */
