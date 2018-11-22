#pragma once

#include <cstdlib>
#include <vector>
#include <memory>
#include <iostream>
#include <time.h>
#include <cmath>
#include <GL/freeglut.h>
#include <cassert>

enum FigureId {point=0, circle};

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

class tFigure : public tLocation {
private:
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
    virtual double getR() const = 0;
    virtual void setR(const double& r) = 0;
    static std::shared_ptr<tFigure> createFigure(FigureId id);
};

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


class tCircle : public tPoint {
private:
    double r;
    std::pair<double, double> coordOfCentr;
public:
    explicit tCircle(const double& x = 400, const double& y = 400, const double& r = 200) : r(r), coordOfCentr{x, y} {
        setX(x);
        setY(y);
    }
    void setR(const double& r) {
        this->r = r;
    }

    double getR() const {
        return r;
    }

    double getTX(const double& fi) {
        return coordOfCentr.first + (getR() * cos(grTOrad(fi)));
    }

    double getTY(const double& fi) {
        return coordOfCentr.second + (getR() * sin(grTOrad(fi)));
    }

    double grTOrad(const double& Gr) {
        return Gr * M_PI / 180;
    }

    void draw() final {
        glBegin(GL_LINE_LOOP);
        for (size_t i = 0; i < 360; ++i) {
            glVertex2f(static_cast<GLfloat>(getTX(i)), static_cast<GLfloat>(getTY(i)));
            glVertex2f(static_cast<GLfloat>(getTX(i + 1)), static_cast<GLfloat>(getTY(i + 1)));
        }
    }
};

std::shared_ptr<tFigure> tFigure::createFigure( FigureId id ) {
    static std::weak_ptr<tFigure> pInstance;
    std::shared_ptr<tFigure> instance = pInstance.lock();
    switch (id) {
        case point:
            instance.reset(new tPoint);
            pInstance = instance;
            break;
        case circle:
            instance.reset(new tCircle);
            pInstance = instance;
            break;
        default:
            assert(false);
    }
    return instance;
};
