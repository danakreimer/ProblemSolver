//
// Created by duni on 12/01/2020.
//

#ifndef PROBLEMSOLVER_CACHEMANAGER_H
#define PROBLEMSOLVER_CACHEMANAGER_H

template<class Problem, class Solution>
class CacheManager {
 public:
  virtual bool doesSolutionExist(Problem, string) = 0;
  virtual Solution getSolution(Problem, string) = 0;
  virtual void saveSolution(Problem, Solution, string) = 0;
};

#endif //PROBLEMSOLVER_CACHEMANAGER_H
