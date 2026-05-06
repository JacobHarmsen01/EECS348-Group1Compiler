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

*** evaluator.h ***

*/

#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <cmath>
#include <stdexcept>
#include "ast.h"
#include "token.h"

using namespace std;

class Evaluator {
    public:
        double evaluate(const astNode* node);
};
#endif