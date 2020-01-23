//
// Created by duni on 12/01/2020.
//

#ifndef PROBLEMSOLVER_SOLVER_H
#define PROBLEMSOLVER_SOLVER_H

#include <string>

using namespace std;

template<class Problem, class Solution>
class Solver {
 public:
  virtual Solution solve(Problem *) = 0;
  virtual string getName() = 0;
};

#endif //PROBLEMSOLVER_SOLVER_H
