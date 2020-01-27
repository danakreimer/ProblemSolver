//
// Created by duni on 16/01/2020.
//

#ifndef PROBLEMSOLVER_MUTUALSEARCHES_H
#define PROBLEMSOLVER_MUTUALSEARCHES_H

#include "Searcher.h"
#include <list>
//#include <hash_map>
#include <unordered_set>

using namespace std;

template<class P>
class MutualSearches : public Searcher<P> {
private:
    list<State<P> *> *openList;
    unordered_set<State<P> *> *closed;
    int evaluatedNodes;
public:

    // The Constructor
    MutualSearches<P>() {
        this->openList = new list<State<P> *>();
        this->evaluatedNodes = 0;
        this->closed = new unordered_set<State<P> *>();
    }

    // Returns the back trace of the path from state start to state end
    vector<State<P> *> backTrace(State<P> *start, State<P> *end) {
        vector<State<P> *> nodeTrace;
        // Push the end state
        nodeTrace.emplace(nodeTrace.begin(), end);
        // The current state is the "cameFrom" state of the end state
        State<P> *current = end->getCameFrom();
        // The loop runs until it gets to the start state
        while (!(current->Equals(start))) {
            // Pudh the current state to the vector
            nodeTrace.emplace(nodeTrace.begin(), current);
            current = current->getCameFrom();
        }
        // Push the start state to the vector
        nodeTrace.emplace(nodeTrace.begin(), start);
        return nodeTrace;
    };

    virtual vector<State<P> *> search(Searchable<P> *) = 0;

    // Returns the size of the open list
    int openListSize() {
        return openList->size();
    }

    // Returns the number of nodes evaluated
    int getNumberOfNodesEvaluated() {
        return evaluatedNodes;
    }

    // Adds the state to the open list
    void addToOpenList(State<P> *s) {
        openList->emplace_back(s);
    }

    // Checks if the open list contains the given state
    bool openContains(State<P> *s) {
        for (typename list<State<P> *>::iterator iter = this->openList->begin();
             iter != this->openList->end(); iter++) {
            if ((*iter)->getState() == s->getState()) {
                return true;
            }
        }
        return false;
    }

    // Adds the given state to the closed list
    void addToClosedList(State<P> *s) {
        closed->insert(s);
    }

    // Checks if the closed list contains the given state
    bool closedContains(State<P> *s) {
        for (typename unordered_set<State<P> *>::iterator iter = this->closed->begin(); iter != this->closed->end();
             iter++) {
            if ((*iter)->getState() == s->getState()) {
                return true;
            }
        }
        return false;
    }

protected:

    // The function pop the open list
    State<P> *popOpenList() {
        // Initialize the min state
        State<P> *min = *openList->begin();
        for (typename list<State<P> *>::iterator it = openList->begin(); it != openList->end(); ++it) {
            // Checks id the cumulative cost of the current state is smaller than the cumulative cost of min state
            if ((*it)->getCumulativeCost() < min->getCumulativeCost()) {
                min = *it;
            }
        }
        openList->remove(min);
        evaluatedNodes++;
        return min;
    }

    // The function pop the open list of Astar algorithm
    State<P> *popOpenListAstar() {
        // Initialize the min state
        State<P> *min = *openList->begin();
        for (typename list<State<P> *>::iterator it = openList->begin(); it != openList->end(); ++it) {
            // Checks id the f value (g+h) of the current state is smaller than the f value (g+h) of min state
            if (((*it)->getCumulativeCost() + (*it)->getHeuristicCost())
                < (min->getCumulativeCost() + min->getHeuristicCost())) {
                min = *it;
            }
        }
        openList->remove(min);
        evaluatedNodes++;
        return min;
    }
};

#endif //PROBLEMSOLVER_MUTUALSEARCHES_H
