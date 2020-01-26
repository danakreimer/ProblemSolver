//
// Created by duni on 12/01/2020.
//

#ifndef PROBLEMSOLVER_FILECHACHEMANAGER_H
#define PROBLEMSOLVER_FILECHACHEMANAGER_H

#include <fstream>
#include <mutex>
#include "CacheManager.h"

using namespace std;

template <class Problem>
class FileCacheManager : public CacheManager<Problem, string> {
private:
    std::mutex fileLock;
public:
    // This function checks the cache if a current solution exists and returns the result
    bool doesSolutionExist(Problem p, string algorithmName) {
        fileLock.lock();
        ifstream file;
        string strFileName = "";
        char currentChar;
        int i;

        // Preform hash function on the problem to save the file in a unique way
        std::size_t fileName = std::hash<std::string>{}(p);
        strFileName = std::to_string(fileName);
        // Concatenate the algorithm name which solved the problem to the result of the hash function
        strFileName += algorithmName;
        // Concatenate the ending of the file name
        strFileName.append(".txt");
        file.open(strFileName);
        // Check if the wanted file exists in the cache
        bool doesExist = file.good();
        file.close();
        fileLock.unlock();
        return doesExist;
    }

    // This function saves the solution in the cache
    void saveSolution(Problem p, string s, string algorithmName) {
        fileLock.lock();
        ofstream file;
        string strFileName = "";
        char currentChar;
        int i;

        // Preform hash function on the problem to save the file in a unique way
        std::size_t fileName = std::hash<std::string>{}(p);
        strFileName = std::to_string(fileName);
        // Concatenate the algorithm name which solved the problem to the result of the hash function
        strFileName += algorithmName;
        // Concatenate the ending of the file name
        strFileName.append(".txt");

        // Open the file
        file.open(strFileName, ios::app);

        if (file.is_open()) {
            // Write the solution into the file
            file << s << endl;
            //file.write((char *) &s, sizeof(s));
        } else {
            throw "could not open file";
        }
        file.close();
        fileLock.unlock();
    }

    // This function returns the solution from the cache
    string getSolution (Problem p, string algorithmName) {
        fileLock.lock();
        ifstream file;
        string strFileName;
        char currentChar;
        int i;
        string s;
        // Preform hash function on the problem to save the file in a unique way
        std::size_t fileName = std::hash<std::string>{}(p);
        strFileName = std::to_string(fileName);
        // Concatenate the algorithm name which solved the problem to the result of the hash function
        strFileName += algorithmName;
        // Concatenate the ending of the file name
        strFileName.append(".txt");

        // OPen the file that contains the solution
        file.open(strFileName, ios::in);
        if (file.is_open()) {
            getline(file, s);
        } else {
            throw "object doesnt exist in cache or files";
        }

        file.close();
        fileLock.unlock();
        return s;
    }
};

#endif //PROBLEMSOLVER_FILECHACHEMANAGER_H
