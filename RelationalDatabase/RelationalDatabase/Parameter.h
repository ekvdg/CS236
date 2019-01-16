//
//  Parameter.hpp
//  DatalogParserP2
//
//  Created by Ellie Van De Graaff on 10/8/18.
//  Copyright � 2018 Ellie Van De Graaff. All rights reserved.
//

#ifndef Parameter_hpp
#define Parameter_hpp

#include <stdio.h>
#include <string>
#include <sstream>

class Parameter {
    
public:
    Parameter() {}
    std::string storedString;
    
    Parameter(std::string newString) {
        storedString = newString;
    }
    
    std::string toString() {
        std::ostringstream out;
        out << storedString;
        return out.str();
        
    }
    
    void setString(std::string newString) {
        storedString = newString;
    }
};

#endif /* Parameter_hpp */
