//
// Created by duni on 14/01/2020.
//

#ifndef PROBLEMSOLVER_STRINGREVERSE_H
#define PROBLEMSOLVER_STRINGREVERSE_H

#include "Solver.h"
#include <string>

using namespace std;

class StringReverse : public Solver<string, string> {
public:
    string solve (string) override;
};


#endif //PROBLEMSOLVER_STRINGREVERSE_H
