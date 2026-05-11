/*
******** exprparser ********
A C++ Mathematical Arithmetic compiler

exprparser takes a mathematical expression and calculates the answer using proper order of operations.
It features a color CLI and returns a graphical token classifier and Abstract Syntax Tree that makes up the provided expression.

--- Authors ---
Quinn Sells - Designer & Programmer
Jacob Harmsen - Project Manager
Hudson Rupp - Implementer
Logan Sigg - Reviewer
Lauren Wesely - Integrator
Collin Rawson - Tester

--- University ---
The University of Kansas School of Engineering
EECS 348 - Software Engineering
Professor Hossein Saedian

*** lexer.cpp ***

*/

#include "lexer.h"

using namespace std;
using L = Lexer;
using tt = tokenType;

L::Lexer(const string& input) : input(input), pos(0) {}

char L::current() const { // Current character position
    if (pos >= input.size()) return '\0';
    return input[pos];
}
char L::peek() const { // Peek at next character position
    if (pos + 1 >= input.size()) return '\0';
    return input[pos + 1];
}
void L::advance() {
    pos++;
}
void L::skipWhiteSpace() {
    while (pos < input.size() && isspace(current()))
        advance();
}
token Lexer::readNumber() {
    size_t start = pos;
    while (isdigit(current())) advance();
    if (current() == '.' && isdigit(peek())) {
        advance();
        while (isdigit(current())) advance();
    }
    return token(tt::number, input.substr(start, pos - start), start);
}
vector<token> L::tokenize() {
    vector<token> tokens;

    while (pos < input.size()) {
        skipWhiteSpace();
        if (pos >= input.size()) break;

        char c = current();
        size_t tokenStart = pos;

        if (isdigit(c)) {
            tokens.push_back(readNumber());
            continue;
        }
        switch(c) {
            case '+': tokens.push_back(token(tt::plus, "+", tokenStart)); break;
            case '-': tokens.push_back(token(tt::minus, "-", tokenStart)); break;
            case '/': tokens.push_back(token(tt::slash, "/", tokenStart)); break;
            case '%': tokens.push_back(token(tt::percent, "%", tokenStart)); break;
            case '(': tokens.push_back(token(tt::lParen, "(", tokenStart)); break;
            case ')': tokens.push_back(token(tt::rParen, ")", tokenStart)); break;
            case '*': // When compiler sees a '*', it peeks at next char to determine multiplication or power.
                if (peek() == '*') {
                    tokens.push_back(token(tt::power, "**", tokenStart));
                    advance();
                }
                else {
                    tokens.push_back(token(tt::star, "*", tokenStart));
                }
                break;
            default:
                throw runtime_error("Unknown character '" + string(1, c) +
                                    "' at position " + to_string(tokenStart));
        }
        advance();
    }
    tokens.push_back(token(tt::end, "", pos));
    return tokens;
}