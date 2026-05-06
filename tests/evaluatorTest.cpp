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