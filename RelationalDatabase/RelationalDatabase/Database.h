//
//  Database.h
//  RelationalDatabase
//
//  Created by Ellie Van De Graaff on 10/18/18.
//  Copyright © 2018 Ellie Van De Graaff. All rights reserved.
//

#ifndef Database_h
#define Database_h
#include <map>
#include <string>
#include "Relation.h"

class Database : public std::map<std::string, Relation>{
public:
    Database(std::string name, Relation myRel){
        this->insert(std::pair<std::string, Relation>(name, myRel));
    }
    Database(){}
    void insertItem(std::string name, Relation myRel){
        this->insert(std::pair<std::string, Relation>(name, myRel));
    }

};


#endif /* Database_h */
