//
// Created by duni on 16/01/2020.
//

#ifndef PROBLEMSOLVER_SEARCHABLE_H
#define PROBLEMSOLVER_SEARCHABLE_H

#include "State.h"
#include <list>

using namespace std;

template <class T>
class Searchable {
public:
    virtual State<T>* getInitialState() = 0;
    virtual State<T>* getGoalState() = 0;
    virtual list<State<T>*>* getAllPossibleStates (State<T>* s) = 0;
    virtual double getDistance(State<T>*,State<T>* ) = 0;
};

#endif //PROBLEMSOLVER_SEARCHABLE_H
