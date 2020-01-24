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
  vector<State<Problem> *> search(Searchable<Problem> *searchable) {
    State<Problem> *currState = searchable->getInitialState();
    currState->setHeuristicCost(searchable->getDistance(currState, searchable->getGoalState()));

    this->addToOpenListAstar(currState);
    while (this->openListSize() > 0) {
      currState = this->popOpenList();

      if (currState->Equals(searchable->getGoalState())) {
        return this->backTrace(searchable->getInitialState(), searchable->getGoalState());
      }
      numberOfNodesEvaluated++;
      this->addToClosedList(currState);
      list<State<Problem> *> *neighbors = searchable->getAllPossibleStates(currState);
      for (typename list<State<Problem> *>::iterator it = neighbors->begin(); it != neighbors->end(); ++it) {
        double g = currState->getCumulativeCost() + (*it)->getCost();
        double h = searchable->getDistance((*it), searchable->getGoalState());
        double f = g + h;

        if (!this->closedContains(*it) && !this->openContains(*it)) {
          (*it)->setCameFrom(currState);
          (*it)->setCumulativeCost(g);
          (*it)->setHeuristicCost(h);
          this->addToOpenList(*it);
        } else if (!this->closedContains(*it) && this->openContains(*it)) {
          if (f < (*it)->getCumulativeCost()+(*it)->getHeuristicCost()){
            (*it)->setCameFrom(currState);
            (*it)->setCumulativeCost(g);
            (*it)->setHeuristicCost(h);
          }
            //n->getCumulativeCost() + (*it)->getCost() < (*it)->getCumulativeCost()) {

        }
      }
    }
    throw "no Path";
  }

};
#endif //PROBLEMSOLVER__ASTAR_H_
