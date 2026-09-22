#include "Rectangle.h"
#include <sstream>

Rectangle::Rectangle(std::string id, int x, int y, std::string color, bool isFilled, int width, int height)
    : Shape(std::move(id), x, y, std::move(color), isFilled), width(width), height(height) {}

std::string Rectangle::getType() const {
    return "rectangle";
}

std::string Rectangle::getInfo() const {
    std::string inside = isFilled ? "fill" : "frame";
    return id + " " + getType() + " " + color + " " + inside + " " + std::to_string(x) +
           " " + std::to_string(y) + " " + std::to_string(width) + " " + std::to_string(height);
}

bool Rectangle::containsPoint(int px, int py) const {
    bool insideBounds = (px >= x && px < x + width && py >= y && py < y + height);
    if (!insideBounds) {
        return false;
    }
    if (isFilled) {
        return true;
    }
    return (px == x || px == x + width - 1 || py == y || py == y + height - 1);
}

void Rectangle::draw(std::vector<std::vector<char>> &grid, int boardWidth, int boardHeight) const {
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

std::string Rectangle::serialize() const {
    return "rectangle " + std::to_string(x) + " " + std::to_string(y) + " " +
           (color.empty() ? "*" : color) + " " + (isFilled ? "fill" : "frame") + " " +
           std::to_string(width) + " " + std::to_string(height);
}

bool Rectangle::edit(const std::string &args) {
    std::stringstream ss(args);
    int nx, ny, nw, nh;
    if (ss >> nx >> ny >> nw >> nh) {
        x = nx; y = ny;
        width = nw; height = nh;
        return true;
    }
    ss.clear();
    ss.str(args);
    if (ss >> nw >> nh) {
        width = nw; height = nh;
        return true;
    }
    return false;
}