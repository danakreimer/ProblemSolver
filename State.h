//
// Created by duni on 16/01/2020.
//

#ifndef PROBLEMSOLVER_STATE_H
#define PROBLEMSOLVER_STATE_H

template<class T>
class State {
private:
    T *state;
    double cost = 0;
    double cumulativeCost = 0;
    State<T> *cameFrom = nullptr;
    double heuristicCost = 0;
public:

    // This is a constructor function
    State(double cost, T *state) {
        this->cost = cost;
        this->state = state;
        this->cumulativeCost = cost;
    }

    // This function checks if two states - of a given node and the current node, are equal
    bool Equals(State<T> *s) {
        return state->Equals(s->state);
    }

    // This function returns the cost of a current node
    double getCost() {
        return this->cost;
    }

    // This function returns the previous node to the current node
    State<T> *getCameFrom() {
        return this->cameFrom;
    }

    // This function sets the cost of a current node
    void setCost(double cost) {
        this->cost = cost;
    }

    // This function sets the previous node to the current node
    void setCameFrom(State<T> *s) {
        this->cameFrom = s;
    }

    // This function returns the state of the current node
    T *getState() {
        return this->state;
    }

    // This function sets the state of the current node
    void setState(T *state) {
        this->state = state;
    }

    // This function returns the cumulative cost of the current node
    double getCumulativeCost() {
        return this->cumulativeCost;
    }

    // This function sets the cumulative cost of the current node
    void setCumulativeCost(double cumulativeCost) {
        this->cumulativeCost = cumulativeCost;
    }

    // This function returns the heuristic cost of the current node
    double getHeuristicCost() {
        return this->heuristicCost;
    }

    // This function sets the heuristic cost of the current node
    void setHeuristicCost(double heuristicCost) {
        this->heuristicCost = heuristicCost;
    }

    // This function preforms a placement of a given node to the current node
    State<T> &operator=(const State<T> &other) {
        this->cost = other.getCost();
        this->state = other.getState();
        this->cameFrom = other.getCameFrom();
        this->cumulativeCost = other.getCumulativeCost();
        this->heuristicCost = other.getHeuristicCost();
        return *this;
    }
};

#endif //PROBLEMSOLVER_STATE_H
