#include <iostream>
#include "../source/lexer.h"
#include "../source/parser.h"

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