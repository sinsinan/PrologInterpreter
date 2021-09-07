#pragma once
#include <string>
#include <map>
#include "./Symbol.hpp"
class LexicalAnalyzer
{
private:
    int lineNo;
    int index;
    std::string program;
    std::string variableName;
    double number;
    int length;
    std::map<std::string, Symbol> keywordToSymbolMap;
    std::map<std::string, Symbol> initializeMap();
    Symbol getDoubleFromString();
    Symbol getKeyWordSymbol();
    int getKeywordMatchCount(std::string);
    Symbol getVariableSymbol();

public:
    LexicalAnalyzer(std::string);
    Symbol getSymbol();
    double getNumber();
    std::string getVariableName();
    int getLineNumber();
};

