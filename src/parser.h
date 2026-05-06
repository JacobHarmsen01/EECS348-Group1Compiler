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

*** parser.h ***

*/

#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>
#include <stdexcept>
#include "token.h"
#include "ast.h"

using namespace std;

class Parser {
    public:
        explicit Parser(const vector<token>& tokens);
        unique_ptr<astNode> parse();
    
    private:
        vector<token> tokens;
        size_t pos;

        token current() const;
        token consume();
        token expect(tokenType type);

        unique_ptr<astNode> parseExpression(); // + , -
        unique_ptr<astNode> parseTerm(); // * , / , %
        unique_ptr<astNode> parsePower(); // **
        unique_ptr<astNode> parseUnary(); // unary
        unique_ptr<astNode> parsePrimary(); // numbers, parens
};
#endif