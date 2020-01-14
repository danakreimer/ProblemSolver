//
// Created by duni on 12/01/2020.
//

#ifndef PROBLEMSOLVER_CACHEMANAGER_H
#define PROBLEMSOLVER_CACHEMANAGER_H

template <class Problem, class Solution>
class CacheManager {
public:
    virtual bool doesSolutionExist(Problem) = 0;
    virtual Solution getSolution (Problem) = 0;
    virtual void saveSolution (Problem, Solution) = 0;

};


#endif //PROBLEMSOLVER_CACHEMANAGER_H
