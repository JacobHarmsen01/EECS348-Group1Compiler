#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <memory>
#include <stdexcept>
#include "token.h"
#include "ast.h"

using namespace std;

class Parser {
    public:
        explicit Parser(const vector<token>& tokens);
        unique_ptr<astNode> parse();
    
    private:
        vector<token> tokens;
        size_t pos;

        token current() const;
        token consume();
        token expect(tokenType type);

        unique_ptr<astNode> parseExpression(); // + , -
        unique_ptr<astNode> parseTerm(); // * , / , %
        unique_ptr<astNode> parsePower(); // **
        unique_ptr<astNode> parseUnary(); // unary
        unique_ptr<astNode> parsePrimary(); // numbers, parens
};
#endif