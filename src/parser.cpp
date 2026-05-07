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

*** parser.cpp ***

*/

#include "parser.h"

using P = Parser;
using tt = tokenType;

using namespace std;

P::Parser(const vector<token>& tokens) : tokens(tokens), pos(0) {}

token P::current() const {
    return tokens[pos];
}
token P::consume() {
    return tokens[pos++];
}
token P::expect(tt type) {
    if (current().type != type)
        throw runtime_error("Expected '" + string(tokenTypeName(type)) +
                            "' but got '" + string(tokenTypeName(current().type)) +
                            "' at position " + to_string(current().position));
    return consume();
}
unique_ptr<astNode> P::parse() {
    auto result = parseExpression();
    expect(tt::end);
    return result;
}
unique_ptr<astNode> P::parsePrimary() {
    token t = current();

    if (t.type == tt::number) {
        consume();
        return make_unique<numberNode>(stod(t.value));
    }
    if (t.type == tt::lParen) {
        consume(); // open expression
        auto expr = parseExpression();
        expect(tt::rParen); // make sure there is a closing )
        return expr;
    }
    throw runtime_error("Unexpected token '" + string(tokenTypeName(t.type)) +
                        "' at position " + to_string(t.position));
}
unique_ptr<astNode> P::parseUnary() {
    token t = current();

    if (t.type == tt::minus || t.type == tt::plus) {
        consume();
        auto operand = parseUnary(); // recursive function to handle "--", "++", etc
        return make_unique<unaryNode>(t.type, std::move(operand));
    }
    return parsePrimary();
}
unique_ptr<astNode> P::parsePower() {
    auto base = parseUnary();

    if (current().type == tt::power) {
        consume();
        auto exponent = parsePower();
        return make_unique<binaryNode>(tt::power, std::move(base), std::move(exponent));
    }
    return base;
}
unique_ptr<astNode> P::parseTerm() {
    auto left = parsePower();

    while (current().type == tt::star ||
            current().type == tt::slash ||
            current().type == tt::percent) {
        token op = consume();
        auto right = parsePower();
        left = make_unique<binaryNode>(op.type, std::move(left), std::move(right));
    }
    return left;
}
unique_ptr<astNode> P::parseExpression() {
    auto left = parseTerm();

    while (current().type == tt::plus || current().type == tt::minus) {
        token op = consume();
        auto right = parseTerm();
        left = make_unique<binaryNode>(op.type, std::move(left), std::move(right));
    }
    return left;
}