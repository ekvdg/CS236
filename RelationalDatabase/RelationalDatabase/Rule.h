//
//  Rule.hpp
//  DatalogParserP2
//
//  Created by Ellie Van De Graaff on 10/8/18.
//  Copyright � 2018 Ellie Van De Graaff. All rights reserved.
//

#ifndef Rule_hpp
#define Rule_hpp

#include <stdio.h>
#include <vector>
#include <sstream>
#include "Predicate.h"
class Rule {
private:
public:
    Predicate head;
    std::vector<Predicate> storedPred;
    void addVector(Predicate newPred) {
        storedPred.push_back(newPred);
    }
    Rule() {}
    std::string toString() {
        std::ostringstream out;
        out << head.toString() << " :- ";
        for (unsigned int i = 0; i < storedPred.size(); i++) {
            if (i == storedPred.size() - 1) {
                out << storedPred.at(i).rulesToString() << ".";
            }
            else {
                out << storedPred.at(i).rulesToString() << ",";
            }
        }
        return out.str();
    }
    void setHead(Predicate newHead) {
        head = newHead;
    }
};

#endif /* Rule_hpp */
