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
    type(type), value(move(value)), position(position) {}
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