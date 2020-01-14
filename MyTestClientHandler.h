//
// Created by duni on 12/01/2020.
//

#ifndef PROBLEMSOLVER_MYTESTCLIENTHANDLER_H
#define PROBLEMSOLVER_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Server.h"
#include "CacheManager.h"
#include "Solver.h"


class MyTestClientHandler : public ClientHandler {
private:
    Solver* solver;
    CacheManager* cm;

public:
    void handleClient(int);

};


#endif //PROBLEMSOLVER_MYTESTCLIENTHANDLER_H
