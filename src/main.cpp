#include <iostream>
#include <string>
#include <cmath>

#include "lexer.h"
#include "parser.h"
#include "evaluator.h"
#include "printer.h"

using namespace std;

void evaluate(const string& input) {
    cout << "\n";
    printDivider('*', 60);

    try {
        Lexer lex(input);
        vector<token> tokens = lex.tokenize();
        printTokens(tokens);

        Parser parser(tokens);
        unique_ptr<astNode> tree = parser.parse();

        Evaluator eval;
        double val = eval.evaluate(tree.get());

        if (isinf(val)) { printError("overflow - result too large to represent (exceeds 10^12)"); return; }
        if (isinf(val)) { printError("undefined - not a number"); return; }

        printResult(val, input);

        cout << Colors::White << "  ast\n\n" << Colors::Reset;
        printTree(tree.get(), " ");
        cout << "\n";

    } catch (const runtime_error& e) {
        printError(e.what());
    }
}
int main(int argc, char* argv[]) {
    printHeader();

    // Single Expression Mode - ./exprparser "x + y * z"
    if (argc > 1) {
        string expr;
        for (int i = 1; i < argc; i++) {
            if (i > 1) expr += " ";
            expr += argv[i];
        }
        evaluate(expr);
        printDivider('-', 60);
        cout << "\n";
        return 0;
    }
    // Continuous run Mode
    cout << Colors::White
         << "   enter an expression or 'exit' to quit\n"
         << "   operators: + - * / % ** ( )\n\n"
         << Colors::Reset;

    string input;
    while (true) {
        cout << Colors::Bold << Colors::Crimson << " > " << Colors::Reset;
        if (!getline(cin, input)) break;
        if (input == "exit" || input == "quit" || input == "q") break;
        if (input.empty()) continue;
        evaluate(input);
    }
    printDivider('-', 60);
    cout << Colors::White << "  Goodbye!\n" << Colors::Reset << "\n";
    return 0;
}