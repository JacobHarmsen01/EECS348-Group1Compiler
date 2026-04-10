#ifndef AST_H
#define AST_H

#include <memory>
#include "token.h"

using namespace std;

struct astNode {
    virtual ~astNode() = default;
};
struct numberNode : astNode {
    double value;

    explicit numberNode(double value) : value(value) {}
};
struct unaryNode : astNode {
    tokenType op;
    unique_ptr<astNode> operand;

    unaryNode(tokenType op, unique_ptr<astNode> operand) :
            op(op), operand(move(operand)) {}
};
struct binaryNode : astNode {
    tokenType op;
    unique_ptr<astNode> left;
    unique_ptr<astNode> right;

    binaryNode(tokenType op, unique_ptr<astNode> left,
               unique_ptr<astNode> right)
        : op(op), left(move(left)), right(move(right)) {}
};
#endif