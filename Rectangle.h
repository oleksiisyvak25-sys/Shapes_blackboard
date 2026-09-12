//
// Created by alex on 12.09.26.
//

#ifndef SHAPES_BLACKBOARD_BOX_H
#define SHAPES_BLACKBOARD_BOX_H
#include "Shape.h"
#include <string>
#include <vector>

class Rectangle : public Shape {
protected:
    int width;
    int height;
public:
    Rectangle(std::string id, int x, int y, std::string color, bool isFilled, int width, int height)
        : Shape(std::move(id), x, y, std::move(color), isFilled), width(width), height(height) {}

    std::string getType() const override {
        return "rectangle";
    }

    std::string getInfo() const override {
        std::string inside = "frame";
        if (isFilled) {
            inside = "fill";
        }
        return id + " " + getType() + " " + color + " " + inside + " " + std::to_string(x) +
            " " + std::to_string(y) + " " + std::to_string(width) + " " + std::to_string(height);
    }

    bool containsPoint(int px, int py) const override {
        bool insideBounds = (px >= x && px < x + width && py >= y && py < y + height);

        if (!insideBounds) {
            return false;
        }

        if (isFilled) {
            return true;
        }

        bool onBorder = (px == x || px == x + width - 1 || py == y || py == y + height - 1);
        return onBorder;
    }

    void draw(std::vector<std::vector<char>> &grid, int boardWidth, int boardHeight) const override {
        char symbol = getColorChar();

        for (int r = 0; r < height; ++r) {
            int currentY = y + r;
            if (currentY < 0 || currentY >= boardHeight) continue;

            for (int c = 0; c < width; ++c) {
                int currentX = x + c;
                if (currentX < 0 || currentX >= boardWidth) continue;

                if (!isFilled) {
                    bool isBorder = (r == 0 || r == height - 1 || c == 0 || c == width - 1);
                    if (!isBorder) continue;
                }

                grid[currentY][currentX] = symbol;
            }
        }
    }
};


#endif //SHAPES_BLACKBOARD_BOX_H
