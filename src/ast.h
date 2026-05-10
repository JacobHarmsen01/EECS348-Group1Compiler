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

*** ast.h ***

*/

#ifndef AST_H
#define AST_H

#include <memory>
#include "token.h"

using namespace std;

struct astNode {
    virtual ~astNode() = default;
};
struct numberNode : astNode {
    double value;

    explicit numberNode(double value) : value(value) {}
};
struct unaryNode : astNode {
    tokenType op;
    unique_ptr<astNode> operand;

    unaryNode(tokenType op, unique_ptr<astNode> operand) :
            op(op), operand(std::move(operand)) {}
};
struct binaryNode : astNode {
    tokenType op;
    unique_ptr<astNode> left;
    unique_ptr<astNode> right;

    binaryNode(tokenType op, unique_ptr<astNode> left,
               unique_ptr<astNode> right)
        : op(op), left(std::move(left)), right(std::move(right)) {}
};
#endif