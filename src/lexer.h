#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>
#include <stdexcept>
#include "token.h"

using namespace std;

class Lexer {
public:
    explicit Lexer(const string& input);
    vector<token> tokenize();

private:
    string input;
    size_t pos;

    char current() const;
    char peek() const;
    void advance();
    void skipWhiteSpace();
    token readNumber();
};

#endif