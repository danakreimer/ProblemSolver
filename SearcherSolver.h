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

template<class P>
class SearcherSolver : public Solver<Searchable<P>, string> {
private:
    AlgorithmOptions<P> *ao;
public:

    // This is a constructor function
    SearcherSolver(AlgorithmOptions<P> *ao) {
        this->ao = ao;
    }

    // This function activates the suitable algorithm for the given problem
    string solve(Searchable<P> *problem) {
        Searcher<P> *searcher = ao->getAlgorithm();
        vector<State<Point> *> vec = searcher->search(problem);
        // Send the solution to be modified into the wanted solution format
        string solution = solutionFormat(vec);
        return solution;
    }

    // This function returns the algorithm name that solved the problem
    string getName() {
        return ao->getAlgorithmName();
    }

    // This function returns the given solution in the right format to print it with
    string solutionFormat(vector<State<Point> *> solution) {
        string strSolution = "";
        string direction;
        string strToSend = "";
        basic_string<char> cost;
        int x;
        int y;
        auto it = solution.begin();

        // Go through the entire solution
        for (it = solution.begin(); it != solution.end() - 1; it++) {
            // Get the next node because the comparison is always done between the current node and the next one
            auto next = it + 1;
            // Calculate the node which is located beneath the current one
            if ((*it)->getState()->getX() + 1 == (*next)->getState()->getX()) {
                strSolution += "Down";
            }

            // Calculate the node which is located above the current one
            if ((*it)->getState()->getX() - 1 == (*next)->getState()->getX()) {
                strSolution += "Up";
            }

            // Calculate the node which is located to right of the current one
            if ((*it)->getState()->getY() + 1 == (*next)->getState()->getY()) {
                strSolution += "Right";
            }

            // Calculate the node which is located to left of the current one
            if ((*it)->getState()->getY() - 1 == (*next)->getState()->getY()) {
                strSolution += "Left";
            }

            cost = to_string((*next)->getCumulativeCost());
            strSolution += " ";
            strSolution += "(" + cost + ")" + ", ";
        }
        strToSend = strSolution.substr(0, strSolution.size() - 2);
        return strToSend;
    }
};

#endif //PROBLEMSOLVER_SEARCHERSOLVER_H
