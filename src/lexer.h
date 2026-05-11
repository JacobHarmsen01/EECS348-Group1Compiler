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

*** lexer.h ***

*/

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