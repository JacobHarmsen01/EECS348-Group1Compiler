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

*** evaluatorTest.cpp ***
! COMPONENT TESTING FILE !
*/

#include <iostream>
#include "../src/lexer.h"
#include "../src/parser.h"
#include "../src/evaluator.h"

using namespace std;

int main() {
    string input;
    
    while (true) {
        cout << "> ";
        getline(cin, input);
        if (input == "quit" || input == "exit") break;

        try {
            Lexer lexer(input);
            vector<token> tokens = lexer.tokenize();

            Parser parser(tokens);
            unique_ptr<astNode> tree = parser.parse();

            Evaluator evaluator;
            double result = evaluator.evaluate(tree.get());

            cout << "= " << result << "\n";
        } catch (const runtime_error& e) {
            cout << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}