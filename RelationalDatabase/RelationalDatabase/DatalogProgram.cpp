//
//  DatalogProgram.cpp
//  DatalogParser
//
//  Created by Ellie Van De Graaff on 10/1/18.
//  Copyright � 2018 Ellie Van De Graaff. All rights reserved.
//

#include <stdio.h>
#include <iomanip>
#include <iostream>
#include "DatalogProgram.h"

DatalogProgram::DatalogProgram(std::vector<Token> lexTokens) {
    passedTokens = lexTokens;
}

bool DatalogProgram::dataFacts(std::string &checkToken) {
    if (checkToken != "FACTS") {
        errorMessage();
        return false;
    }
    vecType = "facts";
    index++;
    checkToken = getTokenType();
    if (checkToken != "COLON") {
        errorMessage();
        return false;
    }
    index++;
    checkToken = getTokenType();
    if (!factList(checkToken)) {
        errorMessage();
        return false;
    }
    return true;
}
bool DatalogProgram::dataRules(std::string &checkToken) {
    if (checkToken != "RULES") {
        errorMessage();
        return false;
    }
    vecType = "rules";
    index++;
    checkToken = getTokenType();
    if (checkToken != "COLON") {
        errorMessage();
        return false;
    }
    index++;
    checkToken = getTokenType();
    if (!ruleList(checkToken)) {
        errorMessage();
        return false;
    }
    return true;
}
bool DatalogProgram::dataQueries(std::string &checkToken) {
    if (checkToken != "QUERIES") {
        errorMessage();
        return false;
    }
    vecType = "queries";
    index++;
    checkToken = getTokenType();
    if (checkToken != "COLON") {
        errorMessage();
        return false;
    }
    index++;
    checkToken = getTokenType();
    if (!query(checkToken)) {
        errorMessage();
        return false;
    }
    index++;
    checkToken = getTokenType();
    if (!queryList(checkToken)) {
        errorMessage();
        return false;
    }
    return true;
}

bool DatalogProgram::datalogProgram(std::string &checkToken) {
    //SCHEMES COLON scheme schemeList   FACTS COLON factList   RULES COLON ruleList   QUERIES COLON query queryList
    if (checkToken != "SCHEMES") {
        errorMessage();
        return false;
    }
    vecType = "schemes";
    index++;
    checkToken = getTokenType();
    if (checkToken != "COLON") {
        errorMessage();
        return false;
    }
    index++;
    checkToken = getTokenType();
    if (!scheme(checkToken)) {
        errorMessage();
        return false;
    }
    index++;
    checkToken = getTokenType();
    if (!schemeList(checkToken)) {
        errorMessage();
        return false;
    }
    if (!dataFacts(checkToken)) {
        errorMessage();
        return false;
    }
    if (!dataRules(checkToken)) {
        errorMessage();
        return false;
    }
    if (!dataQueries(checkToken)) {
        errorMessage();
        return false;
    }
    return true;
}
bool DatalogProgram::scheme(std::string &checkToken) {
    //ID LEFT_PAREN ID idList RIGHT_PAREN
    if (checkToken != "ID") {
        errorMessage();
        return false;
    }
    schemeStore.setID(passedTokens.at(index).getString());
    index++;
    checkToken = getTokenType();
    if (checkToken != "LEFT_PAREN") {
        errorMessage();
        return false;
    }
    index++;
    checkToken = getTokenType();
    if (checkToken != "ID") {
        errorMessage();
        return false;
    }
    Parameter addParameter(passedTokens.at(index).getString());
    schemeStore.addParam(addParameter);
    index++;
    checkToken = getTokenType();
    if (!idList(checkToken)) {
        errorMessage();
        return false;
    }
    if (checkToken != "RIGHT_PAREN") {
        errorMessage();
        return false;
    }
    storedSchemes.push_back(schemeStore);
    schemeStore.clear();
    return true;
}
bool DatalogProgram::schemeList(std::string &checkToken) {
    //scheme schemeList | lambda
    if (checkToken == "FACTS") {
        return true;
    }
    if (!scheme(checkToken)) {
        errorMessage();
        return false;
    }
    index++;
    checkToken = getTokenType();
    if (!schemeList(checkToken)) {
        errorMessage();
        return false;
    }
    return true;
}

