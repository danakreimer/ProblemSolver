//
// Created by duni on 12/01/2020.
//

#ifndef PROBLEMSOLVER_MYTESTCLIENTHANDLER_H
#define PROBLEMSOLVER_MYTESTCLIENTHANDLER_H

#include <ClientHandler.h>
#include <Solver.h>
#include <CacheManager.h>


class MyTestClientHandler : public ClientHandler {
private:
    Solver* solver;
    CacheManager* cm;

};


#endif //PROBLEMSOLVER_MYTESTCLIENTHANDLER_H
