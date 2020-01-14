//
// Created by duni on 12/01/2020.
//

#ifndef PROBLEMSOLVER_MYTESTCLIENTHANDLER_H
#define PROBLEMSOLVER_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Server.h"
#include "CacheManager.h"
#include "Solver.h"

using namespace std;

template<class Problem, class Solution>
class MyTestClientHandler : public ClientHandler {
private:
    Solver<Problem, Solution> *solver;
    CacheManager<Problem, Solution> *cm;

public:
    MyTestClientHandler(Solver<Problem, Solution> * s, CacheManager<Problem, Solution> * cm) {
        this->solver = s;
        this->cm = cm;

    }

    void handleClient(int);

};


#endif //PROBLEMSOLVER_MYTESTCLIENTHANDLER_H
