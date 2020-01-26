//
// Created by duni on 14/01/2020.
//

#include "StringReverse.h"

// This function solves the problem of reversing a given string
string StringReverse::solve(string problem) {
    int n = problem.length();

    // Swap character starting from two corners
    for (int i = 0; i < n / 2; i++) {
        swap(problem[i], problem[n - i - 1]);
    }
    return problem;
}

// This function returns the name of the algorithm that solved the problem (in this case the function isn't relevant
string StringReverse::getName() {
    return "";
}