//
//  Parameter.hpp
//  DatalogParserP2
//
//  Created by Ellie Van De Graaff on 10/8/18.
//  Copyright © 2018 Ellie Van De Graaff. All rights reserved.
//

#ifndef Parameter_hpp
#define Parameter_hpp

#include <stdio.h>
#include <string>
#include <sstream>

class Parameter{
    
    public:
    Parameter(){}
    class Expressions{
    private:
        
    public:
        Parameter* leftOp;
        std::string operatorStr;
        Parameter* rightOp;
        
        Expressions(){
            leftOp = NULL;
            rightOp = NULL;
            operatorStr = "";
        }
        ~Expressions(){
            if(leftOp != NULL){
                //delete left;
            }
            if(rightOp != NULL){
                //delete right;
            }
        }
        Parameter* getLeft(){
            return leftOp;
        }
        void setLeft(Parameter* newLeft){
           /* Parameter temp;
            temp.storedEx.leftOp = newLeft;
            leftOp = &temp;*/
            leftOp = newLeft;
        }
        Parameter* getRight(){
            return rightOp;
        }
        void setRight(Parameter* newRight){
            /*Parameter temp;
            temp.storedEx.rightOp = newRight;
            rightOp = &temp;*/
            rightOp = newRight;
        }
        std::string getOperator(){
            return operatorStr;
        }
        void setOperator(std::string newOp){
            operatorStr = newOp;
        }
        std::string exprToString(){
            std::ostringstream out;
            if(leftOp == NULL || rightOp == NULL){
                out << "NULL";
            }
            else
                out << "(" << leftOp->toString() << operatorStr << rightOp->toString() << ")";
            return out.str();
        }
    };
    void setLeft(Parameter* newLeft){
        storedEx.setLeft(newLeft);
    }
    void setRight(Parameter* newRight){
        storedEx.setRight(newRight);
    }
    void setOp(std::string newOp){
        storedEx.setOperator(newOp);
    }
    Parameter(std::string newString){
        storedString = newString;
    }
    Parameter(Expressions newEx){
        storedEx = newEx;
    }
    
    std::string toString(){
        std::ostringstream out;
        out << "!";
        if(storedString == ""){
            out << storedEx.exprToString();
        }
        else{
            out << storedString;
        }
        return out.str();
    }
    
    void setString(std::string newString){
        storedString = newString;
    }
   
    std::string storedString;
    Expressions storedEx;
    
};

#endif /* Parameter_hpp */