bool DatalogProgram::idList(std::string &checkToken) {
    //COMMA ID idList | lambda
    if (checkToken == "RIGHT_PAREN") {
        return true;
    }
    if (checkToken != "COMMA") {
        errorMessage();
        return false;
    }
    index++;
    checkToken = getTokenType();
    if (checkToken != "ID") {
        errorMessage();
        return false;
    }
    if (vecType == "rules") {
        ruleStore.head.addParam(passedTokens.at(index).getString());
    }
    if (vecType == "schemes") {
        Parameter addParameter(passedTokens.at(index).getString());
        schemeStore.addParam(addParameter);
    }
    index++;
    checkToken = getTokenType();
    if (!idList(checkToken)) {
        errorMessage();
        return false;
    }
    return true;
}

bool DatalogProgram::fact(std::string &checkToken) {
    //ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
    if (checkToken != "ID") {
        errorMessage();
        return false;
    }
    factStore.setID(passedTokens.at(index).getString());
    index++;
    checkToken = getTokenType();
    if (checkToken != "LEFT_PAREN") {
        errorMessage();
        return false;
    }
    index++;
    checkToken = getTokenType();
    if (checkToken != "STRING") {
        errorMessage();
        return false;
    }
    Parameter addParameter(passedTokens.at(index).getString());
    factStore.addParam(addParameter);
    domain.insert(passedTokens.at(index).getString());
    index++;
    checkToken = getTokenType();
    if (!stringList(checkToken)) {
        errorMessage();
        return false;
    }
    if (checkToken != "RIGHT_PAREN") {
        errorMessage();
        return false;
    }
    index++;
    checkToken = getTokenType();
    if (checkToken != "PERIOD") {
        errorMessage();
        return false;
    }
    storedFacts.push_back(factStore);
    factStore.clear();
    return true;
}

bool DatalogProgram::factList(std::string &checkToken) {
    //fact factList | lambda
    if (checkToken == "RULES") {
        return true;
    }
    if (!fact(checkToken)) {
        errorMessage();
        return false;
    }
    index++;
    checkToken = getTokenType();
    if (!factList(checkToken)) {
        errorMessage();
        return false;
    }
    return true;
}

bool DatalogProgram::rule(std::string &checkToken) {
    //headPredicate COLON_DASH predicate predicateList PERIOD
    ruleStore = Rule();
    if (!headPredicate(checkToken)) {
        errorMessage();
        return false;
    }
    index++;
    checkToken = getTokenType();
    if (checkToken != "COLON_DASH") {
        errorMessage();
        return false;
    }
    index++;
    checkToken = getTokenType();
    if (!predicate(checkToken)) {
        errorMessage();
        return false;
    }
    index++;
    checkToken = getTokenType();
    if (!predicateList(checkToken)) {
        errorMessage();
        return false;
    }
    if (checkToken != "PERIOD") {
        errorMessage();
        return false;
    }
    storedRules.push_back(ruleStore);
    return true;
}

bool DatalogProgram::ruleList(std::string &checkToken) {
    //rule ruleList | lambda
    if (checkToken == "QUERIES") {
        return true;
    }
    if (!rule(checkToken)) {
        errorMessage();
        return false;
    }
    index++;
    checkToken = getTokenType();
    if (!ruleList(checkToken)) {
        errorMessage();
        return false;
    }
    return true;
}

bool DatalogProgram::headPredicate(std::string &checkToken) {
    //ID LEFT_PAREN ID idList RIGHT_PAREN
    if (checkToken != "ID") {
        errorMessage();
        return false;
    }
    ruleStore.head.setID(passedTokens.at(index).getString());
    index++;
    checkToken = getTokenType();
    if (checkToken != "LEFT_PAREN") {
        errorMessage();
        return false;
    }
    index++;
    checkToken = getTokenType();
    if (checkToken != "ID") {
        errorMessage();
        return false;
    }
    ruleStore.head.addParam(passedTokens.at(index).getString());
    index++;
    checkToken = getTokenType();
    if (!idList(checkToken)) {
        errorMessage();
        return false;
    }
    //index++;
    //checkToken = getTokenType();
    if (checkToken != "RIGHT_PAREN") {
        errorMessage();
        return false;
    }
    return true;
}

