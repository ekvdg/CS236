//
//  Graph.h
//  RuleEvaluation
//
//  Created by Ellie Van De Graaff on 11/19/18.
//  Copyright © 2018 Ellie Van De Graaff. All rights reserved.
//

#ifndef Graph_h
#define Graph_h
#include <vector>
#include <sstream>
#include <stack>
#include "Node.h"
#include "Rule.h"
#include "Predicate.h"

class Graph{
private:
    std::vector<Node> dependencyGraph;
    std::vector<Node> reverse;
    std::vector<std::set<int>> sccs;
    std::vector<int> order;
    std::stack<int> tracker;
    std::set<int> temporary;
    int popIndex = 0;
    int size = 0;
public:
    void buildDependencyGraph(std::vector<Rule> &rules){
        Node addNode;
        for(auto& indivRule : rules){
            for(auto& preds : indivRule.storedPred){
                for(unsigned int i = 0; i < rules.size(); i++){
                    if(rules.at(i).head.getID() == preds.getID()){
                        addNode.forwardGraph.insert(i);
                    }
                }
            }
            dependencyGraph.push_back(addNode);
            addNode.forwardGraph.clear();
        }
    }
    
    void initVector(size_t size){
        Node emptyNode;
        for(unsigned int i = 0; i < size; i++){
            reverse.push_back(emptyNode);
        }
    }
    
    void buildReverseGraph(std::vector<Rule> &rules){
        initVector(rules.size());
        for(unsigned int i = 0; i < dependencyGraph.size(); i++){
            reverse.at(i).forwardGraph = dependencyGraph.at(i).forwardGraph;
            for(auto& nodes : dependencyGraph.at(i).forwardGraph){
                reverse.at(nodes).reverseGraph.insert(i);
            }
        }
    }
    
    bool allVisitedReverse(int index){
        for(auto& nodes : reverse.at(index).reverseGraph){
            if(reverse.at(nodes).getVisited() != true){
                return false;
            }
        }
        return true;
    }
    
    bool allVisitedForward(int index){
        for(auto& nodes : dependencyGraph.at(index).forwardGraph){
            if(dependencyGraph.at(nodes).getVisited() != true){
                return false;
            }
        }
        return true;
    }
    
    void orderNodes(){
        size = (int)reverse.size() - 1;
        while(size >= 0){
            orderRecursive();
        }
    }
    
    void orderRecursive(){
        for(unsigned int i = 0; i < reverse.size(); i++){
            if(reverse.at(i).getPostOrderNum() == size){
                order.push_back(i);
                size--;
            }
        }
    }
    
    void depthFirstSearchForward(){
        orderNodes();
        for(unsigned int i = 0; i < order.size(); i++){
            if(dependencyGraph.at(order.at(i)).getVisited() != true){
                forwardRecursive(order.at(i));
                sccs.push_back(temporary);
                temporary.clear();
            }
        }
    }
    
    void forwardRecursive(int index){
        dependencyGraph.at(index).setVisited(true);
        temporary.insert(index);
        if(dependencyGraph.at(index).forwardGraph.size() == 0 || allVisitedForward(index)){
            return;
        }
        else{
            for(auto& nodes : dependencyGraph.at(index).forwardGraph){
                if(dependencyGraph.at(nodes).getVisited() != true){
                    forwardRecursive(nodes);
                }
            }
        }
    }
    
    void depthFirstSearchReverse(){
        for(unsigned int i = 0; i < reverse.size(); i++){
            if(reverse.at(i).getVisited() != true){
                reverseRecursive(i);
            }
        }
    }
    
    void reverseRecursive(int index){
        tracker.push(index);
        reverse.at(index).setVisited(true);
        if(reverse.at(index).reverseGraph.size() == 0 || allVisitedReverse(index)){
            tracker.pop();
            reverse.at(index).setPostOrderNum(popIndex);
            popIndex++;
        }
        else{
            for(auto& nodes : reverse.at(index).reverseGraph){
                if(reverse.at(nodes).getVisited() != true){
                    reverseRecursive(nodes);
                }
            }
            tracker.pop();
            reverse.at(index).setPostOrderNum(popIndex);
            popIndex++;
        }
    }
    
    std::vector<std::set<int>> &getSCCS(){
        return sccs;
    }
    
    void specialCondition(){
        for(unsigned int i = 0; i < dependencyGraph.size(); i++){
            if(dependencyGraph.at(i).isTrivial(i)){
                dependencyGraph.at(i).setFlag(true);
            }
        }
    }
    
    bool isTrivial(int index){
        if(dependencyGraph.at(index).getFlag() == true){
            return true;
        }
        else{
            return false;
        }
    }
    
    
    std::string toStringForwardGraph(){
        std::ostringstream out;
        for(unsigned int i = 0; i < dependencyGraph.size(); i++){
            out << "R" << i << ":";
            unsigned int forwardIndex = 0;
            for(auto& nodes : dependencyGraph.at(i).forwardGraph){
                if(forwardIndex < dependencyGraph.at(i).forwardGraph.size() - 1){
                    out << "R" << nodes << ",";
                }
                else{
                    out << "R" << nodes;
                }
                forwardIndex++;
            }
            out << std::endl;
        }
        return out.str();
    }
    
    std::string toStringReverseGraph(){
        std::ostringstream out;
        for(unsigned int i = 0; i < reverse.size(); i++){
            out << "R" << i << ":";
            unsigned int reverseIndex = 0;
            for(auto& nodes : reverse.at(i).reverseGraph){
                if(reverseIndex < reverse.at(i).reverseGraph.size() - 1){
                    out << "R" << nodes << ",";
                }
                else{
                    out << "R" << nodes;
                }
                reverseIndex++;
            }
            out << std::endl;
        }
        
        
        return out.str();
    }
    
    std::string postOrder(){
        std::ostringstream out;
        out << std::endl << "Post-Order Traversal Numbers" << std::endl;
        for(auto& nodes : reverse){
            out << nodes.getPostOrderNum() << std::endl;
        }
        return out.str();
    }

    
    
};


#endif /* Graph_h */
