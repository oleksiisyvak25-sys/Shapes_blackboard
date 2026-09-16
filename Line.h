//
// Created by alex on 16.09.26.
//

#ifndef SHAPES_BLACKBOARD_LINE_H
#define SHAPES_BLACKBOARD_LINE_H

#include "Shape.h"
#include <cmath>
#include <algorithm>
#include <vector>

class Line : public Shape {
private:
    int x2, y2;

    std::vector<std::pair<int, int>> getLinePoints() const {
        std::vector<std::pair<int, int>> points;
        int x0 = x;
        int y0 = y;
        int x1 = x2;
        int y1 = y2;

        int dx = std::abs(x1 - x0);
        int dy = std::abs(y1 - y0);
        int sx = 0;
        int sy = 0;

        if (x0 < x1) {
            sx = 1;
        }
        else {
            sx = -1;
        }

        if (y0 < y1) {
            sy = 1;
        }
        else {
            sy = -1;
        }

        int err = dx - dy;

        while (true) {
            points.push_back({x0, y0});
            if (x0 == x1 && y0 == y1) {
                break;
            }

            int e = 2*err;
            if (e > -dy) {
                err -= dy;
                x0 += sx;
            }
            if (e < dx) {
                err += dx;
                y0 += sy;
            }
        }
        return points;

    }

public:
    Line(std::string id, int x1, int y1, std::string color, int x2, int y2)
        : Shape(std::move(id), x1, y1, std::move(color), true), x2(x2), y2(y2) {}

    std::string getType() const override {
        return "line";
    }

    void move(int dx, int dy) override {
        Shape::move(dx, dy);
        x2 += dx;
        y2 += dy;
    }

    std::string getInfo() const override {
        return id + " " + getType() + " " + color + " " +
               std::to_string(x) + " " + std::to_string(y) + " " +
               std::to_string(x2) + " " + std::to_string(y2);
    }

    bool containsPoint(int px, int py) const override {
        auto points = getLinePoints();
        for (const auto& pt : points) {
            if (pt.first == px && pt.second == py) {
                return true;
            }
        }
        return false;
    }

    void draw(std::vector<std::vector<char>> &grid, int boardWidth, int boardHeight) const override {
        char symbol = getColorChar();
        auto points = getLinePoints();

        for (const auto& pt : points) {
            int px = pt.first;
            int py = pt.second;
            if (px >= 0 && px < boardWidth && py >= 0 && py < boardHeight) {
                grid[py][px] = symbol;
            }
        }
    }
};


#endif //SHAPES_BLACKBOARD_LINE_H
