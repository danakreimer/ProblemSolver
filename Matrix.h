//
// Created by duni on 21/01/2020.
//

#ifndef PROBLEMSOLVER_MATRIX_H
#define PROBLEMSOLVER_MATRIX_H


#include "Searchable.h"
#include "Point.h"
#include <vector>

class Matrix : public Searchable<Point> {
private:
    State<Point>* initialState;
    State<Point>* goalState;
    vector <State<Point>>* matrix;
    int numOfRows = 0;
    int numOfColumns = 0;
public:
    Matrix (vector<vector<double >>, Point*, Point*);
    State<Point>* getInitialState() override;
    State<Point>* getGoalState() override;
    list<State<Point>*>* getAllPossibleStates (State<Point>* s);
};


#endif //PROBLEMSOLVER_MATRIX_H
