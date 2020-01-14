//
// Created by duni on 12/01/2020.
//

#ifndef PROBLEMSOLVER_SOLVER_H
#define PROBLEMSOLVER_SOLVER_H
template <class Problem, class Solution>
        class Solver {
virtual Solution solve (Problem) = 0;
};

#endif //PROBLEMSOLVER_SOLVER_H
