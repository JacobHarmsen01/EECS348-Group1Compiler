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

*** lexerTest.cpp ***
! COMPONENT TESTING FILE !
*/

#include <iostream>
#include "../src/lexer.h"

using namespace std;

int main() {
    string input;
    cout << "Enter expression: ";
    getline(cin, input);

    try {
        Lexer lexer(input);
        vector<token> tokens = lexer.tokenize();

        for (const token& t : tokens) {
            cout << "Type: " << tokenTypeName(t.type)
                 << "  Value: '" << t.value
                 << "'  Position: " << t.position << "\n";
        }
    } catch (const runtime_error& e) {
        cout << "Error: " << e.what() << "\n";
    }

    return 0;
}