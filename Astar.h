//
// Created by chen96 on 23/01/2020.
//

#ifndef PROBLEMSOLVER__ASTAR_H_
#define PROBLEMSOLVER__ASTAR_H_

#include <vector>
#include "MutualSearches.h"

using namespace std;
template<class Problem>
class Astar : public MutualSearches<Problem> {
 private:
  int numberOfNodesEvaluated = 0;
 public:
  // The function returns the back trace of the cheapest path from start state to end state
  vector<State<Problem> *> search(Searchable<Problem> *searchable) {
    // Gets the initial state
    State<Problem> *currState = searchable->getInitialState();
    // Sets the heuristic cost of the state
    currState->setHeuristicCost(searchable->getDistance(currState, searchable->getGoalState()));
    // Adds the state to the open list
    this->addToOpenList(currState);
    while (this->openListSize() > 0) {
      // Pop the open list
      currState = this->popOpenListAstar();
      // Checks if the current state is the goal state
      if (currState->Equals(searchable->getGoalState())) {
        // Returns the back trace
        return this->backTrace(searchable->getInitialState(), searchable->getGoalState());
      }
      numberOfNodesEvaluated++;
      // Adds the current state to the colsed list
      this->addToClosedList(currState);
      // Gets the neighbors of the current state
      list<State<Problem> *> *neighbors = searchable->getAllPossibleStates(currState);
      // Goes over the neighbors
      for (typename list<State<Problem> *>::iterator it = neighbors->begin(); it != neighbors->end(); ++it) {
        // g = The known distance between the current state and its neighbor
        double g = currState->getCumulativeCost() + (*it)->getCost();
        // h = Estimate the distance between the current state and the destination state
        double h = searchable->getDistance((*it), searchable->getGoalState());
        double f = g + h;
        // Checks if the neighbor is not in the open list and not in the closed list
        if (!this->closedContains(*it) && !this->openContains(*it)) {
          // Sets the neighbor fields
          (*it)->setCameFrom(currState);
          (*it)->setCumulativeCost(g);
          (*it)->setHeuristicCost(h);
          this->addToOpenList(*it);
        } else if (!this->closedContains(*it) && this->openContains(*it)) {
          // Checks if f of the currState is smaller than the f of the neighbor
          if (f < (*it)->getCumulativeCost() + (*it)->getHeuristicCost()) {
            // Sets the neighbor fields
            (*it)->setCameFrom(currState);
            (*it)->setCumulativeCost(g);
            (*it)->setHeuristicCost(h);
          }
        }
      }
    }
    throw "no Path";
  }
};

#endif //PROBLEMSOLVER__ASTAR_H_
