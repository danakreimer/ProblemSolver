//
// Created by duni on 21/01/2020.
//

#ifndef PROBLEMSOLVER_SEARCHERSOLVER_H
#define PROBLEMSOLVER_SEARCHERSOLVER_H

#include "Solver.h"
#include "AlgorithmOptions.h"
#include "Point.h"
#include <string>
#include <string.h>
#include <stdlib.h>

template <class P, class S>
class SearcherSolver : public Solver<P, S> {
private:
    AlgorithmOptions<P, S>* ao;
public:
    SearcherSolver(AlgorithmOptions<P, S>* ao ) {
        this->ao = ao;
    }

    S solve(P problem) {
        Searcher<P, S>* searcher = ao->getAlgorithm();
        S solution = solutionFormat(searcher->search(problem));
        return solution;
    }

    string getName(){
        return ao->getAlgorithmName();
    }

    string solutionFormat (vector<State<Point>>* solution) {
        string strSolution = "";
        string direction;
        basic_string<char> cost;
        int x;
        int y;
        auto it = solution->begin();

        for(it = solution->begin(); it != solution->end() - 1; it++) {
            auto next = it++;
            if (it->getState()->getX() + 1 == next->getState()->getX()) {
                strSolution += "Right";
            }
            if (it->getState()->getX() - 1 == next->getState()->getX()) {
                strSolution += "Left";
            }
            if (it->getState()->getY() + 1 == next->getState()->getY()) {
                strSolution += "Down";
            }
            if (it->getState()->getY() - 1 == next->getState()->getY()) {
                strSolution += "Up";
            }

            cost = to_string(it->getCost());
            strSolution = strSolution + " " + "(" + cost + ")" + ", ";
        }
        return strSolution;
    }
};

#endif //PROBLEMSOLVER_SEARCHERSOLVER_H
