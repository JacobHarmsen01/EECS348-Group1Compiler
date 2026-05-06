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

*** printer.h ***

*/

#ifndef PRINTER_H
#define PRINTER_H

#include <string>
#include <vector>
#include "ast.h"
#include "token.h"

using namespace std;

// Terminal output colors
namespace Colors {
    const string Reset   = "\033[0m";
    const string Bold    = "\033[1m";
    const string Crimson = "\033[38;5;196m";
    const string Teal    = "\033[38;5;43m";
    const string Amber   = "\033[38;5;214m";
    const string Coral   = "\033[38;5;209m";
    const string Purple  = "\033[38;5;141m";
    const string Green   = "\033[38;5;84m";
    const string Red     = "\033[38;5;160m";
    const string White   = "\033[38;5;252m";
}
// Print tree
void printTree(const astNode* node, const string& prefix = "", bool isLast = true);

// Token stream to tree
void printTokens(const vector<token>& tokens);

// UI stuff
void printDivider(char c = '-', int width = 60);
void printHeader();
void printResult(double val, const string& msg);
void printError(const string& msg);

#endif


