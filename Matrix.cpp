//
// Created by duni on 21/01/2020.
//

#include <iostream>
#include "Matrix.h"

Matrix::Matrix(vector<vector<double>>* matrixVec, Point* start, Point* end) {
    this->numOfRows = matrixVec->size();
    this->numOfColumns = matrixVec->at(0).size();
    matrix = new vector <State<Point>*>();
    int currCell = 0;
    int i;
    int j;
    for (i = 0; i < numOfRows; i++) {
        for (j = 0; j < numOfColumns; j++) {
            auto* pointCurr = new Point(i, j);
//            cout << "matrixVec[" << i << ", " << j << "] = " << matrixVec->at(i).at(j) << endl;
            auto* matrixState = new State<Point>(matrixVec->at(i).at(j),pointCurr);
            //matrixState->setCost(matrixVec->at(i).at(j));
            this->matrix->emplace_back(matrixState);

            if (*start == *pointCurr) {

                this->initialState = matrixState;
            }
            if (*end == *pointCurr) {
              this->goalState = matrixState;
            }

            currCell++;
        }
    }
}

State<class Point> * Matrix::getInitialState() {
    return this->initialState;
}

State<class Point> * Matrix::getGoalState() {
    return this->goalState;
}

list<State<class Point> *> * Matrix::getAllPossibleStates(State<class Point> * s) {
    auto * neighbors = new list<State<class Point> *> ();
    int x = s->getState()->getX();
    int y = s->getState()->getY();

    int currCell = x*this->numOfColumns + y;

    if (x != 0) {
        State<Point>* neighborUp = matrix->at(currCell - numOfColumns);
        if (neighborUp->getCost() != -1) {
            neighbors->push_back(neighborUp);
        }
    }

    if (y != 0) {
        State<Point>* neighborLeft = matrix->at(currCell - 1);
        if (neighborLeft->getCost() != -1) {
            neighbors->push_back(neighborLeft);
        }
    }

    if (x != this->numOfRows - 1) {
        State<Point>* neighborDown = matrix->at(currCell + numOfColumns);
        if (neighborDown->getCost() != -1) {
            neighbors->push_back(neighborDown);
        }
    }

    if (y != this->numOfColumns - 1) {
        State<Point>* neighborRight = matrix->at(currCell + 1);
        if (neighborRight->getCost() != -1) {
            neighbors->push_back(neighborRight);
        }
    }

    return neighbors;
}

double Matrix::getDistance(State<Point> *state1,State<Point> *state2) {
    double xDistance = abs(state1->getState()->getX() - state2->getState()->getX());
    double yDistance = abs(state1->getState()->getY() - state2->getState()->getY());
    return sqrt(pow(xDistance,2)+pow(yDistance,2));
}


