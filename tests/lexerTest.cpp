#include <iostream>
#include "../source/lexer.h"

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