//
//  Header.h
//  RelationalDatabase
//
//  Created by Ellie Van De Graaff on 10/18/18.
//  Copyright © 2018 Ellie Van De Graaff. All rights reserved.
//

#ifndef Header_h
#define Header_h
#include "Parameter.h"
#include <vector>
#include <string>
#include <sstream>

class Header : public std::vector<std::string>{
public:
    Header(std::vector<Parameter> params){
        for(unsigned int i = 0; i < params.size(); i++){
            this->push_back(params.at(i).storedString);
        }
    }
    Header(){}
    void operator=(std::vector<Parameter> params){
        for(unsigned int i = 0; i < params.size(); i++){
            this->push_back(params.at(i).storedString);
        }
    }
    
    Header modifiedHeader(unsigned int index){
        Header newHeader;
        for(unsigned int i = 0; i < this->size(); i++){
            if(i != index){
                continue;
            }
            else{
                newHeader.push_back(this->at(i));
            }
        }
        return newHeader;
    }
    
    std::string toString(){
        std::ostringstream out;
        for(unsigned int i = 0; i < this->size(); i++){
            out << this->at(i) << std::endl;
        }
        return out.str();
    }
    
    
};


#endif /* Header_h */
