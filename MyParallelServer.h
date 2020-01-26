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
  int server_socket;
  vector<thread> clients;
 public:
  MyParallelServer() {
    run = true;
  }

  void open(int, ClientHandler *) override;
  void stop() override;
  int getServerSocket() {
    return this->server_socket;
  }
};

#endif //PROBLEMSOLVER_MYPARALLELSERVER_H
