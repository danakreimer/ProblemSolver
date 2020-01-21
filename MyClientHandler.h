//
// Created by duni on 21/01/2020.
//

#ifndef PROBLEMSOLVER_MYCLIENTHANDLER_H
#define PROBLEMSOLVER_MYCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"
#include "Matrix.h"
#include <string>
#include <unistd.h>
#include <vector>
#include <cstring>
#include <sys/socket.h>

using namespace std;

template<class Problem, class T>
class MyClientHandler : public ClientHandler {
    private:
        Solver<Searchable<T>, string> *solver;
        CacheManager<Problem, string> *cm;

    public:
        MyClientHandler(Solver<Searchable<T>, string> * s, CacheManager<Problem, string> * cm) {
            this->solver = s;
            this->cm = cm;

        }

        void handleClient(int socketId) {
            string solution;
            char buffer1[1] = {0};
            string bufferWithLine = "";
            char* newBuffer;
            vector<vector<double>> matrixVec;
            char* wordToPush;
            int rowIndex = 0;
            Matrix* matrix;
            Point* start;
            Point* end;
            string nameAlgorithm;
            string strProblem = "";
            while (read(socketId, buffer1, 1)) {
                char currChar = buffer1[0];
                if (currChar != '\n') {
                    // Insert each letter to the current buffer - each buffer contains a single line
                    bufferWithLine += buffer1[0];
                } else {
                    strProblem += bufferWithLine;

                    // Get the start point and the end point from the last two lines of the matrix
                    if (bufferWithLine.compare("end\r") == 0) {
                        end->setX(matrixVec.at(rowIndex - 1).at(0));
                        end->setY(matrixVec.at(rowIndex - 1).at(1));
                        start->setX(matrixVec.at(rowIndex - 2).at(0));
                        start->setY(matrixVec.at(rowIndex - 2).at(1));

                        // Erse the last two lines that are not really a part of the matrix
                        matrixVec.erase(matrixVec.end() - 1, matrixVec.end() - 2);

                        matrix = new Matrix(matrixVec, start, end);
                        nameAlgorithm = solver->getName();

                        if (cm->doesSolutionExist(strProblem, nameAlgorithm)) {
                            solution = cm->getSolution(strProblem, nameAlgorithm);
                        } else {
                            solution = solver->solve(matrix);
                            cm->saveSolution(strProblem, solution, nameAlgorithm);
                        }
                        const char *solutionToSend = solution.c_str();
                        send(socketId, solutionToSend, strlen(solutionToSend), 0);
                    }
                    break;
                }

                strcpy(newBuffer, bufferWithLine.c_str());
                wordToPush = strtok(newBuffer, " ,");
                while (wordToPush != nullptr) {
                    matrixVec.at(rowIndex).emplace_back(wordToPush);
                    wordToPush = strtok(nullptr, " ,");
                }
                rowIndex++;
                bufferWithLine = "";
            }
        }
    };


#endif //PROBLEMSOLVER_MYCLIENTHANDLER_H
