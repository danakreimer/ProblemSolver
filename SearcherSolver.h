//
// Created by duni on 21/01/2020.
//

#ifndef PROBLEMSOLVER_SEARCHERSOLVER_H
#define PROBLEMSOLVER_SEARCHERSOLVER_H

#include "Solver.h"
#include "AlgorithmOptions.h"
#include "Point.h"
#include <string>
#include <iostream>

template <class P>
class SearcherSolver : public Solver<Searchable<P>,string> {
private:
    AlgorithmOptions<P>* ao;
public:
    SearcherSolver(AlgorithmOptions<P>* ao ) {
        this->ao = ao;
    }

    string solve(Searchable<P>* problem) {
        Searcher<P>* searcher = ao->getAlgorithm();
        vector<State<Point>*> vec = searcher->search(problem);
        string solution = solutionFormat(vec);
        return solution;
    }

    string getName(){
        return ao->getAlgorithmName();
    }

    string solutionFormat (vector<State<Point>*> solution) {
        string strSolution = "";
        string direction;
        string strToSend ="";
        basic_string<char> cost;
        int x;
        int y;
        auto it = solution.begin();

        for(it = solution.begin(); it != solution.end() - 1; it++) {
            auto next = it + 1;
            if ((*it)->getState()->getX() + 1 == (*next)->getState()->getX()) {
                strSolution += "Down";
            }
            if ((*it)->getState()->getX() - 1 == (*next)->getState()->getX()) {
                strSolution += "Up";
            }
            if ((*it)->getState()->getY() + 1 == (*next)->getState()->getY()) {
                strSolution += "Right";
            }
            if ((*it)->getState()->getY() - 1 == (*next)->getState()->getY()) {
                strSolution += "Left";
            }

            cost = to_string((*next)->getCumulativeCost());
            strSolution +=" ";
            strSolution+= "(" + cost + ")" + ", ";
        }
        strToSend = strSolution.substr(0, strSolution.size()-2);
        return strToSend;
    }
};

#endif //PROBLEMSOLVER_SEARCHERSOLVER_H
