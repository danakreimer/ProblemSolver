//
// Created by duni on 16/01/2020.
//

#ifndef PROBLEMSOLVER_SEARCHER_H
#define PROBLEMSOLVER_SEARCHER_H

#include "Searchable.h"

template <class P, class S>
class Searcher {
public:
    virtual S search (Searchable<P>* ) = 0;
    virtual int getNumberOfNodesEvaluated() = 0;
};

#endif //PROBLEMSOLVER_SEARCHER_H
