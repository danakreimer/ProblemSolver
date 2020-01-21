//
// Created by duni on 16/01/2020.
//

#ifndef PROBLEMSOLVER_BESTFIRSTSEARCH_H
#define PROBLEMSOLVER_BESTFIRSTSEARCH_H


#include "MutualSearches.h"

template <class Problem, class Solution>
class BestFirstSearch : MutualSearches<Problem, Solution> {
public:
    Solution search(Searchable<Problem>* searchable) {
        this->addToOpenList(searchable->getInitialState());
        while (this->openListSize() > 0) {
            State<Problem>* n = this->popOpenList();
            this->addToClosedList(n);
            if (n->Equals(searchable->getGoalState())) {
                return this->backTrace();
            }
            list<State<Problem>*> neighbors = searchable->getAllPossibleStates(n);
            auto it = neighbors.begin();
            for (it = neighbors.begin(); it < neighbors.end(); ++it) {
                if (!this->closedContains(it) && !this->openContains(it)) {
                    it.setCameFrom(n);
                    it.setCost(n->getCost() + it->getCost());
                    this->addToOpenList(it);
                } else if (n->getCost() + it->getCost() < it->getCost()) {
                    it.setCost(n->getCost() + it->getCost());
                }
            }
        }
    }

};


#endif //PROBLEMSOLVER_BESTFIRSTSEARCH_H
