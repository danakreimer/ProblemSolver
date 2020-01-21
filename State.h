//
// Created by duni on 16/01/2020.
//

#ifndef PROBLEMSOLVER_STATE_H
#define PROBLEMSOLVER_STATE_H

template <class T>
class State {
private:
    T state;
    double cost;
    State<T>* cameFrom;
public:
    State (T state) {
        this->state = state;
    }
    bool Equals (State<T> s) {
        return state.Equals(s.state);
    }

    int getCost() {
        return this->cost;
    }

    State<T>* getCameFrom() {
        return this->cameFrom;
    }

    void setCost (double cost) {
        this->cost = cost;
    }

    void setCameFrom(State<T>* s) {
        this->cameFrom = s;
    }

    // TODO: get back here when we figure everything out!!


};

#endif //PROBLEMSOLVER_STATE_H
