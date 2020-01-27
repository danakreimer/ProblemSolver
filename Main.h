//
// Created by duni on 16/01/2020.
//

#ifndef PROBLEMSOLVER_MAIN_H
#define PROBLEMSOLVER_MAIN_H

#include <string>
#include "MySerialServer.h"
#include "MyClientHandler.h"
#include "FileCacheManager.h"
#include "SearcherSolver.h"
#include "Matrix.h"
#include "MyParallelServer.h"

using namespace std;

namespace boot {

    class Main {
    public:
        void main(int port) {
            try {
                // Create the parallel server
                server_side::Server *A = new MyParallelServer();
                // Implement the chosen algorithm to solve the problem
                AlgorithmOptions<Point> *ao = new AlgorithmOptions<Point>("Astar");
                // Create the object adapter that will connect the solver to the searcher
                Solver<Searchable<Point>, string> *s = new SearcherSolver<Point>(ao);
                // Create the cache manager that will run the solved problems by now
                CacheManager<string, string> *cm = new FileCacheManager<string>();
                // Create the client handler to read the problem with
                ClientHandler *B = new MyClientHandler<string, Point>(s, cm);
                // Open the socket to handle the date from the server
                A->open(port, B);
                delete (A);
                delete (B);
            }

            catch (const char *e) {}
        }
    };
}

#endif //PROBLEMSOLVER_MAIN_H
