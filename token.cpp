#include "core.h"
#include "bimap.h"

#include <vector>
#include <ctype.h>

namespace tk {
    enum TokenType {
        _err = -1,
        _eof = 0,

        //Keywords
        _if = 1, _else = 2,
        _true = 3, _false = 4,
        _null = 5,
        _and = 6, _or = 7,
        _function = 8,
        _return = 9,
        _var = 10,
        _for = 11, _while = 12,

        //Literals
        _identifier = 13,
        _string = 14,
        _number = 15,

        //One or two character tokens
        _bang = 16, _bang_eq = 17,
        _eq = 18, _eq_eq = 19,
        _greater = 20, _greater_eq = 21,
        _less = 21, less_eq = 22,

        //One character tokens
        _l_paren = 23, _r_paren = 24,
        _l_brace = 25, _r_brace = 25,
        _comma = 26, _dot = 27,
        _minus = 28, _plus = 29, _slash = 30, _asterisk = 31,
        _semicolon = 32
    };
    
    typedef Bimap<string, TokenType> LexemesMap;
    typedef struct { string content; TokenType id; } ContentfulLexeme;
  
    LexemesMap lexemesDef;

    const int populateLexemes = [&] {
        lexemesDef.set("true", _true);
        lexemesDef.set("false", _false);
        lexemesDef.set("null", _null);
        lexemesDef.set("function", _function);
        lexemesDef.set("return", _return);
        lexemesDef.set("var", _var);

        lexemesDef.set("identifier", _identifier);
        lexemesDef.set("string", _string);
        lexemesDef.set("number", _number);

        lexemesDef.set("=", _eq);
        lexemesDef.set("==", _eq_eq);
        lexemesDef.set("!", _bang);
        lexemesDef.set("!=", _bang_eq);

        lexemesDef.set("{", _l_brace);
        lexemesDef.set("}", _r_brace);
        lexemesDef.set("(", _l_paren);
        lexemesDef.set(")", _r_paren);
        lexemesDef.set("-", _minus);
        lexemesDef.set("+", _plus);
        lexemesDef.set(",", _comma);

        lexemesDef.set(";", _semicolon);

        return 0;
    }();


    ContentfulLexeme getContentfulLexeme(string input) {
        ContentfulLexeme error = { "", _err };

        if (lexemesDef.hasKey(input)) {

            return ContentfulLexeme { input, lexemesDef.valueForKey(input) };
        }
        else {
            TokenType lexeme = _err;
            
            if (isalpha(input[0])) lexeme = lexemesDef.valueForKey("identifier");
            if (isdigit(input[0])) lexeme = lexemesDef.valueForKey("number");
            if (input[0] == '"') lexeme = lexemesDef.valueForKey("string");

            return ContentfulLexeme{ input, lexeme };
        }

        return error;
    }
}


bool canBeFollowed(char c) {
    return (c == '=' || c == '!');
}

using namespace tk;

int tokenizer(string input) {
    int i = input.length();
    char lastChar = '\0';
    char firstChar = '\0';
    bool shouldAppend = false;
    string word;

    std::vector<string> tokenVec;

    for (char& c : input) {
        if (word.length() == 0) firstChar = c;

        shouldAppend = false;
        if (isalnum(firstChar) && isalnum(c)) shouldAppend = true;
        if (ispunct(firstChar) && ispunct(c) && (canBeFollowed(firstChar) == word.length() > 0)) shouldAppend = true;
        if (ispunct(firstChar) && ispunct(c) && word.length() == 0) shouldAppend = true;

        if (shouldAppend){
            word.append(string(1, c));
        }
        else if (word.length()) {
            ContentfulLexeme lex = getContentfulLexeme(word);
            string lexType = lexemesDef.keyForValue(lex.id);
            std::cout << lex.content << "\t\t\t" << lex.id << "\t\t\t" << lexType << std::endl;

            word = "";
            if (isalnum(c) || ispunct(c)) {
                firstChar = c;
                word.append(string(1, c));
            }
        }

        lastChar = c;
    }
    return 0;
}