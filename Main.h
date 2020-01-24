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
            //Solver<vector<string>, string> *solver = new GraphSolver();
            server_side::Server *A = new MyParallelServer();
            AlgorithmOptions<Point>* ao = new AlgorithmOptions<Point>("Astar");
            Solver<Searchable<Point>, string>* s = new SearcherSolver<Point>(ao);
            CacheManager<string, string>* cm = new FileCacheManager<string>();
            ClientHandler *B = new MyClientHandler<string, Point>(s, cm);
            A->open(port, B);
            delete(A);
            delete(B);
          }
          catch (const char* e) {}
         /* vector<vector<double>>* vec = new vector<vector<double>>(4);
          vec->at(0).push_back(10.0);
          vec->at(0).push_back(3.0);
          vec->at(0).push_back(8.0);
          vec->at(0).push_back(4.0);
          vec->at(0).push_back(12.0);
          vec->at(1).push_back(1.0);
          vec->at(1).push_back(1.0);
          vec->at(1).push_back(-1.0);
          vec->at(1).push_back(9.0);
          vec->at(1).push_back(10.0);
          vec->at(2).push_back(3.0);
          vec->at(2).push_back(9.0);
          vec->at(2).push_back(20.0);
          vec->at(2).push_back(14.0);
          vec->at(2).push_back(1.0);
          vec->at(3).push_back(11.0);
          vec->at(3).push_back(-1.0);
          vec->at(3).push_back(13.0);
          vec->at(3).push_back(2.0);
          vec->at(3).push_back(15.0);
          Point* start = new Point(0.0,0.0);
          Point* end = new Point(3.0,4.0);

          Searchable<Point>* mat = new Matrix(vec,start,end);
          Searcher<Point>* s = new BestFirstSearch<Point>();
          try {
            vector<State<Point>*> v = s->search(mat);
            printf("hi");
          }
          catch (const char* e) {}*/


        }

    };

}

#endif //PROBLEMSOLVER_MAIN_H
