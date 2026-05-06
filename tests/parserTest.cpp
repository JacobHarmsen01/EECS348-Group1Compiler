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

*** parserTest.cpp ***
! COMPONENT TESTING FILE !
*/

#include <iostream>
#include "../src/lexer.h"
#include "../src/parser.h"

using namespace std;

void printAST(const astNode* node, int indent = 0) {
    string pad(indent * 2, ' ');

    if (const auto* n = dynamic_cast<const numberNode*>(node)) {
        cout << pad << n->value << "\n";
    }
    else if (const auto* n = dynamic_cast<const unaryNode*>(node)) {
        cout << pad << "unary(" << tokenTypeName(n->op) << ")\n";
        printAST(n->operand.get(), indent + 1);
    }
    else if (const auto* n = dynamic_cast<const binaryNode*>(node)) {
        cout << pad << "binary(" << tokenTypeName(n->op) << ")\n";
        printAST(n->left.get(),  indent + 1);
        printAST(n->right.get(), indent + 1);
    }
}

int main() {
    string input;
    cout << "Enter expression: ";
    getline(cin, input);

    try {
        Lexer lexer(input);
        vector<token> tokens = lexer.tokenize();

        Parser parser(tokens);
        unique_ptr<astNode> tree = parser.parse();

        printAST(tree.get());
    } catch (const runtime_error& e) {
        cout << "Error: " << e.what() << "\n";
    }

    return 0;
}