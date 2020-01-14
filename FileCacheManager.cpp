//
// Created by duni on 12/01/2020.
//

#include "FileCacheManager.h"
#include <string>
#include <fstream>
#include <cstring>

template<class Problem, class Solution>
bool CacheManager<Problem, Solution>::doesSolutionExist(Problem p) {

    ifstream file;
    string strFileName = "";
    char currentChar;
    int i;

    std::size_t fileName = std::hash<std::string>{}(p);
    strFileName = std::to_string(fileName);

    file.open(strFileName);
    bool doesExist = file.good();
    file.close();
    return doesExist;
}

template<class Problem, class Solution>
void CacheManager<Problem, Solution>::saveSolution(Problem p, Solution s) {

    ofstream file;
    string strFileName = "";
    char currentChar;
    int i;

    std::size_t fileName = std::hash<std::string>{}(p);
    strFileName = std::to_string(fileName);


    // Open the file
    file.open(strFileName, ios::binary);

    if (file.is_open()) {
        file.write((char *) &s, sizeof(s));
    } else {
        throw "could not open file";
    }
    file.close();
}

template<class Problem, class Solution>
Solution CacheManager<Problem, Solution>::getSolution (Problem p) {

    ifstream file;
    string strFileName = "";
    char currentChar;
    int i;
    Solution s;

    std::size_t fileName = std::hash<std::string>{}(p);
    strFileName = std::to_string(fileName);

    file.open(strFileName, ios::binary);
    if (file.is_open()) {
        file.read((char *) &s, sizeof(s));
    } else {
        throw "object doesnt exist in cache or files";
    }

    file.close();
    return s;
}