//
//  Interpreter.h
//  RelationalDatabase
//
//  Created by Ellie Van De Graaff on 10/18/18.
//  Copyright © 2018 Ellie Van De Graaff. All rights reserved.
//

#ifndef Interpreter_h
#define Interpreter_h
#include "Database.h"
#include "Relation.h"
#include "Header.h"
#include "Predicate.h"
#include "Parameter.h"
#include "DatalogProgram.h"
#include "Rule.h"
#include <string>
#include <vector>
#include <sstream>

class Interpreter{
private:
    std::string name;
    Database myData;
    Relation myRel;
    std::vector<Predicate> schemes;
    std::vector<Predicate> facts;
    std::vector<Predicate> queries;
    std::vector<Rule> rules;
    
    
public:
    Interpreter(DatalogProgram parser){
        schemes = parser.returnSchemes();
        facts = parser.returnFacts();
        queries = parser.returnQueries();
        rules = parser.returnRules();
    }
    
    
    void makeRel(){
        //insert schemes
        for(unsigned int i = 0; i < schemes.size(); i++){
            name = schemes.at(i).getID();
            myRel = schemes.at(i);
            myData.insertItem(name, myRel);
        }
        //insert facts
        for(unsigned int i = 0; i < facts.size(); i++){
            name = facts.at(i).getID();
            Tuple newTuple(facts.at(i).getParam());
            myData[name].addTuple(newTuple);
        }
    }
    
    bool checkIfString(std::string name){
        if(name.substr(0,1) == "\'"){
            return true;
        }
        else{
            return false;
        }
    }
    
    bool inVector(std::vector<std::string> tupleStrings, std::string checker){
        for(unsigned int i = 0; i < tupleStrings.size(); i++){
            if(tupleStrings.at(i) == checker){
                return true;
            }
        }
        return false;
    }
    
    int returnTupleIndex(std::vector<std::string> tupleString, std::string checker){
        for(unsigned int i = 0; i < tupleString.size(); i++){
            if(checker == tupleString.at(i)){
                return i;
            }
        }
        return 0;
    }

    
    Relation evaluateQuery(Predicate currentQuery){
        std::vector<std::string> headerStrings;
        std::vector<std::string> tupleStrings;
        std::vector<int> storedIndexes;
        int index = 0;
        Relation copy = myData[currentQuery.getID()];
        for(auto& indivParam : currentQuery.getParam()){
            if(checkIfString(indivParam.storedString)){
                copy = copy.select(index,indivParam.storedString);
            }
            //else if(indivParam.storedString == repeatingString){
                //TODO- fix select function so it also takes in a variable not just a string
                //hit a variable- store the variable and the header val in two different vectors first time seen
                //check if the variable has been seen before
              //  copy.select(index,indivParam.storedString);
            //}
            else if (inVector(tupleStrings, indivParam.storedString)){
                int passedIndex = returnTupleIndex(tupleStrings, indivParam.storedString);
                copy = copy.select(index, storedIndexes.at(passedIndex));
                    //select for variables
                    
            }
            else{
                tupleStrings.push_back(indivParam.storedString);
                headerStrings.push_back(copy.getHeader().at(index));
                storedIndexes.push_back(index);
            }
            index++;
        }
        
        //std::cout << copy.toString();
        
        copy = copy.project(storedIndexes);
        //project- go through headers; if the header name is not in the vector, get rid of the header column and corresponding tuples
        //std::cout << copy.toString();
        copy = copy.rename(tupleStrings);
        //std::cout << copy.toString();
        //rename- go through the vector and rename the header values to the values in the variable vector
        return copy;
    }
    
    int interpretMain(){
        std::ostringstream out;
        makeRel();
        for(unsigned int i = 0; i < queries.size(); i++){
            Relation tempRelation;
            tempRelation = evaluateQuery(queries.at(i));
            if(tempRelation.getSize() != 0){
                out << queries.at(i).toString() << "? Yes(" << tempRelation.getSize() << ")" << std::endl;
                if(tempRelation.toString() != "  ")
                    out << tempRelation.toString();
            }
            else{
                out << queries.at(i).toString() << "? No" << std::endl;
            }
        }
        std::cout << out.str();
        return 0;
    }
       
};


#endif /* Interpreter_h */
