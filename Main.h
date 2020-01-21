//
// Created by duni on 16/01/2020.
//

#ifndef PROBLEMSOLVER_MAIN_H
#define PROBLEMSOLVER_MAIN_H

#include <string>
#include "MySerialServer.h"
#include "MyClientHandler.h"
#include "StringReverse.h"
#include "FileCacheManager.h"
#include "SearcherSolver.h"
#include "Matrix.h"

using namespace std;

namespace boot {

    class Main {
    public:
        void main(int port) {
            //Solver<vector<string>, string> *solver = new GraphSolver();
            server_side::Server *A = new MySerialServer();
            AlgorithmOptions<Point, string>* ao = new AlgorithmOptions<Point, string>("BestFirstSearch");
            Solver<Searchable<Point>, string>* s = new SearcherSolver<Point>(ao);

            CacheManager<string, string>* cm = new FileCacheManager<string>();
            ClientHandler *B = new MyClientHandler<string, Point>(s, cm);
            A->open(port, B);
            delete(A);
            delete(B);

        }
    };

}

#endif //PROBLEMSOLVER_MAIN_H
