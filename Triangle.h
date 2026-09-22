#ifndef SHAPES_BLACKBOARD_TRIANGLE_H
#define SHAPES_BLACKBOARD_TRIANGLE_H

#include "Shape.h"

class Triangle : public Shape {
private:
    int x2, y2;
    int x3, y3;

    double sign(double p1x, double p1y, double p2x, double p2y, double p3x, double p3y) const;
    bool isInside(double px, double py, double ax, double ay, double bx, double by, double cx, double cy) const;

public:
    Triangle(std::string id, int x1, int y1, std::string color, bool isFilled, int x2, int y2, int x3, int y3);

    void move(int dx, int dy) override;
    std::string getType() const override;
    std::string getInfo() const override;
    bool containsPoint(int px, int py) const override;
    void draw(std::vector<std::vector<char>> &grid, int boardWidth, int boardHeight) const override;
    std::string serialize() const override;
    bool edit(const std::string &args) override;
};

#endif //SHAPES_BLACKBOARD_TRIANGLE_H