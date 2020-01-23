//
// Created by duni on 16/01/2020.
//

#ifndef PROBLEMSOLVER_BESTFIRSTSEARCH_H
#define PROBLEMSOLVER_BESTFIRSTSEARCH_H


#include "MutualSearches.h"

template <class Problem>
class BestFirstSearch : public MutualSearches<Problem> {
private:
     int numberOfNodesEvaluated = 0;
public:
    vector<State<Problem>*> search(Searchable<Problem>* searchable) {
        this->addToOpenList(searchable->getInitialState());
        while (this->openListSize() > 0) {
            State<Problem>* n = this->popOpenList();
            this->addToClosedList(n);
            if (n->Equals(searchable->getGoalState())) {
                return this->backTrace(searchable->getInitialState(), searchable->getGoalState());
            }
            numberOfNodesEvaluated++;
            list<State<Problem>*>* neighbors = searchable->getAllPossibleStates(n);
            for (typename list<State<Problem>*>::iterator it = neighbors->begin(); it != neighbors->end(); ++it) {
                if (!this->closedContains(*it) && !this->openContains(*it)) {
                  (*it)->setCameFrom(n);
                  (*it)->setCumulativeCost((n->getCumulativeCost() + (*it)->getCost()));
                    this->addToOpenList(*it);
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
