//
// Created by duni on 21/01/2020.
//

#ifndef PROBLEMSOLVER_POINT_H
#define PROBLEMSOLVER_POINT_H


class Point {
private:
    int x;
    int y;
public:
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int getX() const {
        return this->x;
    }

    int getY() const {
        return this->y;
    }

    void setX(int x) {
        this->x = x;
    }

    void setY(int y) {
        this->y = y;
    }

    void setPoint(Point* point) {
        this->setX(point->x);
        this->setY(point->y);
    }

    bool operator== (const Point &other) const {
        return this->getX() == other.getX() && this->getY() == other.getY();
    }

};


#endif //PROBLEMSOLVER_POINT_H
