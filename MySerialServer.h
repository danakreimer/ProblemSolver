//
// Created by duni on 12/01/2020.
//

#ifndef PROBLEMSOLVER_MYSERIALSERVER_H
#define PROBLEMSOLVER_MYSERIALSERVER_H

//#include "Server.h"
#include "ClientHandler.h"
#include "Server.h"


using namespace server_side;
using namespace std;


class MySerialServer : public Server {
private:
    bool run;

public:
    MySerialServer();
    void open(int, ClientHandler*);
    void stop();

};


#endif //PROBLEMSOLVER_MYSERIALSERVER_H
