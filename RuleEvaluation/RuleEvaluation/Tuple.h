//
//  Tuple.h
//  RelationalDatabase
//
//  Created by Ellie Van De Graaff on 10/18/18.
//  Copyright © 2018 Ellie Van De Graaff. All rights reserved.
//

#ifndef Tuple_h
#define Tuple_h
#include <vector>
#include <string>
#include <sstream>
#include "Parameter.h"
class Tuple : public std::vector<std::string>{
public:
    Tuple(std::vector<Parameter> params){
        for(unsigned int i = 0; i < params.size(); i++){
            this->push_back(params.at(i).storedString);
        }
    }
    Tuple(){}
    
    bool checkForVal(unsigned int index, std::string checker){
        for(unsigned int i = 0; i < this->size(); i++){
            if(i == index && this->at(i) == checker){
                return true;
            }
        }
        return false;
    }
    
    std::string toString(int index){
        return this->at(index);
    }
    
     bool checkVal(unsigned int index1, unsigned int index2){
        if(this->at(index1) == this->at(index2)){
            return true;
        }
        else{
            return false;
        }
        return false;
    }
    
    Tuple getReducedTuple(std::vector<int> &indexes){
        Tuple returnTuple;
        for(unsigned int i = 0; i < indexes.size(); i++){
            returnTuple.push_back(this->at(indexes.at(i)));
            
        }
        return returnTuple;
    }
};

#endif /* Tuple_h */
