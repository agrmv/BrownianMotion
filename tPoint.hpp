#pragma once

#include <time.h>
#include <cmath>
#include <GL/freeglut.h>
#include "tFigure.hpp"

class tPoint : public tFigure {
    std::pair<double, double> point;
public:
    tPoint() : point{6, 0.007} {}
    explicit tPoint(const double& r) : point{r, 0.007} {}
    tPoint(const double& r, const double& DT = 0.007) : point{r, DT} {}
    tPoint(const double& x, const double& y, const double& r) : point{r, 0.007} {
        setX(x);
        setY(y);
    }

    double getR() const {
        return point.first;
    }

    void setR(const double& r) {
        if (r < 1)  {
            point.first = 1;
        } else  {
            point.first = r;
        }
    }

    void move() override {
        setX(getX() + (getVX() * point.second));
        setY(getY() + (getVY() * point.second));
    }

    void chaoticMove() {
        if (rand() % 2) {
            increment.first  = -150 + rand() % 300;
            increment.second = -150 + rand() % 300;

        }
    }

    void draw() override {
        glBegin(GL_LINES);
        for (size_t i = 0; i < 360; ++i) {
            double x = point.first * cos(i * M_PI / 180);
            double y = point.first * sin(i * M_PI / 180);
            glVertex2f(static_cast<GLfloat>(getX() + x), static_cast<GLfloat>(getY() + y));
            x = point.first * cos((i + 1) * M_PI / 180);
            y = point.first * sin((i + 1) * M_PI / 180);
            glVertex2f(static_cast<GLfloat>(getX() + x), static_cast<GLfloat>(getY() + y));
        }
    }
};