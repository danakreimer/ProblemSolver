//
// Created by duni on 12/01/2020.
//

#ifndef PROBLEMSOLVER_SERVER_H
#define PROBLEMSOLVER_SERVER_H


#include "ClientHandler.h"

namespace server_side {
    class Server {
    public:
        virtual void open (int, ClientHandler*) = 0;
        virtual void stop() = 0;
    };
}

#endif //PROBLEMSOLVER_SERVER_H
