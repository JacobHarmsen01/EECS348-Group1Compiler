#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <cmath>
#include <stdexcept>
#include "ast.h"
#include "token.h"

using namespace std;

class Evaluator {
    public:
        double evaluate(const astNode* node);
};
#endif