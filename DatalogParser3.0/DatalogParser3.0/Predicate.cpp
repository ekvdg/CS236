//
//  Predicate.cpp
//  DatalogParserP2
//
//  Created by Ellie Van De Graaff on 10/8/18.
//  Copyright � 2018 Ellie Van De Graaff. All rights reserved.
//

#include "Predicate.h"
#include <sstream>
#include <iomanip>
#include <iostream>

std::string Predicate::rulesToString() {
    std::ostringstream out;
    out << ID << "(";
    for (unsigned int i = 0; i < parameters.size(); i++) {
        if (i == parameters.size() - 1) {
            out << parameters.at(i).toString();
        }
        else {
            out << parameters.at(i).toString() << ",";
        }
    }
    out << ")";
    std::string outString;
    outString = out.str();
    return outString;
}

std::string Predicate::queriesToString() {
    std::ostringstream out;
    out << "  " << ID << "(";
    for (unsigned int i = 0; i < parameters.size(); i++) {
        if (i == parameters.size() - 1) {
            out << parameters.at(i).toString();
        }
        else {
            out << parameters.at(i).toString() << ",";
        }
    }
    out << ")?";
    return out.str();
}

std::string Predicate::toString() {
    std::ostringstream out;
    out << "  " << ID << "(";
    for (unsigned int i = 0; i < parameters.size(); i++) {
        if (i == parameters.size() - 1) {
            out << parameters.at(i).toString();
        }
        else {
            out << parameters.at(i).toString() << ",";
        }
    }
    out << ")";
    std::string outString;
    outString = out.str();
    return outString;
}

void Predicate::addParam(Parameter newParam) {
    parameters.push_back(newParam);
}

void Predicate::setID(std::string newID) {
    ID = newID;
}

void Predicate::clear() {
    parameters.clear();
}


