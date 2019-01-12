//
// Created by agrmv on 13.01.19.
//

#pragma once

#include "tLocation.hpp"
#include <memory>
#include <vector>

enum FigureId {point = 0, circle};

class tFigure : public tLocation {

protected:
    std::pair<double, double> increment;
public:
    tFigure() {
        increment.first  = -100 + rand() % 200;
        increment.second = -100 + rand() % 200;
    }

    tFigure(const double& vx, const double& vy) : increment{vx, vy} {}

    double getVX() const {
        return increment.first;
    }

    double getVY() const {
        return increment.second;
    }

    void setVX(const double& vx) {
        increment.first = vx;
    }

    void setVY(const double& vy) {
        increment.second = vy;
    }

    virtual void move() = 0;
    virtual void draw() = 0;
    virtual void chaoticMove() = 0;
    virtual double getR() const = 0;
    virtual void setR(const double& r) = 0;
    static std::unique_ptr<tFigure> createFigure(FigureId figureId);
};