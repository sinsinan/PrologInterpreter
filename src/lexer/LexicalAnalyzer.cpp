#include "../include/lexer.hpp"

using namespace std;

std::map<std::string, lexer::Symbol> lexer::LexicalAnalyzer::initializeMap()
{
    std::map<std::string, Symbol> map = std::map<std::string, Symbol>();
    map.insert(pair<string, Symbol>("and", Symbol::AND));
    map.insert(pair<string, Symbol>("not", Symbol::NOT));
    return map;
}

lexer::LexicalAnalyzer::LexicalAnalyzer(std::string p)
{
        lineNo = 1;
        index = 0;
        program = p;
        length = p.length();
        keywordToSymbolMap = initializeMap();
};

//    public Lexer(String exp) {
//        exp = exp;
//        length = exp.length();
//        index = 0;
//        keyWordTable = new KeyWordTable();
//        lineNumber = 1;
//    }
//
 lexer::Symbol lexer::LexicalAnalyzer::getSymbol() {
        if (index >= length) {
            return Symbol::EOFSY;
        }
        Symbol tok;
        switch (program[index]) {
            // Handling comments
            case '{':
                while (program[index] != '}') {
                    index++;
                }
                index++;
                tok = getSymbol();
                break;
            case '\n':
                lineNo+=1;
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
            case '\'':
                parseCharacterLiteral();
                tok = Token.CHAR_LITERAL;
                break;
            default:
                tok = getKeyWordSymbol();
                if (tok != Token.EOFSY) {
                    break;
                }
                tok = getVariableSymbol();
                if (tok != Token.EOFSY) {
                    break;
                }
                System.out.println(String.format("Invalid character %c found at index %d in expression %s", exp.charAt(index), index, exp));
                throw new Exception("Invalid character found");
        }
        return tok;
    }
//
//    public double getNumber() {
//        return number;
//    }

lexer::Symbol lexer::LexicalAnalyzer::getDoubleFromString() {
        String numberStr = "";
        while (index < length && (exp.charAt(index) == '0' || exp.charAt(index) == '1' || exp.charAt(index) == '2' || exp.charAt(index) == '3' || exp.charAt(index) == '4' || exp.charAt(index) == '5' || exp.charAt(index) == '6' || exp.charAt(index) == '7' || exp.charAt(index) == '8' || exp.charAt(index) == '9')) {
            numberStr += exp.charAt(index);
            index++;
        }
        number = Double.parseDouble(numberStr);
        return Token.NUMERAL;
    }
//
//    private Token getKeyWordSymbol() {
//        String possibleKeyWord = "";
//        int tempIndex = index;
//        Token tokenFromKeyWord = keyWordTable.getSymbolFromKeyWord(possibleKeyWord);
//        while (keyWordTable.getKeywordMatchCount(possibleKeyWord) > 0) {
//            if (keyWordTable.getSymbolFromKeyWord(possibleKeyWord) != Token.EOFSY) {
//                tokenFromKeyWord = keyWordTable.getSymbolFromKeyWord(possibleKeyWord);
//                index = tempIndex;
//            }
//            possibleKeyWord += exp.charAt(tempIndex);
//            tempIndex++;
//        }
//        return tokenFromKeyWord;
//    }
//
//    private Token getVariableSymbol() {
//        if (Character.isLetter(exp.charAt(index))) {
//            variableName = "";
//            while (index < length && (Character.isAlphabetic(exp.charAt(index)) || Character.isDigit(exp.charAt(index)) || exp.charAt(index) == '_')) {
//                variableName += exp.charAt(index);
//                index++;
//            }
//            return Token.WORD;
//
//        } else {
//            return Token.EOFSY;
//        }
//    }
//
//    private void parseCharacterLiteral() throws Exception {
//        quotedString = "";
//        int quoteCount = 0;
//        if (exp.charAt(index) == '\'') {
//            while ((index < length) && quoteCount < 2) {
//                if (exp.charAt(index) == '\'') {
//                    quoteCount++;
//                } else {
//                    quotedString += exp.charAt(index);
//                }
//                index++;
//            }
//        }
//        if (quoteCount != 2) {
//            throw new Exception("Quoted string not ended");
//        }
//        if (quotedString.length() != 1) {
//            throw new Exception("Quoted string should be 1, got "+ quotedString.length());
//        }
//    }
//
//    private void parseQuotedString() throws Exception {
//        quotedString = "";
//        int quoteCount = 0;
//        if (exp.charAt(index) == '"') {
//            while ((index < length) && quoteCount < 2) {
//                if (exp.charAt(index) == '"') {
//                    quoteCount++;
//                } else {
//                    quotedString += exp.charAt(index);
//                }
//                index++;
//            }
//        }
//        if (quoteCount != 2) {
//            throw new Exception("Quoted string not ended");
//        }
//    }
//
//    public String getVariableName() {
//        return variableName;
//    }
//
//    public String getQuotedString() {
//        return quotedString;
//    }
//
//    public int getLineNumber() {
//        return lineNumber;
//    }
//
//    public String getNonParsedExp() {
//        return exp.substring(index);
//    }
//}
