#include "core.h";

#include <vector>
#include <map>

enum Token {
    tok_eof = -1,

    // commands
    tok_func = -2,
    tok_export = -3,

    // primary
    tok_identifier = -4,
    tok_number = -5,
};

typedef std::map<string, int> TokenMap;


int getTokenId(string input) {
    //Define tokenMap
    TokenMap tk;
    tk["fun"] = tok_func;
    tk["export"] = tok_export;
    tk["identifier"] = tok_identifier;
    tk["number"] = tok_number;

    if (tk.find(input) != tk.end()) {
        return tk[input];
    }
    else {
        if (isalpha(input[0])) return tk["identifier"];
        if (isdigit(input[0])) return tk["number"];
    }
}

int wordSpitter(string input) {
    char lastChar;
    string word;
    std::vector<string> tokenVec;

    for (char& c : input) {
        if (isalnum(c)) {
            word.append(string(1, c));
        }
        else {
            std::cout << getTokenId(word) << std::endl;
            word = "";
        }

        lastChar = c;
    }

    return 0;
}