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

*** printer.cpp ***

*/

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <vector>

#include "printer.h"

using namespace std;

// AST Node Colors
static string nodeColor(const astNode* node) {
    if (dynamic_cast<const numberNode*>(node))  return Colors::Teal;
    if (dynamic_cast<const unaryNode*>(node))   return Colors::Coral;
    if (dynamic_cast<const binaryNode*>(node))  return Colors::Amber;
    return Colors::White;
}
// AST Node Labels
static string nodeLabel(const astNode* node) {
    if (const auto* n = dynamic_cast<const numberNode*>(node)) {
        ostringstream ss;
        if (n->value == (long long)n->value && abs(n->value) < 1e12)
            ss << (long long)n->value;
        else
            ss << fixed << setprecision(6) << n->value;
        return ss.str();
    }
    if (const auto* n = dynamic_cast<const unaryNode*>(node))
        return string("unary(") + tokenTypeName(n->op) + ")";
    if (const auto* n = dynamic_cast<const binaryNode*>(node))
        return string("binary(") + tokenTypeName(n->op) + ")";
    return "?";
}
// AST Node types (number, unary (+/-), binary)
static string nodeType(const astNode* node) {
    if (dynamic_cast<const numberNode*>(node))  return "num";
    if (dynamic_cast<const unaryNode*>(node))   return "unary";
    if (dynamic_cast<const binaryNode*>(node))  return "binary";
    return "";
}
// Text color
static string tokenColor(tokenType t) {
    using tt = tokenType;
    switch(t) {
        case tt::number:    return Colors::Teal;
        case tt::plus:
        case tt::minus:     return Colors::Green;
        case tt::star:
        case tt::slash:
        case tt::percent:   return Colors::Amber;
        case tt::power:     return Colors::Coral;
        case tt::lParen:
        case tt::rParen:    return Colors::Purple;
        case tt::end:       
    }
    return Colors::White;
}
// Get node children
static vector<const astNode*> getChildren(const astNode* node) {
    vector<const astNode*> ch;
    if (const auto* n = dynamic_cast<const unaryNode*>(node)) {
        if (n->operand)     ch.push_back(n->operand.get());
    } else if (const auto* n = dynamic_cast<const binaryNode*>(node)) {
        if (n->left)        ch.push_back(n->left.get());
        if (n->right)       ch.push_back(n->right.get());
    }
    return ch;
}
// Print AST
void printTree(const astNode* node, const string& prefix, bool isLast) {
    if (!node) return;

    string connector =      isLast ? "\u2514\u2500\u2500 " : "\u251C\u2500\u2500 ";
    string childPrefix =    prefix + (isLast ? "   ": "/u2502  ");
    string color =          nodeColor(node);
    string label =          nodeLabel(node);
    string type =           nodeType(node);

    cout << Colors::White << prefix << connector << Colors::Reset
         << Colors::Bold << color << label << Colors::Reset
         << " "
         << Colors::White << type << Colors::Reset
         << "\n";

    auto children = getChildren(node);

    for (size_t i = 0; i < children.size(); i++)
        printTree(children[i], childPrefix, i == children.size() - 1);
}
// Stream of tokens to AST
void printTokens(const vector<token>& tokens) {
    cout << Colors::White << "  tokens  " << Colors::Reset;
    for (const auto& t : tokens) {
        if (t.type == tokenType::end) break;

        string col = tokenColor(t.type);
        cout << col << Colors::Bold << tokenTypeName(t.type) << Colors::Reset;

        if (!t.value.empty() && t.value != tokenTypeName(t.type))
            cout << Colors::White << "(" << t.value << ")" << Colors::Reset;
        cout << " ";
    }
    cout << "\n\n";
}
// CLI UI Structure
void printDivider(char c, int width) {
    cout << Colors::White;
    for (int i = 0; i < width; i++) cout << c;
    cout << Colors::Reset << "\n";
}
void printHeader() {
    cout << "\n";
    printDivider('-', 60);
    cout << Colors::Bold << Colors::Crimson << "    expr" << Colors::Reset
         << Colors::Bold << Colors::White << "parser" << Colors::Reset
         << Colors::White << "  c++ arithmetic expression compiler\n"
         << Colors::Reset;
    printDivider('-', 60);
    cout << "\n";
}
void printResult(double val, const string& expr) {
    ostringstream ss;
    if (val == (long long)val && abs(val) < 1e12)
        ss << (long long)val;
    else
        ss << fixed << setprecision(8) << val;
    
    cout << Colors::White << "  result  " << Colors::Reset
         << Colors::White << expr << Colors::Reset
         << Colors::White << "  =   " << Colors::Reset
         << Colors::Bold << Colors::Green << ss.str() << Colors::Reset
         << "\n\n";
}
void printError(const string& msg) {
    cout << "\n"
         << Colors::Bold << Colors::Red << "    error   " << Colors::Reset
         << Colors::White << msg << Colors::Reset
         << "\n\n";
}
