//
// Created by alex on 15.09.26.
//

#ifndef SHAPES_BLACKBOARD_CIRCLE_H
#define SHAPES_BLACKBOARD_CIRCLE_H

#include "Shape.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <istream>

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
        double dx = (double)(px - x);
        double dy = (double)(py - y) * 2.0;
        double distSquared = dx * dx + dy * dy;
        double r = radius * 2.0;

        if (isFilled) {
            return distSquared <= r * r;
        } else {
            double dist = std::sqrt(distSquared);
            return std::abs(dist - r) < 1.5;
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

    std::string serialize() const override {
        return "circle " + std::to_string(x) + " " + std::to_string(y) + " " +
               (color.empty() ? "*" : color) + " " + (isFilled ? "fill" : "frame") + " " +
               std::to_string(radius);
    }

    bool edit(const std::string &args) override {
        std::stringstream ss(args);
        int nx, ny, nr;
        if (ss >> nx >> ny >> nr) {
            x = nx;
            y = ny;
            radius = nr;
            return true;
        }

        ss.clear();
        ss.str(args);
        if (ss >> nr) {
            radius = nr;
            return true;
        }

        return false;
    }
};

#endif //SHAPES_BLACKBOARD_CIRCLE_H












