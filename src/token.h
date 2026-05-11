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

*** token.h ***

*/

#ifndef TOKEN_H
#define TOKEN_H
#include <string>

using namespace std;

enum class tokenType {
    number,
    plus,
    minus,
    star,
    slash,
    percent,
    power,
    lParen,
    rParen,
    end
};
struct token {
    tokenType type;
    string value;
    size_t position;

    token(tokenType type, string value, size_t position) :
    type(type), value(std::move(value)), position(position) {}
};
inline const char* tokenTypeName(tokenType type) {
    using t = tokenType;
    switch (type) {
        case t::number: return "number";
        case t::plus: return "+";
        case t::minus: return "-";
        case t::star: return "*";
        case t::slash: return "/";
        case t::percent: return "%";
        case t::power: return "**";
        case t::lParen: return "(";
        case t::rParen: return ")";
        case t::end: return "end";
    }
    return "Unknown";
}

#endif