void DatalogProgram::extraPred(){
    if (vecType == "rules") {
        currentPred.setID(passedTokens.at(index).getString());
    }
    if (vecType == "queries")
        currentPred.setID(passedTokens.at(index).getString());
}

bool DatalogProgram::predicate(std::string &checkToken) {
    //ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    currentPred = Predicate();
    if (checkToken != "ID") {
        errorMessage();
        return false;
    }
    extraPred();
    //queryStore.setID(passedTokens.at(index).getString());
    index++;
    checkToken = getTokenType();
    if (checkToken != "LEFT_PAREN") {
        errorMessage();
        return false;
    }
    index++;
    checkToken = getTokenType();
    if (!parameter(checkToken)) {
        errorMessage();
        return false;
    }
    if (tempExpr.parsing) {
        tempExpr.addItem(")");
        Parameter holder;
        holder.setString(tempExpr.stringValue);
        currentPred.addParam(holder);
        tempExpr.clear();
    }
    else {
        currentPred.addParam(currentParam);
    }
    index++;
    checkToken = getTokenType();
    if (!parameterList(checkToken)) {
        errorMessage();
        return false;
    }
    if (checkToken != "RIGHT_PAREN") {
        errorMessage();
        return false;
    }
    otherExtraPred();
    return true;
}

void DatalogProgram::otherExtraPred(){
    if (vecType == "rules") {
        ruleStore.addVector(currentPred);
    }
    if (vecType == "queries") {
        storedQueries.push_back(currentPred);
    }
}


bool DatalogProgram::predicateList(std::string &checkToken) {
    //COMMA predicate predicateList | lambda
    if (checkToken == "PERIOD") {
        return true;
    }
    if (checkToken != "COMMA") {
        errorMessage();
        return false;
    }
    index++;
    checkToken = getTokenType();
    if (!predicate(checkToken)) {
        errorMessage();
        return false;
    }
    index++;
    checkToken = getTokenType();
    if (!predicateList(checkToken)) {
        errorMessage();
        return false;
    }
    return true;
}

bool DatalogProgram::parameter(std::string &checkToken) {
    //STRING | ID | expression
    currentParam = Parameter();
    if (checkToken == "STRING") {
        currentParam.setString(passedTokens.at(index).getString());
        return true;
    }
    else if (checkToken == "ID") {
        currentParam.setString(passedTokens.at(index).getString());
        return true;
    }
    else if (expression(checkToken)) {
        return true;
    }
    else {
        errorMessage();
        return false;
    }
}

bool DatalogProgram::parameterList(std::string &checkToken) {
    //COMMA parameter parameterList | lambda
    if (checkToken == "RIGHT_PAREN") {
        if (tempExpr.parsing) {
            tempExpr.addItem(")");
        }
        return true;
    }
    if (checkToken != "COMMA") {
        errorMessage();
        return false;
    }
    index++;
    checkToken = getTokenType();
    if (!parameter(checkToken)) {
        errorMessage();
        return false;
    }
    
    if (tempExpr.parsing) {
        tempExpr.addItem(")");
        Parameter holder;
        holder.setString(tempExpr.stringValue);
        currentPred.addParam(holder);
        tempExpr.clear();
    }
    else {
        currentPred.addParam(currentParam);
    }
    index++;
    checkToken = getTokenType();
    if (!parameterList(checkToken)) {
        errorMessage();
        return false;
    }
    return true;
}

bool DatalogProgram::expression(std::string &checkToken) {
    //LEFT_PAREN parameter operator parameter RIGHT_PAREN
    tempExpr.parsing = true;
    if (checkToken != "LEFT_PAREN") {
        errorMessage();
        return false;
    }
    tempExpr.addItem(passedTokens.at(index).getString());
    index++;
    checkToken = getTokenType();
    if (!parameter(checkToken)) {
        errorMessage();
        return false;
    }
    tempExpr.addItem(passedTokens.at(index).getString());//here
    index++;
    checkToken = getTokenType();
    if (!operatorFunction(checkToken)) {
        errorMessage();
        return false;
    }
    tempExpr.addItem(passedTokens.at(index).getString());
    index++;
    checkToken = getTokenType();
    if (!parameter(checkToken)) {
        errorMessage();
        return false;
    }
    tempExpr.addItem(passedTokens.at(index).getString());
    index++;
    checkToken = getTokenType();
    if (checkToken != "RIGHT_PAREN") {
        errorMessage();
        return false;
    }
    
    return true;
}

