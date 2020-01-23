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
  MutualSearches<P>() {
    this->openList = new list<State<P> *>();
    this->evaluatedNodes = 0;
    this->closed = new unordered_set<State<P> *>();
  }

  vector<State<P> *> backTrace(State<P> *start, State<P> *end) {
    vector<State<P> *> nodeTrace;
    nodeTrace.emplace(nodeTrace.begin(), end);
    State<P> *current = end->getCameFrom();
    while (!(current->Equals(start))) {
      nodeTrace.emplace(nodeTrace.begin(), current);
      current = current->getCameFrom();
    }
    nodeTrace.emplace(nodeTrace.begin(), start);
    return nodeTrace;
  };

  virtual vector<State<P> *> search(Searchable<P> *) = 0;
  int openListSize() {
    return openList->size();
  }
  int getNumberOfNodesEvaluated() {
    return evaluatedNodes;
  }

  void addToOpenList(State<P> *s) {
    openList->emplace_back(s);
  }

  bool openContains(State<P> *s) {
    //auto iter = this->openList->begin();
    //auto it = find(this->openList->begin(), this->openList->end(), s) != this->openList->end();
    for (typename list<State<P> *>::iterator iter = this->openList->begin(); iter != this->openList->end(); iter++) {
      if ((*iter)->getState() == s->getState()) {
        return true;
      }
    }
    return false;
  }
  State<P> *openGetMin(State<P> *s) {
    //auto iter = this->openList->begin();
    //auto it = find(this->openList->begin(), this->openList->end(), s) != this->openList->end();
    for (typename list<State<P> *>::iterator iter = this->openList->begin(); iter != this->openList->end(); iter++) {
      if ((*iter)->getState() == s->getState()) {
        return *iter;
      }
    }
    return nullptr;
  }

  void addToClosedList(State<P> *s) {
    closed->insert(s);
  }

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
  State<P> *popOpenList() {
    State<P> *min = *openList->begin();

    for (typename list<State<P> *>::iterator it = openList->begin(); it != openList->end(); ++it) {
      if ((*it)->getCumulativeCost() < min->getCumulativeCost()) {
        min = *it;
      }
    }
    //State<P>* removeState = this->openGetMin(min);
    openList->remove(min);
    evaluatedNodes++;
    return min;
  }

  State<P> *popOpenListAstar() {
    State<P> *min = *openList->begin();

    for (typename list<State<P> *>::iterator it = openList->begin(); it != openList->end(); ++it) {
      if (((*it)->getCumulativeCost() + (*it)->getHeuristicCost())
          < (min->getCumulativeCost() + min->getHeuristicCost())) {
        min = *it;
      }
    }
    //State<P>* removeState = this->openGetMin(min);
    openList->remove(min);
    evaluatedNodes++;
    return min;
  }
};

#endif //PROBLEMSOLVER_MUTUALSEARCHES_H
