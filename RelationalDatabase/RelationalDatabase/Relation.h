//
//  Relation.h
//  RelationalDatabase
//
//  Created by Ellie Van De Graaff on 10/18/18.
//  Copyright © 2018 Ellie Van De Graaff. All rights reserved.
//

#ifndef Relation_h
#define Relation_h
#include <string>
#include <set>
#include <sstream>
#include "Header.h"
#include "Tuple.h"
#include "Predicate.h"

class Relation{
private:
    std::string name;
    Header myHeader;
    std::set<Tuple> tuples;
public:
    Relation(Predicate myScheme){
        name = myScheme.getID();
        myHeader = myScheme.getParam();
    }
    
    Relation(){}
    
    void operator=(Predicate myScheme){
        name = myScheme.getID();
        myHeader = myScheme.getParam();
    }
    
    void addTuple(Tuple newTup){
        tuples.insert(newTup);
    }
    
    int getSize(){
        int size = 0;
        for(Tuple x : tuples){
            size++;
        }
        return size;
    }
    
    std::string toString(){
        std::ostringstream out;
        for(Tuple x : tuples){
            out << "  ";
            for(unsigned int i = 0; i < myHeader.size(); i++){
                if(i == myHeader.size() - 1){
                    out << myHeader.at(i) << "=" << x.toString(i) << std::endl;
                }
                else{
                    out << myHeader.at(i) << "=" << x.toString(i) << ", ";
                }
            }
        }
        return out.str();
    }
    
    void eraseTuples(Tuple myTuple){
        tuples.erase(myTuple);
    }
    
    Header getHeader(){
        return myHeader;
    }
    
    bool checkIfString(std::string name){
        if(name.substr(0,1) == "\'"){
            return true;
        }
        else{
            return false;
        }
    }
    
    Relation select(int index, std::string checker){
        Relation returnRelation;
        returnRelation.myHeader = this->myHeader;
        returnRelation.name = this->name;
        for(Tuple myTuple : this->tuples){
                if(myTuple.checkForVal(index, checker)){
                    returnRelation.addTuple(myTuple);
                }
                else{
                    continue;
                }
        }

        return returnRelation;
    }
    
    Relation select(int index1, int index2){
        Relation returnRelation;
        returnRelation.myHeader = this->myHeader;
        returnRelation.name = this->name;
        for(Tuple myTuple : this->tuples){
            if(myTuple.checkVal(index1, index2)){
                returnRelation.addTuple(myTuple);
            }
            else{
                continue;
            }
        }
        return returnRelation;
    }
    
    bool inIndex(std::vector<int> &indexes, int currentIndex){
        for(unsigned int i = 0; i < indexes.size(); i++){
            if(currentIndex == indexes.at(i)){
                return true;
            }
        }
        return false;
    }
    
    Relation project(std::vector<int> indexes){
        Relation returnRelation;
        Header tempHeader;
        Tuple tempTuple;
        for(unsigned int i = 0; i < myHeader.size(); i++){
            if(inIndex(indexes, i)){
                tempHeader.push_back(myHeader.at(i));
            }
        }
        for(Tuple myTuple : tuples){
            returnRelation.addTuple(myTuple.getReducedTuple(indexes));
        }
        returnRelation.myHeader = tempHeader;
        return returnRelation;
    }
    
    Relation rename(std::vector<std::string> tupleStrings){
        for(unsigned int i = 0; i < myHeader.size(); i++){
            myHeader.at(i) = tupleStrings.at(i);
        }
        return *this;
    }
    
};

#endif /* Relation_h */
