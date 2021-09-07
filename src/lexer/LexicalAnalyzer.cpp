#include "../include/LexicalAnalyzer.hpp"

std::map<std::string, Symbol> LexicalAnalyzer::initializeMap()
{
    std::map<std::string, Symbol> map = std::map<std::string, Symbol>();
    map.insert(std::pair<std::string, Symbol>("and", Symbol::AND));
    map.insert(std::pair<std::string, Symbol>("not", Symbol::NOT));
    return map;
}

LexicalAnalyzer::LexicalAnalyzer(std::string p)
{
    lineNo = 1;
    index = 0;
    program = p;
    length = p.length();
    keywordToSymbolMap = initializeMap();
};

Symbol LexicalAnalyzer::getSymbol() {
    if (index >= length) {
        return Symbol::EOFSY;
    }
    Symbol tok;
    switch (program[index]) {
    case '{':
        while (program[index] != '}') {
            if (program[index] == '\n')
            {
                lineNo++;
            }
            index++;
        }
        index++;
        tok = getSymbol();
        break;
    case '\n':
        lineNo += 1;
    case '\t':
    case ' ':
        index++;
        tok = getSymbol();
        break;
    case ',':
        index++;
        tok = Symbol::COMMA;
        break;
    case '(':
        index++;
        tok = Symbol::OPEN_PARANTHESIS;
        break;
    case ')':
        index++;
        tok = Symbol::CLOSE_PARANTHESIS;
        break;
    case '[':
        index++;
        tok = Symbol::OPEN_SQUARE;
        break;
    case ']':
        index++;
        tok = Symbol::CLOSE_SQUARE;
        break;

    case '.':
        index++;
        tok = Symbol::DOT;
        break;
    case '<':
        index++;
        if (index + 1 < length && program[index] == '=')
        {
            tok = Symbol::IMPLIED_BY;
            break;
        }
        //error
    case ':':
        tok = Symbol::COLON;
        index++;
        if (index + 1 < length && program[index] == '-')
        {
            tok = Symbol::IMPLIED_BY;
            break;
        }
        break;
    case '?':
        index++;
        tok = Symbol::QUESTION;
        break;
    case '&':
        index++;
        tok = Symbol::AND;
        break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        tok = getDoubleFromString();
        break;
    default:
        tok = getKeyWordSymbol();
        if (tok != Symbol::EOFSY) {
            break;
        }
        tok = getVariableSymbol();
        if (tok != Symbol::EOFSY) {
            break;
        }
        //error
    }
    return tok;
}

double LexicalAnalyzer::getNumber() {
    return number;
}

Symbol LexicalAnalyzer::getDoubleFromString() {
    std::string numberStr = "";
    while (index < length && (program[index] == '0' || program[index] == '1' || program[index] == '2' || program[index] == '3' || program[index] == '4' || program[index] == '5' || program[index] == '6' || program[index] == '7' || program[index] == '8' || program[index] == '9')) {
        numberStr += program[index];
        index++;
    }
    number = stod(numberStr);
    return Symbol::NUMERAL;
}

Symbol LexicalAnalyzer::getKeyWordSymbol() {
    std::string possibleKeyWord = "";
    int tempIndex = index;
    std::map<std::string, Symbol>::const_iterator keywordSymbolInterator;
    Symbol tokenFromKeyWord = Symbol::EOFSY;
    while (getKeywordMatchCount(possibleKeyWord) > 0) {
        keywordSymbolInterator = keywordToSymbolMap.find(possibleKeyWord);
        if (keywordSymbolInterator != keywordToSymbolMap.end()) {
            tokenFromKeyWord = keywordSymbolInterator->second;
            index = tempIndex;
        }
        possibleKeyWord += program[tempIndex];
        tempIndex++;
    }
    return tokenFromKeyWord;
}

int LexicalAnalyzer::getKeywordMatchCount(std::string inputKeyWord) {
    int count = 0;
    for (auto keywordSymbolPair : keywordToSymbolMap) {
        if (keywordSymbolPair.first.rfind(inputKeyWord, 0) == 0 || keywordSymbolPair.first == inputKeyWord) {
            count++;
        }
    }
    return count;
}

Symbol  LexicalAnalyzer::getVariableSymbol() {
    if (iswalpha(program[index])) {
        variableName = "";
        while (index < length && (iswalpha(program[index]) || iswalnum(program[index]))) {
            variableName += program[index];
            index++;
        }
        if (islower(variableName[0]))
        {
            return Symbol::LC_WORD;
        }
        else
        {
            return Symbol::UC_WORD;
        }
    }
    else {
        return Symbol::EOFSY;
    }
}
std::string LexicalAnalyzer::getVariableName() {
    return variableName;
}
int LexicalAnalyzer::getLineNumber() {
    return lineNo;
}