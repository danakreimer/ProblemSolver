//
// Created by duni on 21/01/2020.
//

#include "Matrix.h"

Matrix::Matrix(vector<vector<double>> matrixVec, Point* start, Point* end) {
    this->numOfRows = matrixVec.size();
    this->numOfColumns = matrixVec[0].size();

    int currCell = 0;
    int i;
    int j;
    for (i = 0; i < numOfRows; i++) {
        for (j = 0; j < numOfColumns; j++) {
            Point* pointCurr = new Point(i, j);
            this->matrix->at(currCell).setCost(matrixVec.at(i).at(j));
            this->matrix->at(currCell).getState()->setPoint(pointCurr);
            if (start == pointCurr) {
                this->initialState->setCost(matrixVec.at(i).at(j));
                this->initialState->getState()->setPoint(pointCurr);
            }
            if (end == pointCurr) {
                this->goalState->setCost(matrixVec.at(i).at(j));
                this->goalState->getState()->setPoint(pointCurr);
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

    if (y != this->numOfColumns - 1) {
        State<Point>* neighborRight = &matrix->at(currCell + 1);
        if (neighborRight->getCost() != -1) {
            neighbors->push_back(neighborRight);
        }
    }

    if (y != 0) {
        State<Point>* neighborLeft = &matrix->at(currCell - 1);
        if (neighborLeft->getCost() != -1) {
            neighbors->push_back(neighborLeft);
        }
    }

    if (x != 0) {
        State<Point>* neighborUp = &matrix->at(currCell - numOfColumns);
        if (neighborUp->getCost() != -1) {
            neighbors->push_back(neighborUp);
        }
    }

    if (x != 0) {
        State<Point>* neighborDown = &matrix->at(currCell + numOfColumns);
        if (neighborDown->getCost() != -1) {
            neighbors->push_back(neighborDown);
        }
    }

    return neighbors;
}


