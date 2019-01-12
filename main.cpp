#include "tPoint.hpp"
#include "tCircle.hpp"
#include "Glut.hpp"

std::unique_ptr<tFigure> tFigure::createFigure(FigureId figureId) {
    switch (figureId) {
        case point:
            return std::make_unique<tPoint>();
        case circle:
            return std::make_unique<tCircle>();
        default:
            break;
    }
};

int main(int argc, char **argv) {
    for (size_t i = 0; i < 12; ++i) {
        v.emplace_back(tFigure::createFigure(point));
    }

    v.emplace_back(tFigure::createFigure(circle)); // always last!!!

    Glut::getInstance(argc, argv);
    return 0;
}