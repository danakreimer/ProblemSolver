//
// Created by duni on 21/01/2020.
//

#ifndef PROBLEMSOLVER_ALGORYTHEMOPTIONS_H
#define PROBLEMSOLVER_ALGORYTHEMOPTIONS_H

#include <string>
#include "BestFirstSearch.h"
# include "Astar.h"
using namespace std;

template <class P>
class AlgorithmOptions {
private:
    string algorithmName;
public:
    AlgorithmOptions(string algorithmName) {
        this->algorithmName = algorithmName;
    }

    Searcher<P>* getAlgorithm () {
        if (algorithmName.compare("BFS") == 0) {
            return nullptr;
        }
        if (algorithmName.compare("DFS") == 0) {
            return nullptr;
        }
        if (algorithmName.compare("Astar") == 0) {
            return new Astar<P>;
        }
        if (algorithmName.compare("BestFirstSearch") == 0) {
            return new BestFirstSearch<P>;
        }
    }

    string getAlgorithmName () {
        return this->algorithmName;
    }
};

#endif //PROBLEMSOLVER_ALGORYTHEMOPTIONS_H
