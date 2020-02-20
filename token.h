#pragma once
#ifndef TOKEN_H
#define TOKEN_H
#include <map>
#include "core.h"

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

int getTokenId(string input);
int wordSpitter(string input);

#endif