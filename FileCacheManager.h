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
    bool doesSolutionExist(Problem p, string algorithmName) {
        fileLock.lock();
        ifstream file;
        string strFileName = "";
        char currentChar;
        int i;

        std::size_t fileName = std::hash<std::string>{}(p);
        strFileName = std::to_string(fileName);
        strFileName += algorithmName;
        strFileName.append(".txt");
        file.open(strFileName);
        bool doesExist = file.good();
        file.close();
        fileLock.unlock();
        return doesExist;
    }
    void saveSolution(Problem p, string s, string algorithmName) {
        fileLock.lock();
        ofstream file;
        string strFileName = "";
        char currentChar;
        int i;

        std::size_t fileName = std::hash<std::string>{}(p);
        strFileName = std::to_string(fileName);
        strFileName += algorithmName;
        strFileName.append(".txt");

        // Open the file
        file.open(strFileName, ios::app);

        if (file.is_open()) {
            file << s << endl;
            //file.write((char *) &s, sizeof(s));
        } else {
            throw "could not open file";
        }
        file.close();
        fileLock.unlock();
    }
    string getSolution (Problem p, string algorithmName) {
        fileLock.lock();
        ifstream file;
        string strFileName;
        char currentChar;
        int i;
        string s;
        std::size_t fileName = std::hash<std::string>{}(p);
        strFileName = std::to_string(fileName);
        strFileName += algorithmName;
        strFileName.append(".txt");

        file.open(strFileName, ios::in);
        if (file.is_open()) {
            //file.read((char*)&s, sizeof(s));
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
