//
// Created by duni on 12/01/2020.
//

#ifndef PROBLEMSOLVER_MYTESTCLIENTHANDLER_H
#define PROBLEMSOLVER_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "CacheManager.h"
#include "Solver.h"
#include <string>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>

using namespace std;

template<class Problem, class Solution>
class MyTestClientHandler : public ClientHandler {
private:
    Solver<Problem, Solution> *solver;
    CacheManager<Problem, Solution> *cm;

public:
    MyTestClientHandler(Solver<Problem, Solution> * s, CacheManager<Problem, Solution> * cm) {
        this->solver = s;
        this->cm = cm;

    }

    void handleClient(int socketId) {
        string solution;
        char buffer1[1] = {0};
        string bufferWithLine = "";
        while (read(socketId, buffer1, 1)) {
            char currChar = buffer1[0];
            if (currChar != '\n') {
                // Insert each letter to the current buffer - each buffer contains a single line
                bufferWithLine += buffer1[0];
            } else {
                if (bufferWithLine.compare("end\r") == 0) {
                    break;
                }
                if (cm->doesSolutionExist(bufferWithLine, "")) {
                    solution = cm->getSolution(bufferWithLine, "");
                } else {
                    solution = solver->solve(bufferWithLine);
                    cm->saveSolution( bufferWithLine, solution, "");
                }
                const char *solutionToSend = solution.c_str();
                bufferWithLine = "";
                send(socketId, solutionToSend, strlen(solutionToSend), 0);
            }

        }
    }

};




#endif //PROBLEMSOLVER_MYTESTCLIENTHANDLER_H
