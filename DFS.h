//
// Created by duni on 25/01/2020.
//

#ifndef PROBLEMSOLVER_DFS_H
#define PROBLEMSOLVER_DFS_H

#include "MutualSearches.h"
#include <vector>
#include <stack>
#include <iostream>

template <class Problem>
class DFS : public MutualSearches<Problem> {
private:
    int numberOfNodesEvaluated = 0;
public:

    vector<State<Problem>*> search(Searchable<Problem>* searchable) {
        stack<State<Problem>*> dfsStack;
        State<Problem>* node;
        dfsStack.push(searchable->getInitialState());
        while (!dfsStack.empty()) {
            node = dfsStack.top();
            dfsStack.pop();
            this->numberOfNodesEvaluated++;

            if (node->Equals(searchable->getGoalState())) {
                return this->backTrace(searchable->getInitialState(), searchable->getGoalState());
            }

            if (!this->closedContains(node)) {
                this->addToClosedList(node);
            }

            list<State<Problem>*> *neighbors = searchable->getAllPossibleStates(node);
            for (auto it = neighbors->begin(); it != neighbors->end(); ++it) {
                if (!this->closedContains(*it)) {
                    (*it)->setCameFrom(node);
                    (*it)->setCumulativeCost((node->getCumulativeCost() + (*it)->getCost()));
                    dfsStack.push(*it);
                }
            }
        }

        throw "no Path";
    }
};


#endif //PROBLEMSOLVER_BFS_H
