//
// Created by alex on 16.09.26.
//

#ifndef SHAPES_BLACKBOARD_TRIANGLE_H
#define SHAPES_BLACKBOARD_TRIANGLE_H

#include "Shape.h"
#include <cmath>
#include <algorithm>

class Triangle : public Shape {
private:
    int x2, y2;
    int x3, y3;

    double sign(double p1x, double p1y, double p2x, double p2y, double p3x, double p3y) const {
        return (p1x - p3x) * (p2y - p3y) - (p2x - p3x) * (p1y - p3y);
    }

    void move(int dx, int dy) override {
        Shape::move(dx, dy);
        x2 += dx;
        y2 += dy;
        x3 += dx;
        y3 += dy;
    }

    bool isInside(double px, double py, double ax, double ay, double bx, double by, double cx, double cy) const {
        double d1 = sign(px, py, ax, ay, bx, by);
        double d2 = sign(px, py, bx, by, cx, cy);
        double d3 = sign(px, py, cx, cy, ax, ay);

        bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
        bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

        return !(has_neg && has_pos);
    }
public:
    Triangle(std::string id, int x1, int y1, std::string color, bool isFilled, int x2, int y2, int x3, int y3)
        : Shape(std::move(id), x1, y1, std::move(color), isFilled), x2(x2), y2(y2), x3(x3), y3(y3) {}

    std::string getType() const override {
        return "triangle";
    }

    std::string getInfo() const override {
        std::string mode = isFilled ? "fill" : "frame";
        return id + " " + getType() + " " + color + " " + mode + " " +
               std::to_string(x) + " " + std::to_string(y) + " " +
               std::to_string(x2) + " " + std::to_string(y2) + " " +
               std::to_string(x3) + " " + std::to_string(y3);
    }

    bool containsPoint(int px, int py) const override {
        double ax = (double)x, ay = (double)y;
        double bx = (double)x2, by = (double)y2;
        double cx = (double)x3, cy = (double)y3;
        double pfx = (double)px, pfy = (double)py;

        if (isFilled) {
            return isInside(pfx, pfy, ax, ay, bx, by, cx, cy);
        }
        else {
            return isInside(pfx, pfy, ax, ay, bx, by, cx, cy);
        }
    }

    void draw(std::vector<std::vector<char>> &grid, int boardWidth, int boardHeight) const override {
        char symbol = getColorChar();

        int minX = std::max(0, std::min({x, x2, x3}));
        int maxX = std::min(boardWidth - 1, std::max({x, x2, x3}));
        int minY = std::max(0, std::min({y, y2, y3}));
        int maxY = std::min(boardHeight - 1, std::max({y, y2, y3}));

        for (int py = minY; py <= maxY; ++py) {
            for (int px = minX; px <= maxX; ++px) {
                double ax = (double)x, ay = (double)y;
                double bx = (double)x2, by = (double)y2;
                double cx = (double)x3, cy = (double)y3;
                double pfx = (double)px, pfy = (double)py;

                if (isFilled) {
                    if (isInside(pfx, pfy, ax, ay, bx, by, cx, cy)) {
                        grid[py][px] = symbol;
                    }
                } else {
                    if (isInside(pfx, pfy, ax, ay, bx, by, cx, cy)) {
                        bool isBorder = false;
                        for (int nx = -1; nx <= 1; ++nx) {
                            for (int ny = -1; ny <= 1; ++ny) {
                                if (!isInside(px + nx, py + ny, ax, ay, bx, by, cx, cy)) {
                                    isBorder = true;
                                }
                            }
                        }
                        if (isBorder) {
                            grid[py][px] = symbol;
                        }
                    }
                }
            }
        }
    }
};


#endif //SHAPES_BLACKBOARD_TRIANGLE_H
