
#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H
#include <string>
#include <sstream>

class Expressions {
public:
    std::string stringValue;
    bool parsing = false;
    
    void addItem(std::string value) {
        stringValue += value;
    }
    
    void clear() {
        stringValue = "";
        parsing = false;
    }
    
    std::string toString() {
        std::ostringstream out;
        out << stringValue;
        return out.str();
    }
    
};
#endif
