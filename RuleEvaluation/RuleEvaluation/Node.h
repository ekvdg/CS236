//
//  Node.h
//  RuleEvaluation
//
//  Created by Ellie Van De Graaff on 11/19/18.
//  Copyright © 2018 Ellie Van De Graaff. All rights reserved.
//

#ifndef Node_h
#define Node_h

class Node {
public:
    std::set<int> forwardGraph;
    std::set<int> reverseGraph;
    
    Node(){
        visited = false;
        flag = false;
        postOrderNum = 0;
    }
    void setVisited(bool newVal){
        visited = newVal;
    }
    bool getVisited(){
        return visited;
    }
    void setFlag(bool newVal){
        flag = newVal;
    }
    bool getFlag(){
        return flag;
    }
    void setPostOrderNum(int newVal){
        postOrderNum = newVal;
    }
    int getPostOrderNum(){
        return postOrderNum;
    }
    bool isTrivial(int index){
        for(auto& nodes : forwardGraph){
            if(index == nodes){
                return false;
            }
        }
        return true;
    }
    
private:
    bool visited;
    bool flag;
    int postOrderNum;
    
};



#endif /* Node_h */
