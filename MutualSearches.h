//
// Created by duni on 16/01/2020.
//

#ifndef PROBLEMSOLVER_MUTUALSEARCHES_H
#define PROBLEMSOLVER_MUTUALSEARCHES_H

#include "Searcher.h"
#include <list>
#include <hash_map>
#include <unordered_set>

using namespace std;

template <class P, class S>
class MutualSearches : public Searcher<P, S> {
private:
    list <State <P>*> openList;
    unordered_set<State<P>*> closed;
    int evaluatedNodes;
public:
    MutualSearches<P, S> () {
        this->openList = new list<State<P>> ();
        this->evaluatedNodes = 0;
        this->closed = new unordered_set<State<P>*>();
    }

    vector<State<P>*> backTrace(State<P>* start, State<P>* end) {
        vector<State<P>*> nodeTrace;
        nodeTrace.emplace(nodeTrace.begin(), start);
        State<P>* current = end->getCameFrom();
        while (!(current->Equals(start))) {
            nodeTrace.emplace(nodeTrace.begin(), current);
            current = current->getCameFrom();
        }
        nodeTrace.emplace(nodeTrace.begin(), end);
        return nodeTrace;
    };

    virtual S search (Searchable<P>* ) = 0;
    int openListSize() {
        return openList.size();
    }
    int getNumberOfNodesEvaluated() {
        return evaluatedNodes;
    }

    void addToOpenList(State <P>* s) {
        openList.emplace_back(s);
    }

    bool openContains (State<P>* s) {
        return find(this->openList.begin(), this->openList.end(), s) != this->openList.end();
    }

    void addToClosedList(State <P>* s) {
        closed.insert(s);
    }

    bool closedContains (State<P>* s) {
        return find(this->closed.begin(), this->closed.end(), s) != this->closed.end();
    }

protected:
    State <P>* popOpenList() {
        auto it = openList.begin();
        State<P>* min = openList.begin();

        for (it = openList.begin(); it != openList.end(); ++it) {
            if (it.getCost() < min->getCost()) {
                min->setCost(it.getCost());
                min->setState(it.getState());
                min->setCameFrom(*it.getCameFrom());
            }
        }

        openList.remove(min);
        evaluatedNodes++;
        return min;
    }
};


#endif //PROBLEMSOLVER_MUTUALSEARCHES_H
