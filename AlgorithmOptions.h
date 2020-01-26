//
// Created by duni on 21/01/2020.
//

#ifndef PROBLEMSOLVER_ALGORYTHEMOPTIONS_H
#define PROBLEMSOLVER_ALGORYTHEMOPTIONS_H

#include <string>
#include "BestFirstSearch.h"
# include "Astar.h"
#include "BFS.h"
#include "DFS.h"

using namespace std;

template<class P>
class AlgorithmOptions {
private:
    string algorithmName;
public:
    // This is a constructor function
    AlgorithmOptions(string algorithmName) {
        this->algorithmName = algorithmName;
    }

    // This function returns the suitable algorithm for the given problem
    Searcher<P> *getAlgorithm() {
        if (algorithmName.compare("BFS") == 0) {
            return new BFS<P>;
        }
        if (algorithmName.compare("DFS") == 0) {
            return new DFS<P>;
        }
        if (algorithmName.compare("Astar") == 0) {
            return new Astar<P>;
        }
        if (algorithmName.compare("BestFirstSearch") == 0) {
            return new BestFirstSearch<P>;
        }
    }

    // This function returns the name of the algorithm that solved the problem
    string getAlgorithmName() {
        return this->algorithmName;
    }
};

#endif //PROBLEMSOLVER_ALGORYTHEMOPTIONS_H
