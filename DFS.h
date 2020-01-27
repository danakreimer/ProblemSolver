//
// Created by duni on 25/01/2020.
//

#ifndef PROBLEMSOLVER_DFS_H
#define PROBLEMSOLVER_DFS_H

#include "MutualSearches.h"
#include <vector>
#include <stack>
#include <iostream>

template<class Problem>
class DFS : public MutualSearches<Problem> {
private:
    int numberOfNodesEvaluated = 0;
public:

    // The function returns the back trace of the first path from start state to end state that the algorithm found
    vector<State<Problem> *> search(Searchable<Problem> *searchable) {
        stack < State<Problem> * > dfsStack;
        State<Problem> *node;
        // Push the initial state to the stack
        dfsStack.push(searchable->getInitialState());
        // While the stack has nodes in it - keep on the operations
        while (!dfsStack.empty()) {
            // Pull the first node from the stack
            node = dfsStack.top();
            dfsStack.pop();
            // Update the number of nodes that has been checked by the algorithm
            this->numberOfNodesEvaluated++;
            // Check if we reached the goal state - if true return the back trace that has been calculated
            if (node->Equals(searchable->getGoalState())) {
                return this->backTrace(searchable->getInitialState(), searchable->getGoalState());
            }

            // If the current node doesn't exist in the closed list - push it to the closed list
            if (!this->closedContains(node)) {
                this->addToClosedList(node);
            }

            // Initialize a list of all the neighbors of the current node
            list<State<Problem> *> *neighbors = searchable->getAllPossibleStates(node);
            // Go through all of the neighbors
            for (auto it = neighbors->begin(); it != neighbors->end(); ++it) {
                // Check if the current node exists in the closed list and update it suitably
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
