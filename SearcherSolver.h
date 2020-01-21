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

template <class P>
class SearcherSolver : public Solver<Searchable<P>,string> {
private:
    AlgorithmOptions<P, string>* ao;
public:
    SearcherSolver(AlgorithmOptions<P, string>* ao ) {
        this->ao = ao;
    }

    string solve(Searchable<P>* problem) {
        Searcher<P, string>* searcher = ao->getAlgorithm();
        string solution = solutionFormat(searcher->search(problem));
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
