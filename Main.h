//
// Created by duni on 16/01/2020.
//

#ifndef PROBLEMSOLVER_MAIN_H
#define PROBLEMSOLVER_MAIN_H

#include <string>
#include "MySerialServer.h"
#include "MyTestClientHandler.h"
#include "StringReverse.h"
#include "FileCacheManager.h"

namespace boot {

    class Main {
    public:
        void main(int port) {
            //Solver<vector<string>, string> *solver = new GraphSolver();
            server_side::Server *A = new MySerialServer();
            Solver<string, string>* s = new StringReverse();
            CacheManager<string, string>* cm = new FileCacheManager<string, string >();
            ClientHandler *B = new MyTestClientHandler<string, string>(s, cm);
            A->open(port, B);
            delete(A);
            delete(B);

        }
    };

}

#endif //PROBLEMSOLVER_MAIN_H
