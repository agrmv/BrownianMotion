//
// Created by agrmv on 13.01.19.
//

#pragma once

#include <GL/freeglut.h>
#include <vector>
#include <cmath>
#include "tFigure.hpp"

std::vector<std::unique_ptr<tFigure>> v;

class Glut {
private:
    static std::weak_ptr<Glut> pInstance;

    Glut(int argc, char **argv) {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE);
        glutInitWindowSize(800, 800);
        glutInitWindowPosition(0, 0);
        glutCreateWindow("Brownian motion");
        glClearColor(0, 0, 0, 1.0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, 800, 800, 0, -1, 1);
        glutDisplayFunc(displayWindow);
        glutTimerFunc(0, timer, 0);
        glutMainLoop();
    }

    static void displayWindow() {
        glClear(GL_COLOR_BUFFER_BIT);
        for (const auto &i : v) {
            glPointSize(5);
            glColor3f(1.0, 0.0, 0.0);
            glEnable(GL_POINT_SMOOTH);
            i->draw();
        }
        v.back()->draw();
        glEnd();
        glutSwapBuffers();

    }

    static void timer(int) {
        for (size_t i = 0; i < v.size() - 1; ++i) {
            for (size_t j = 0; j < v.size() - 1; ++j) {
                if (i != j) {
                    double d = sqrt(pow(v[i]->getX() - v[j]->getX(), 2) + pow(v[i]->getY() - v[j]->getY(), 2));
                    if (d <= (v[i]->getR() + v[j]->getR())) {
                        double f = 99 * (v[i]->getR() + v[j]->getR() - d);
                        v[i]->setVX(v[i]->getVX() + f * (v[i]->getX() - v[j]->getX()) / d / v[i]->getR() * 0.1);
                        v[i]->setVY(v[i]->getVY() + f * (v[i]->getY() - v[j]->getY()) / d / v[i]->getR() * 0.1);
                        v[j]->setVX(v[j]->getVX() - f * (v[i]->getX() - v[j]->getX()) / d / v[j]->getR() * 0.1);
                        v[j]->setVY(v[j]->getVY() - f * (v[i]->getY() - v[j]->getY()) / d / v[j]->getR() * 0.1);
                    }
                }
            }

            double d = ((v[i]->getX() - 400) * (v[i]->getX() - 400) + (v[i]->getY() - 400) * (v[i]->getY() - 400));
            if (d >
                ((v.back()->getR() - v[i]->getR() - v[i]->getR()) * (v.back()->getR() - v[i]->getR() - v[i]->getR()))) {
                double f = 50 * (v.back()->getR() * v.back()->getR() - d);
                v[i]->setVX(v[i]->getVX() - f * (v[i]->getX() - 400) / d / v[i]->getR() * 0.1);
                v[i]->setVY(v[i]->getVY() - f * (v[i]->getY() - 400) / d / v[i]->getR() * 0.1);
            }
            v[i]->move();
            //v[i]->chaoticMove();
        }
        displayWindow();
        glutTimerFunc(10, timer, 0);
    }

public:
    //useless singleton
    static std::shared_ptr<Glut> getInstance(int argc, char **argv) {
        static std::weak_ptr<Glut> pInstance;
        std::shared_ptr<Glut> instance = pInstance.lock();
        if (pInstance.expired()) {
            instance.reset(new Glut(argc, argv));
            pInstance = instance;
        }
        return instance;
    }
};