bool DatalogProgram::operatorFunction(std::string &checkToken) {
    //ADD | MULTIPLY
    if (checkToken == "ADD") {
        return true;
    }
    if (checkToken == "MULTIPLY") {
        return true;
    }
    return false;
}

bool DatalogProgram::query(std::string &checkToken) {
    //predicate Q_MARK
    if (!predicate(checkToken)) {
        errorMessage();
        return false;
    }
    index++;
    checkToken = getTokenType();
    if (checkToken != "Q_MARK") {
        errorMessage();
        return false;
    }
    Parameter addParamater(passedTokens.at(index).getString());
    currentPred.addParam(addParamater);
    return true;
}

bool DatalogProgram::queryList(std::string &checkToken) {
    //query queryList | lambda
    if (checkToken == "EOF") {
        return true;
    }
    if (!query(checkToken)) {
        errorMessage();
        return false;
    }
    index++;
    checkToken = getTokenType();
    if (!queryList(checkToken)) {
        errorMessage();
        return false;
    }
    return true;
}

bool DatalogProgram::stringList(std::string &checkToken) {
    //COMMA STRING stringList | lambda
    if (checkToken == "RIGHT_PAREN") {
        return true;
    }
    if (checkToken != "COMMA") {
        errorMessage();
        return false;
    }
    index++;
    checkToken = getTokenType();
    if (checkToken != "STRING") {
        errorMessage();
        return false;
    }
    Parameter addParameter(passedTokens.at(index).getString());
    factStore.addParam(addParameter);
    domain.insert(passedTokens.at(index).getString());
    index++;
    checkToken = getTokenType();
    if (!stringList(checkToken)) {
        errorMessage();
        return false;
    }
    return true;
}

void DatalogProgram::errorMessage() {
    Token failValue = passedTokens.at(index);
    throw failValue;
}


std::string DatalogProgram::getTokenType() {
    std::string returnVal;
    returnVal = passedTokens.at(index).getTokenType();
    return returnVal;
}

void DatalogProgram::printOutSchemes() {
    std::cout << "Schemes(" << storedSchemes.size() << "):" << std::endl;
    for (unsigned int i = 0; i < storedSchemes.size(); i++) {
        std::cout << storedSchemes.at(i).toString() << std::endl;
    }
}

void DatalogProgram::printOutFacts() {
    std::cout << "Facts(" << storedFacts.size() << "):" << std::endl;
    for (unsigned int i = 0; i < storedFacts.size(); i++) {
        std::cout << storedFacts.at(i).toString() << "." << std::endl;
    }
}

void DatalogProgram::printOutRules() {
    std::cout << "Rules(" << storedRules.size() << "):" << std::endl;
    for (unsigned int i = 0; i < storedRules.size(); i++) {
        std::cout << storedRules.at(i).toString() << std::endl;
    }
}

void DatalogProgram::printOutQueries() {
    std::cout << "Queries(" << storedQueries.size() << "):" << std::endl;
    for (unsigned int i = 0; i < storedQueries.size(); i++) {
        std::cout << storedQueries.at(i).queriesToString() << std::endl;
    }
}

void DatalogProgram::printOutDomain() {
    std::cout << "Domain(" << domain.size() << "):" << std::endl;
    for (std::set<std::string>::iterator it = domain.begin(); it != domain.end(); ++it) {
        std::cout << "  " << *it << std::endl;
    }
}

std::vector<Predicate> DatalogProgram :: returnSchemes(){
    return storedSchemes;
}
std::vector<Predicate> DatalogProgram :: returnFacts(){
    return storedFacts;
}
std::vector<Predicate> DatalogProgram :: returnQueries(){
    return storedQueries;
}
std::vector<Rule> DatalogProgram :: returnRules(){
    return storedRules;
}

int DatalogProgram::main() {
    std::string checkToken;
    checkToken = getTokenType();
    if (datalogProgram(checkToken)) {
        //std::cout << "Success!" << std::endl;
    }
    //printOutSchemes();
    //printOutFacts();
    //printOutRules();
    //printOutQueries();
    //printOutDomain();
    
    return 0;
}
