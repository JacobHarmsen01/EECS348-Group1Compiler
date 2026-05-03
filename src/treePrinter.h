#ifndef TREEPRINTER_H
#define TREEPRINTER_H

#include <string>
#include <vector>
#include "ast.h"
#include "token.h"

using namespace std;

// Terminal output colors
namespace Colors {
    const string Reset   = "\033[0m";
    const string Bold    = "\033[1m";
    const string Crimson = "\033[38;5;196m";
    const string Teal    = "\033[38;5;43m";
    const string Amber   = "\033[38;5;214m";
    const string Coral   = "\033[38;5;209m";
    const string Purple  = "\033[38;5;141m";
    const string Green   = "\033[38;5;84m";
    const string Red     = "\033[38;5;160m";
    const string White   = "\033[38;5;252m";
}
// Print tree
void printTree(const astNode* node, const string& prefix = "", bool isLast = true);

// Token stream to tree
void printTokens(const vector<token>& tokens);

// UI stuff
void printDivider(char c = '-', int width = 60);
void printHeader();
void printResult(double val, const string& msg);

#endif


