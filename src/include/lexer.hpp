#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <map>

namespace lexer {
    enum Symbol
    {
        LC_WORD,
        UC_WORD,
        NUMERAL,
        OPEN_PARANTHESIS,
        CLOSE_PARANTHESIS,
        OPEN_SQUARE,
        CLOSE_SQUARE,
        IMPLIED_BY,
        NOT,
        AND,
        COMMA,
        COLON,
        DOT,
        QUESTION,
        EOFSY,
        INVALID
    };

    class LexicalAnalyzer
    {
    private:
        int lineNo;
        int index;
        std::string program;
        std::string variableName;
        double numeral;
        int length;
        std::map<std::string, Symbol> keywordToSymbolMap;
        std::map<std::string, Symbol> initializeMap();
        lexer::Symbol getDoubleFromString();

    public:
        LexicalAnalyzer(std::string);
        Symbol getSymbol();

    };

#endif
}