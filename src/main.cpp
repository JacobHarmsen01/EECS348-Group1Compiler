#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <sstream>
#include <iomanip>
#include <cmath>

#include "lexer.h"
#include "parser.h"
#include "evaluator.h"

using namespace std;

// ─── ANSI Colors ──────────────────────────────────────────────────────────────
namespace Colors {
    const string Reset   = "\033[0m";
    const string Bold    = "\033[1m";
    const string Dim     = "\033[2m";

    // Foreground colors
    const string Red     = "\033[38;5;160m";
    const string Crimson = "\033[38;5;196m";
    const string Teal    = "\033[38;5;43m";
    const string Amber   = "\033[38;5;214m";
    const string Coral   = "\033[38;5;209m";
    const string Purple  = "\033[38;5;141m";
    const string Green   = "\033[38;5;84m";
    const string Blue    = "\033[38;5;75m";
    const string Gray    = "\033[38;5;240m";
    const string White   = "\033[38;5;252m";
    const string Muted   = "\033[38;5;238m";
}

// ─── Tree Printing ────────────────────────────────────────────────────────────
struct TreeLine {
    string prefix;
    string connector;
    string label;
    string sublabel;
    string labelColor;
    string subColor;
};

string nodeColor(const astNode* node) {
    if (dynamic_cast<const numberNode*>(node)) return ANSI::Teal;
    if (dynamic_cast<const unaryNode*>(node))  return ANSI::Coral;
    if (dynamic_cast<const binaryNode*>(node)) return ANSI::Amber;
    return ANSI::White;
}

string nodeLabel(const astNode* node) {
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

string nodeType(const astNode* node) {
    if (dynamic_cast<const numberNode*>(node)) return "num";
    if (dynamic_cast<const unaryNode*>(node))  return "unary";
    if (dynamic_cast<const binaryNode*>(node)) return "binary";
    return "";
}

vector<const astNode*> getChildren(const astNode* node) {
    vector<const astNode*> ch;
    if (const auto* n = dynamic_cast<const unaryNode*>(node)) {
        if (n->operand) ch.push_back(n->operand.get());
    } else if (const auto* n = dynamic_cast<const binaryNode*>(node)) {
        if (n->left)  ch.push_back(n->left.get());
        if (n->right) ch.push_back(n->right.get());
    }
    return ch;
}

void printTree(const astNode* node, const string& prefix = "", bool isLast = true) {
    if (!node) return;

    string connector  = isLast ? "└── " : "├── ";
    string childPfx   = prefix + (isLast ? "    " : "│   ");
    string color      = nodeColor(node);
    string label      = nodeLabel(node);
    string type       = nodeType(node);

    // Node line
    cout << ANSI::White << prefix << connector << ANSI::Reset
         << ANSI::Bold << color << label << ANSI::Reset
         << ANSI::White << ANSI::White << "  " << type << ANSI::Reset
         << "\n";

    auto children = getChildren(node);
    for (size_t i = 0; i < children.size(); i++)
        printTree(children[i], childPfx, i == children.size() - 1);
}

// ─── Token color ──────────────────────────────────────────────────────────────
string tokenColor(tokenType t) {
    using tt = tokenType;
    switch (t) {
        case tt::number:  return ANSI::Teal;
        case tt::plus:
        case tt::minus:   return ANSI::Green;
        case tt::star:
        case tt::slash:
        case tt::percent: return ANSI::Amber;
        case tt::power:   return ANSI::Coral;
        case tt::lParen:
        case tt::rParen:  return ANSI::Purple;
        case tt::end:     return ANSI::White;
    }
    return ANSI::White;
}

// ─── UI Helpers ───────────────────────────────────────────────────────────────
void printDivider(char c = '-', int width = 60) {
    cout << ANSI::Muted;
    for (int i = 0; i < width; i++) cout << c;
    cout << ANSI::Reset << "\n";
}

void printHeader() {
    cout << "\n";
    printDivider('-', 60);
    cout << ANSI::Bold << ANSI::Crimson << "  expr" << ANSI::Reset
         << ANSI::Bold << ANSI::White   << "parser" << ANSI::Reset
         << ANSI::White  << ANSI::White    << "  arithmetic expression evaluator\n" << ANSI::Reset;
    printDivider('-', 60);
    cout << "\n";
}

void printTokens(const vector<token>& tokens) {
    cout << ANSI::White << ANSI::White << "  tokens  " << ANSI::Reset;
    for (const auto& t : tokens) {
        if (t.type == tokenType::end) break;
        string col = tokenColor(t.type);
        cout << col << ANSI::Bold << tokenTypeName(t.type) << ANSI::Reset;
        if (!t.value.empty() && t.value != tokenTypeName(t.type))
            cout << ANSI::White << "(" << t.value << ")" << ANSI::Reset;
        cout << " ";
    }
    cout << "\n\n";
}

void printResult(double val, const string& expr) {
    // Format
    ostringstream ss;
    if (val == (long long)val && abs(val) < 1e12)
        ss << (long long)val;
    else
        ss << fixed << setprecision(8) << val;

    cout << ANSI::White << ANSI::White << "  result  " << ANSI::Reset
         << ANSI::White << ANSI::White << expr << ANSI::Reset
         << ANSI::White << "  =  " << ANSI::Reset
         << ANSI::Bold << ANSI::Green << ss.str() << ANSI::Reset
         << "\n\n";
}

void printError(const string& msg) {
    cout << "\n"
         << ANSI::Bold << ANSI::Red << "  error  " << ANSI::Reset
         << ANSI::White << msg << ANSI::Reset
         << "\n\n";
}

void evaluate(const string& input) {
    cout << "\n";
    printDivider('*', 60);

    try {
        // Lex
        Lexer lex(input);
        vector<token> tokens = lex.tokenize();
        printTokens(tokens);

        // Parse
        Parser parser(tokens);
        unique_ptr<astNode> tree = parser.parse();

        // Evaluate
        Evaluator eval;
        double val = eval.evaluate(tree.get());

        if (isinf(val)) {
            printError("overflow — result too large to represent");
            return;
        }
        if (isnan(val)) {
            printError("undefined — result is not a number");
            return;
        }

        printResult(val, input);

        // Tree
        cout << ANSI::White << ANSI::White << "  ast\n\n" << ANSI::Reset;
        cout << "  ";
        printTree(tree.get(), "  ");
        cout << "\n";

    } catch (const runtime_error& e) {
        printError(e.what());
    }
}

// ─── Main ─────────────────────────────────────────────────────────────────────
int main(int argc, char* argv[]) {
    printHeader();

    // Single expression mode: ./parser "2 + 3 * 4"
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

    // REPL mode
    cout << ANSI::White << ANSI::White
         << "  Enter an expression or type 'exit' to quit\n"
         << "  operators: + - * / % ** and parentheses\n\n"
         << ANSI::Reset;

    string input;
    while (true) {
        cout << ANSI::Bold << ANSI::Crimson << "  > " << ANSI::Reset;
        if (!getline(cin, input)) break;
        if (input == "quit" || input == "exit" || input == "q") break;
        if (input.empty()) continue;
        evaluate(input);
    }

    printDivider('-', 60);
    cout << ANSI::White << ANSI::White << "  goodbye\n" << ANSI::Reset << "\n";
    return 0;
}