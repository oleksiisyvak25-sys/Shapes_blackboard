//
// Created by alex on 15.09.26.
//

#ifndef SHAPES_BLACKBOARD_CIRCLE_H
#define SHAPES_BLACKBOARD_CIRCLE_H

#include "Shape.h"
#include <cmath>

class Circle : public Shape {
private:
    int radius;
public:
    Circle(std::string id, int x, int y, std::string color, bool isFilled, int radius)
        :Shape(std::move(id), x, y, std::move(color), isFilled), radius(radius){}

    std::string getType() const override {
        return "circle";
    }

    std::string getInfo() const override {
        std::string inside = "frame";
        if (isFilled) {
            inside = "fill";
        }
        return id + " " + getType() + " " + color + " " + inside + " " + std::to_string(x) +
            " " + std::to_string(y) + " " + std::to_string(radius);
    }

    bool containsPoint(int px, int py) const override {
        int dx = (px - x) * 2;
        int dy = py - y;
        double distSquared = dx * dx + dy * dy;
        double r = radius * 2;

        if (isFilled) {
            return distSquared <= r * r;
        }
        else {
            double dist = std::sqrt(distSquared);
            return std::abs(dist - r) < 1.2;
        }
    }

    void draw(std::vector<std::vector<char>> &grid, int boardWidth, int boardHeight) const override {
        char symbol = getColorChar();

        for (int ry = -radius; ry <= radius; ++ry) {
            for (int rx = -2 * radius; rx <= 2 * radius; ++rx) {
                int currentX = x + rx;
                int currentY = y + ry;

                if (currentX < 0 || currentX >= boardWidth || currentY < 0 || currentY >= boardHeight) {
                    continue;
                }

                double dx = rx;
                double dy = ry * 2;
                double distSquared = dx * dx + dy * dy;
                double r = radius * 2;

                if (isFilled) {
                    if (distSquared <= r * r) {
                        grid[currentY][currentX] = symbol;
                    }
                }
                else {
                    double dist = std::sqrt(distSquared);
                    if (std::abs(dist - r) < 1.5) {
                        grid[currentY][currentX] = symbol;
                    }
                }
            }
        }
    }

};

#endif //SHAPES_BLACKBOARD_CIRCLE_H












