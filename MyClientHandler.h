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
#include <mutex>

using namespace std;

template<class Problem, class T>
class MyClientHandler : public ClientHandler {
private:
    Solver<Searchable<T>, string> *solver;
    CacheManager<Problem, string> *cm;
    std::mutex solverMutex;

public:

    // The Constructor of the class
    MyClientHandler(Solver<Searchable<T>, string> *s, CacheManager<Problem, string> *cm) {
        this->solver = s;
        this->cm = cm;
    }

    // The function handle a client that send a Matrix
    void handleClient(int socketId) override {
        string solution;
        char buffer1[1] = {0};
        string bufferWithLine = "";
        vector<vector<double>> matrixVec;
        char *wordToPush;
        int rowIndex = 0;
        Matrix *matrix;
        Point *start = nullptr;
        Point *end = nullptr;
        string nameAlgorithm;
        string strProblem;
        // Reads char by char from the client, given a socket id of the client
        while (read(socketId, buffer1, 1)) {
            char currChar = buffer1[0];
            if (currChar != '\n') {
                // Insert each letter to the current buffer - each buffer contains a single line
                bufferWithLine += buffer1[0];
            } else {
                // Get the start point and the end point from the last two lines of the matrix
                if (bufferWithLine == "end") {
                    end = new Point(matrixVec.at(rowIndex - 1).at(0),
                            matrixVec.at(rowIndex - 1).at(1));
                    start = new Point(matrixVec.at(rowIndex - 2).at(0),
                            matrixVec.at(rowIndex - 2).at(1));
                    // Erse the last two lines that are not really a part of the matrix
                    matrixVec.pop_back();
                    matrixVec.pop_back();
                    // Creates new Matrix with the matrix vec that contains thw costs, and the start and the end points
                    matrix = new Matrix(&matrixVec, start, end);
                    // Gets the name of the algorithm
                    nameAlgorithm = solver->getName();
                    // Checks if the solution exists in files
                    if (cm->doesSolutionExist(strProblem, nameAlgorithm)) {
                        // Gets the solution from files
                        solution = cm->getSolution(strProblem, nameAlgorithm);
                    } else {
                        // Solves the problem
                        solution = solver->solve(matrix);
                        // Saves the solution
                        cm->saveSolution(strProblem, solution, nameAlgorithm);
                    }
                    const char *solutionToSend = solution.c_str();
                    solverMutex.lock();
                    // Sends the solution to the client
                    send(socketId, solutionToSend, strlen(solutionToSend), 0);
                    solverMutex.unlock();
                    break;
                }
                vector<double> matrixRow;
                strProblem += bufferWithLine;
                char newBuffer[bufferWithLine.length() + 1];
                strcpy(newBuffer, bufferWithLine.c_str());
                solverMutex.lock();
                // Splits the given line by commas
                wordToPush = strtok(newBuffer, " ,");
                while (wordToPush != nullptr) {
                    // Push each separated cost to the vector
                    matrixRow.emplace_back(atof(wordToPush));
                    wordToPush = strtok(nullptr, " ,");
                }
                solverMutex.unlock();
                // Push the vector of the row to the vector of all rows
                matrixVec.push_back(matrixRow);
                rowIndex++;
                bufferWithLine = "";
            }
        }
    }
};

#endif //PROBLEMSOLVER_MYCLIENTHANDLER_H
