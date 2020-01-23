//
// Created by duni on 16/01/2020.
//

#ifndef PROBLEMSOLVER_STATE_H
#define PROBLEMSOLVER_STATE_H

template <class T>
class State {
private:
    T* state;
    double cost = 0;
    double cumulativeCost = 0;
    State<T>* cameFrom = nullptr;
    double heuristicCost = 0;
public:

    State(double cost, T *state){
      this->cost = cost;
      this->state = state;
      this->cumulativeCost = cost;
    }
    bool Equals (State<T>* s) {
        return state->Equals(s->state);
    }

    double getCost() {
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

    T* getState () {
        return this->state;
    }

    void setState (T* state) {
        this->state = state;
    }

    double getCumulativeCost(){
      return this->cumulativeCost;
    }

    void setCumulativeCost(double cumulativeCost){
      this->cumulativeCost = cumulativeCost;
    }

    double getHeuristicCost(){
      return this->heuristicCost;
    }

    void setHeuristicCost(double heuristicCost){
      this->heuristicCost = heuristicCost;
    }

    State<T>& operator= (const State<T> &other)  {
    this->cost = other.getCost();
    this->state = other.getState();
    this->cameFrom = other.getCameFrom();
    this->cumulativeCost = other.getCumulativeCost();
    this->heuristicCost = other.getHeuristicCost();
    return *this;
  }


    // TODO: get back here when we figure everything out!!

};

#endif //PROBLEMSOLVER_STATE_H
