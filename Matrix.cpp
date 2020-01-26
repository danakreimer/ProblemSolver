//
// Created by duni on 21/01/2020.
//

#include "Matrix.h"

// The constructor of Matrix class
Matrix::Matrix(vector<vector<double>> *matrixVec, Point *start, Point *end) {
  this->numOfRows = matrixVec->size();
  this->numOfColumns = matrixVec->at(0).size();
  matrix = new vector<State<Point> *>();
  int currCell = 0;
  int i;
  int j;
  // Goes over thr matrixVec
  for (i = 0; i < numOfRows; i++) {
    for (j = 0; j < numOfColumns; j++) {
      // Creates new Point with x = i and y = j
      auto *pointCurr = new Point(i, j);
      // Creates new State with the cost from the matrixVec and the new point
      auto *matrixState = new State<Point>(matrixVec->at(i).at(j), pointCurr);
      // Push the new state to the Matrix
      this->matrix->emplace_back(matrixState);
      // Checks if the current point is the start state
      if (*start == *pointCurr) {
        this->initialState = matrixState;
      }
      // Checks if the current point is the end state
      if (*end == *pointCurr) {
        this->goalState = matrixState;
      }
      currCell++;
    }
  }
}

// The function returns the initial state
State<class Point> *Matrix::getInitialState() {
  return this->initialState;
}

// The function returns the goal state
State<class Point> *Matrix::getGoalState() {
  return this->goalState;
}

// The function returns a list of the neighbors of a given point
list<State<class Point> *> *Matrix::getAllPossibleStates(State<class Point> *s) {
  auto *neighbors = new list<State<class Point> *>();
  int x = s->getState()->getX();
  int y = s->getState()->getY();
  // Calculates the current cell in the Matrix
  int currCell = x * this->numOfColumns + y;
  // Checks if the point is not in the first row of the Matrix
  if (x != 0) {
    State<Point> *neighborUp = matrix->at(currCell - numOfColumns);
    // Checks if the neighbor is a wall
    if (neighborUp->getCost() != -1) {
      neighbors->push_back(neighborUp);
    }
  }

  // Checks if the point is not in the first column of the Matrix
  if (y != 0) {
    State<Point> *neighborLeft = matrix->at(currCell - 1);
    // Checks if the neighbor is a wall
    if (neighborLeft->getCost() != -1) {
      neighbors->push_back(neighborLeft);
    }
  }

  // Checks if the point is not in the last row of the Matrix
  if (x != this->numOfRows - 1) {
    State<Point> *neighborDown = matrix->at(currCell + numOfColumns);
    // Checks if the neighbor is a wall
    if (neighborDown->getCost() != -1) {
      neighbors->push_back(neighborDown);
    }
  }

  // Checks if the point is not in the last column of the Matrix
  if (y != this->numOfColumns - 1) {
    State<Point> *neighborRight = matrix->at(currCell + 1);
    // Checks if the neighbor is a wall
    if (neighborRight->getCost() != -1) {
      neighbors->push_back(neighborRight);
    }
  }
  return neighbors;
}

// The function returns the distance between two points
double Matrix::getDistance(State<Point> *state1, State<Point> *state2) {
  double xDistance = abs(state1->getState()->getX() - state2->getState()->getX());
  double yDistance = abs(state1->getState()->getY() - state2->getState()->getY());
  return sqrt(pow(xDistance, 2) + pow(yDistance, 2));
}