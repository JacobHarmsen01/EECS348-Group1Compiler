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

*** evaluator.cpp ***

*/

#include "evaluator.h"

using tt = tokenType;

double Evaluator::evaluate(const astNode* node) {
    if (const auto* n = dynamic_cast<const numberNode*>(node)) {
        return n->value;
    }
    if (const auto* n = dynamic_cast<const unaryNode*>(node)) {
        double operand = evaluate(n->operand.get());
        if (n->op == tt::minus) return -operand;
        if (n->op == tt::plus) return +operand;
    }
    if (const auto* n = dynamic_cast<const binaryNode*>(node)) {
        double left = evaluate(n->left.get());
        double right = evaluate(n->right.get());
        switch (n->op) {
            // Operator operation definitions with error handling for undefined expressions (ex. division by zero)
            case tt::plus: return left + right;
            case tt::minus: return left - right;
            case tt::star: return left * right;
            case tt::slash:
                if (right == 0) throw runtime_error("Cannot divide by zero");
                return left / right;
            case tt::percent:
                if (right == 0) throw runtime_error("Cannot divide by zero");
                return fmod(left, right);
            case tt::power: return pow(left, right);
            default: break;
        }
    }
    throw runtime_error("Unknown Type");
}