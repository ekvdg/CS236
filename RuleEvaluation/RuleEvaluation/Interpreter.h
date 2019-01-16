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
#include "Graph.h"
#include <string>
#include <vector>
#include <set>
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
    std::vector<std::set<int>> sccs;
    Graph dependencyGraph;
    int rulePass = 0;
    int previousSize;
    int currentSize;
    
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
    
    bool inVector(std::vector<std::string> &tupleStrings, std::string checker){
        for(unsigned int i = 0; i < tupleStrings.size(); i++){
            if(tupleStrings.at(i) == checker){
                return true;
            }
        }
        return false;
    }
    
    int returnTupleIndex(std::vector<std::string> &tupleString, std::string checker){
        for(unsigned int i = 0; i < tupleString.size(); i++){
            if(checker == tupleString.at(i)){
                return i;
            }
        }
        return 0;
    }
    
    void evaluateRules(Rule &currentRule){
        Relation jointRelation;
        std::string relationName = currentRule.head.getID();
        jointRelation.setName(currentRule.head.getID());
        for(unsigned int i = 0; i < currentRule.storedPred.size(); i++){
            if(i == 0){
                jointRelation = evaluateQuery(currentRule.storedPred.at(i));
            }
            else{
                jointRelation = jointRelation.join(evaluateQuery(currentRule.storedPred.at(i)));
            }
        }
        std::vector<int> indexes = jointRelation.createIndexes(currentRule.head.getParam());
        jointRelation = jointRelation.ruleProject(indexes);
        jointRelation.setName(relationName);
        myData[relationName].unionize(jointRelation);
    }
    
    Relation evaluateQuery(Predicate &currentQuery){
        std::vector<std::string> headerStrings;
        std::vector<std::string> tupleStrings;
        std::vector<int> storedIndexes;
        int index = 0;
        Relation copy = myData[currentQuery.getID()];
        for(auto& indivParam : currentQuery.getParam()){
            if(checkIfString(indivParam.storedString)){
                copy = copy.select(index,indivParam.storedString);
            }
            else if (inVector(tupleStrings, indivParam.storedString)){
                int passedIndex = returnTupleIndex(tupleStrings, indivParam.storedString);
                copy = copy.select(index, storedIndexes.at(passedIndex));
            }
            else{
                tupleStrings.push_back(indivParam.storedString);
                headerStrings.push_back(copy.getHeader().at(index));
                storedIndexes.push_back(index);
            }
            index++;
        }
        copy = copy.project(storedIndexes);
        copy = copy.rename(tupleStrings);
        return copy;
    }
    
    bool isTrivial(std::set<int> &scc){
        if(scc.size() == 1){
            int temp = 0;
            for(auto& nodes : scc){
                temp = nodes;
            }
            if(dependencyGraph.isTrivial(temp)){
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
    
    std::string rulePrint(int i){
        std::ostringstream out;
        size_t counter = 0;
        for(auto& nodes : sccs.at(i)){
            if(counter == sccs.at(i).size() - 1){
                out << "R" << nodes << std::endl;
            }
            else{
                out << "R" << nodes << ",";
            }
            counter++;
        }
        return out.str();
    }
    
    std::string ruleEvaluation(){
        std::ostringstream out;
        for(unsigned int i = 0; i < sccs.size(); i++){
            rulePass = 0;
            do{
                previousSize = myData.dataBaseTupleSize();
                for(auto& nodes : sccs.at(i)){
                    evaluateRules(rules.at(nodes));
                }
                currentSize = myData.dataBaseTupleSize();
                rulePass++;
            }
            while((previousSize != currentSize) && !isTrivial(sccs.at(i)));
            
            out << rulePass << " passes: ";
            out << rulePrint(i);
            
        }
        
        return out.str();
    }
    
    std::string queryEvaluation(){
        std::ostringstream out;
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
        return out.str();
    }
    
    
    int interpretMain(){
        std::ostringstream out;
        dependencyGraph.buildDependencyGraph(rules);
        out << "Dependency Graph" << std::endl;
        out << dependencyGraph.toStringForwardGraph() << std::endl;
        dependencyGraph.buildReverseGraph(rules);
        dependencyGraph.depthFirstSearchReverse();
        dependencyGraph.orderNodes();
        dependencyGraph.depthFirstSearchForward();
        dependencyGraph.specialCondition();
        makeRel();
        sccs = dependencyGraph.getSCCS();
        out << "Rule Evaluation" << std::endl;
        out << ruleEvaluation() << std::endl;
        out << "Query Evaluation" << std::endl;
        out << queryEvaluation();
        std::cout << out.str();
        //return out.str();
        return 0;
    }
    
};


#endif /* Interpreter_h */
