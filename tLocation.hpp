//
// Created by agrmv on 13.01.19.
//
#pragma once

#include <utility>
#include <cstdlib>

class tLocation {
private:
    std::pair<double, double> coordinate;
public:
    tLocation()  {
        coordinate.first  = 250 + rand() % 300;
        coordinate.second = 250 + rand() % 300;
    }
    tLocation(const double& x, const double& y) : coordinate{x, y} {}

    double getX() const {
        return coordinate.first;
    }

    double getY() const {
        return coordinate.second;
    }

    void setX(const double & x) {
        coordinate.first = x;
    }

    void setY(const double & y) {
        coordinate.second = y;
    }
};