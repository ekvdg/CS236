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
    
    void setHeader(Header newHeader){
        myHeader = newHeader;
    }
    
    std::set<Tuple> returnTuples(){
        return tuples;
    }
    void setName(std::string newName){
        name = newName;
    }
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
    
    Relation ruleProject(std::vector<int> indexes){
        Relation returnRel;
        Header tempHeader;
        Tuple tempTuple;
        for(unsigned int i = 0; i < indexes.size(); i++){
            tempHeader.push_back(myHeader.at(i));
        }
        for(Tuple myTuple : tuples){
            returnRel.addTuple(myTuple.getReducedTuple(indexes));
        }
        returnRel.myHeader = tempHeader;
        return returnRel;
    }
    
    std::vector<int> createIndexes(std::vector<Parameter> projectTo){
        std::vector<int> indexes;
        for(unsigned int i = 0; i < projectTo.size(); i++){
            for(unsigned int j = 0; j < this->myHeader.size(); j++){
                if(projectTo.at(i).storedString == this->myHeader.at(j)){
                    indexes.push_back(j);
                }
            }
        }
        return indexes;
    }
    
    Relation rename(std::vector<std::string> tupleStrings){
        for(unsigned int i = 0; i < myHeader.size(); i++){
            myHeader.at(i) = tupleStrings.at(i);
        }
        return *this;
    }
    
    std::map<int,int> commonHeaders(const Header &header1, const Header &header2){
        //this creates a map from relation to relation of the indeces of the columns that are equal
        std::map<int,int> common;
        for(unsigned int i = 0; i < header1.size(); i++){
            for(unsigned int j = 0; j < header2.size(); j++){
                if(header1.at(i) == header2.at(j)){
                    common[i] = j;
                }
            }
        }
        return common;
    }
    
    Tuple createNewTuple(const Tuple &tuples, const Tuple &joinedTuples, std::map<int,int> &common){
        //creates the new tuples without duplicates
        Tuple returnTuple;
        for(unsigned int i = 0; i < tuples.size(); i++){
            returnTuple.push_back(tuples.at(i));
        }
        for(unsigned int i = 0; i < joinedTuples.size(); i++){
            bool seen = false;
            for(std::map<int,int>::iterator it=common.begin(); it != common.end(); it++){
                if(i == (unsigned)it->second){
                    seen = true;
                }
            }
            if(!seen)
                returnTuple.push_back(joinedTuples.at(i));
        }
        return returnTuple;
    }
    
    
    Tuple joinedTuple(const Tuple &tuples, const Tuple &joinedTuples, std::map<int,int> &common){
        //checks if the tuples qualify to be add to the joined relation
        Tuple returnTuple;
        bool tracker = true;
        for(std::map<int,int>::iterator it=common.begin(); it != common.end(); it++){
            if(tuples.at(it->first) != joinedTuples.at(it->second)){
                tracker = false;
            }
        }
        if(tracker)
            returnTuple = createNewTuple(tuples, joinedTuples, common);
        return returnTuple;
    }
    
    Header createHeader(const Header &firstHeader, const Header &secondHeader, std::map<int,int> &common){
        //create header function for when there is actual joining to be done
        Header returnHeader;
        for(unsigned int i = 0; i < firstHeader.size(); i++){
            returnHeader.push_back(firstHeader.at(i));
        }
        for(unsigned int i = 0; i < secondHeader.size(); i++){
            bool seen = false;
            for(std::map<int,int>::iterator it=common.begin(); it != common.end(); it++){
                if(i == (unsigned)it->second){
                    seen = true;
                }
            }
            if(!seen)
                returnHeader.push_back(secondHeader.at(i));
        }
        return returnHeader;
    }
    
    Header createHeader(const Header &first, const Header &second){
        //create header function for when it is just the cartesian product
        Header returnHeader;
        for(unsigned int i = 0; i < first.size(); i++){
            returnHeader.push_back(first.at(i));
        }
        for(unsigned int i = 0; i < second.size(); i++){
            returnHeader.push_back(second.at(i));
        }
        return returnHeader;
    }
    
    Tuple joinedTuple(const Tuple &first, const Tuple &second){
        Tuple returnTup;
        for(unsigned int i = 0; i < first.size(); i++){
            returnTup.push_back(first.at(i));
        }
        for(unsigned int i = 0; i < second.size(); i++){
            returnTup.push_back(second.at(i));
        }
        return returnTup;
    }
    
    
    Relation cartesianProduct(const Relation *one, Relation &two){
        //creates the joined relation when there are no columns in common
        Relation returnRel;
        returnRel.myHeader = createHeader(one->myHeader, two.myHeader);
        for(auto& tuple1 : one->tuples){
            for(auto& tuple2 : two.tuples){
                returnRel.addTuple(joinedTuple(tuple1,tuple2));
            }
        }
        return returnRel;
    }
    
    Relation join(Relation joinedRelation){
        Relation returnRel;
        std::map<int,int> common = commonHeaders(this->myHeader, joinedRelation.getHeader());
        if(common.size() == 0){
            returnRel= cartesianProduct(this, joinedRelation);
        }
        else{
            returnRel.myHeader = createHeader(this->myHeader, joinedRelation.myHeader, common);
            for(auto& tuples : this->tuples){
                for(auto& joinedTuples : joinedRelation.returnTuples()){
                    if(joinedTuple(tuples, joinedTuples, common).size() != 0)
                        returnRel.addTuple(joinedTuple(tuples, joinedTuples, common));
                }
            }
        }
        return returnRel;
    }
    
    Relation unionize(Relation unionedRelation){
        for(auto& tuples : unionedRelation.returnTuples()){
            if(this->tuples.count(tuples) == 0){
                this->addTuple(tuples);
            }
        }
        return *this;
    }
    
};

#endif /* Relation_h */
