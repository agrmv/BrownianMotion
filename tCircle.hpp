//
// Created by agrmv on 13.01.19.
//

#pragma once

#include "tPoint.hpp"

class tCircle : public tPoint {
private:
    double r;
    std::pair<double, double> coordOfCenter;
public:
    explicit tCircle(const double& x = 400, const double& y = 400, const double& r = 200) : r(r), coordOfCenter{x, y} {
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
        return coordOfCenter.first + (getR() * cos(grTOrad(fi)));
    }

    double getTY(const double& fi) {
        return coordOfCenter.second + (getR() * sin(grTOrad(fi)));
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