//
// Created by duni on 12/01/2020.
//

#include "MyTestClientHandler.h"
#include <string>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>

template <class Problem, class Solution>
void MyTestClientHandler<Problem, Solution>::handleClient(int socketId) {
    string solution;
    char buffer1[1] = {0};
    string bufferWithLine = "";
    while (read(socketId, buffer1, 1)) {
        char currChar = buffer1[0];
        if (currChar != '\n') {
            // Insert each letter to the current buffer - each buffer contains a single line
            bufferWithLine += buffer1[0];
        } else {
            if (bufferWithLine.compare("end") == 0) {
                break;
            }
            if (cm->doesSolutionExist(bufferWithLine)) {
                solution = cm->getSolution(bufferWithLine);
            } else {
                solution = solver->solve(bufferWithLine);
                cm->saveSolution(solution);
            }
            const char *solutionToSend = solution.c_str();
            bufferWithLine = "";
            send(socketId, solutionToSend, strlen(solutionToSend), 0);
        }

    }
}
