//
// Created by duni on 25/01/2020.
//

#ifndef PROBLEMSOLVER_BFS_H
#define PROBLEMSOLVER_BFS_H

#include "MutualSearches.h"
#include <vector>
#include <queue>

template<class Problem>
class BFS : public MutualSearches<Problem> {
 private:
  int numberOfNodesEvaluated = 0;
 public:

  // The function returns the back trace of the first path from start state to end state that the algorithm found
  vector<State<Problem> *> search(Searchable<Problem> *searchable) {
    queue < State<Problem> * > bfsQueue;
    // Initialize the start node to be the initialize state
    State<Problem> *startNode = searchable->getInitialState();
    // Initialize the current node
    State<Problem> *currentNode = startNode;
    // Initialize the start node to be the goal state
    State<Problem> *endNode = searchable->getGoalState();
    // Push the current node to the queue
    bfsQueue.push(currentNode);
    // Adds the current node to the closed list
    this->addToClosedList(currentNode);
    while (!bfsQueue.empty()) {
      currentNode = bfsQueue.front();
      bfsQueue.pop();
      this->numberOfNodesEvaluated++;
      // Checks if the current node is not the goal state
      if (!currentNode->Equals(searchable->getGoalState())) {
        // Gets the neighbors of the current node
        list<State<Problem> *> *neighbors = searchable->getAllPossibleStates(currentNode);
        for (typename list<State<Problem> *>::iterator it = neighbors->begin(); it != neighbors->end(); ++it) {
          // Checks if the neighbor is in the closed list
          if (!this->closedContains(*it)) {
            (*it)->setCameFrom(currentNode);
            this->addToClosedList((*it));
            (*it)->setCumulativeCost((currentNode->getCumulativeCost() + (*it)->getCost()));
            bfsQueue.push((*it));
          }
        }
      } else {
        // returns the back trace of the path from the start state to the end state
        return this->backTrace(searchable->getInitialState(), searchable->getGoalState());
      }
    }
    throw "no Path";
  }
};

#endif //PROBLEMSOLVER_BFS_H
