//
// Created by duni on 21/01/2020.
//

#ifndef PROBLEMSOLVER_POINT_H
#define PROBLEMSOLVER_POINT_H

#include <cmath>

class Point {
private:
    int x;
    int y;
public:
    // This is a constructor function
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }

    // This function returns the x coordinate of the current node
    int getX() const {
        return this->x;
    }

    // This function returns the y coordinate of the current node
    int getY() const {
        return this->y;
    }

    // This function sets the x coordinate of the current node
    void setX(int x) {
        this->x = x;
    }

    // This function sets the y coordinate of the current node
    void setY(int y) {
        this->y = y;
    }

    // This function preforms the equal operator between the current point and a given point
    bool operator==(const Point &other) const {
        return this->getX() == other.getX() && this->getY() == other.getY();
    }

    bool Equals(Point *other) {
        return this->getX() == other->getX() && this->getY() == other->getY();
    }

    // This function preforms placement of a given point to the current point
    void operator=(const Point &other) {
        this->x = other.getX();
        this->y = other.getY();
    }

};

#endif //PROBLEMSOLVER_POINT_H
