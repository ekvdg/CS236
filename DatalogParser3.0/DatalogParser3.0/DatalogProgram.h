//
//  DatalogProgram.h
//  DatalogParser
//
//  Created by Ellie Van De Graaff on 10/1/18.
//  Copyright � 2018 Ellie Van De Graaff. All rights reserved.
//

#ifndef DatalogProgram_h
#define DatalogProgram_h
#include "Token.h"
#include "Scanner.h"
#include <vector>
#include <string>
#include <set>
#include "Predicate.h"
#include "Rule.h"
#include "Parameter.h"
#include "Expressions.h"

class DatalogProgram {
private:
    std::vector<Token> passedTokens;
    std::set<std::string> domain;
    std::vector<Predicate> storedSchemes;
    Predicate schemeStore;
    std::vector<Predicate> storedFacts;
    Predicate factStore;
    std::vector<Predicate> storedQueries;
    Predicate queryStore;
    Rule ruleStore;
    std::vector<Rule> storedRules;
    Predicate currentPred;
    Parameter currentParam;
    std::string vecType;
    Expressions tempExpr;
    int index = 0;
public:
    int main();
    DatalogProgram(std::vector<Token> lexTokens);
    void errorMessage();
    std::string getTokenType();
    void printOutSchemes();
    void extraPred();
    void otherExtraPred();
    void printOutFacts();
    void printOutRules();
    void printOutQueries();
    void printOutDomain();
    bool datalogProgram(std::string &checkToken);
    bool dataFacts(std::string &checkToken);
    bool dataRules(std::string &checkToken);
    bool dataQueries(std::string &checkToken);
    bool scheme(std::string &checkToken);
    bool schemeList(std::string &checkToken);
    bool idList(std::string &checkToken);
    bool fact(std::string &checkToken);
    bool factList(std::string &checkToken);
    bool rule(std::string &checkToken);
    bool ruleList(std::string &checkToken);
    bool headPredicate(std::string &checkToken);
    bool predicate(std::string &checkToken);
    bool predicateList(std::string &checkToken);
    bool parameter(std::string &checkToken);
    bool parameterList(std::string &checkToken);
    bool expression(std::string &checkToken);
    bool operatorFunction(std::string &checkToken);
    bool query(std::string &checkToken);
    bool queryList(std::string &checkToken);
    bool stringList(std::string &checkToken);
};


#endif /* DatalogProgram_h */
