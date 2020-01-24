//
// Created by duni on 24/01/2020.
//

#ifndef PROBLEMSOLVER_MYPARALLELSERVER_H
#define PROBLEMSOLVER_MYPARALLELSERVER_H


#include "Server.h"
#include <thread>
#include <vector>

using namespace std;

class MyParallelServer : public server_side::Server {
private:
    bool run;
    vector<thread> clients;
public:
    MyParallelServer() {
        run = true;
    }

    void open(int, ClientHandler*);
    void stop();

};


#endif //PROBLEMSOLVER_MYPARALLELSERVER_H
