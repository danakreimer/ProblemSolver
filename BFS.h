//
// Created by duni on 25/01/2020.
//

#ifndef PROBLEMSOLVER_BFS_H
#define PROBLEMSOLVER_BFS_H

#include "MutualSearches.h"
#include <vector>
#include <queue>

template <class Problem>
class BFS : public MutualSearches<Problem> {
private:
    int numberOfNodesEvaluated = 0;
public:
    vector<State<Problem>*> search(Searchable<Problem>* searchable) {
        queue<State<Problem>*> bfsQueue;
        State<Problem>* startNode = searchable->getInitialState();
        State<Problem>* currentNode = startNode;
        State<Problem>* endNode = searchable->getGoalState();
        bfsQueue.push(currentNode);
        this->addToClosedList(currentNode);
        while (!bfsQueue.empty()) {
            currentNode = bfsQueue.front();
            bfsQueue.pop();
            this->numberOfNodesEvaluated++;
            if (!currentNode->Equals(searchable->getGoalState())) {
                list<State<Problem>*> *neighbors = searchable->getAllPossibleStates(currentNode);
                for (typename list<State<Problem> *>::iterator it = neighbors->begin(); it != neighbors->end(); ++it) {
                    if (!this->closedContains(*it)) {
                        (*it)->setCameFrom(currentNode);
                        this->addToClosedList((*it));
                        (*it)->setCumulativeCost((currentNode->getCumulativeCost() + (*it)->getCost()));
                        bfsQueue.push((*it));
                    }
                }
            } else {
                return this->backTrace(searchable->getInitialState(), searchable->getGoalState());
            }
        }
            throw "no Path";
        }


};


#endif //PROBLEMSOLVER_BFS_H
