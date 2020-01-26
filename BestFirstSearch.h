//
// Created by duni on 16/01/2020.
//

#ifndef PROBLEMSOLVER_BESTFIRSTSEARCH_H
#define PROBLEMSOLVER_BESTFIRSTSEARCH_H

#include "MutualSearches.h"

template<class Problem>
class BestFirstSearch : public MutualSearches<Problem> {
 private:
  int numberOfNodesEvaluated = 0;
 public:
  // The function returns the back trace of the cheapest path from start state to end state
  vector<State<Problem> *> search(Searchable<Problem> *searchable) {
    // Adds the initial state to the open list
    this->addToOpenList(searchable->getInitialState());
    while (this->openListSize() > 0) {
      // Pop the open list to state n
      State<Problem> *n = this->popOpenList();
      // adds n to closed list
      this->addToClosedList(n);
      // Checks if n is the goal state
      if (n->Equals(searchable->getGoalState())) {
        // return the back trace
        return this->backTrace(searchable->getInitialState(), searchable->getGoalState());
      }
      numberOfNodesEvaluated++;
      // Gets the neighbors of state n
      list<State<Problem> *> *neighbors = searchable->getAllPossibleStates(n);
      // Goes over the neighbors of state n
      for (typename list<State<Problem> *>::iterator it = neighbors->begin(); it != neighbors->end(); ++it) {
        // Checks if the neighbor is not in the open list and not the closed list
        if (!this->closedContains(*it) && !this->openContains(*it)) {
          // sets the fields of the neighbor
          (*it)->setCameFrom(n);
          (*it)->setCumulativeCost((n->getCumulativeCost() + (*it)->getCost()));
          this->addToOpenList(*it);
          // Checks if there is a cheapest path
        } else if (n->getCumulativeCost() + (*it)->getCost() < (*it)->getCumulativeCost()) {
          (*it)->setCumulativeCost((n->getCumulativeCost() + (*it)->getCost()));
          (*it)->setCameFrom(n);
        }
      }
    }
    throw "no Path";
  }
};

#endif //PROBLEMSOLVER_BESTFIRSTSEARCH_H
