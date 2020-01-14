//
// Created by duni on 12/01/2020.
//

#ifndef PROBLEMSOLVER_SERVER_H
#define PROBLEMSOLVER_SERVER_H

namespace server_side {
    class Server {
        virtual void open (int) = 0;
        virtual void stop() = 0;
    };
}

#endif //PROBLEMSOLVER_SERVER_H
