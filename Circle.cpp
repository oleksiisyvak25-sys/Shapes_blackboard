#include "Circle.h"
#include <cmath>
#include <sstream>

Circle::Circle(std::string id, int x, int y, std::string color, bool isFilled, int radius)
    : Shape(std::move(id), x, y, std::move(color), isFilled), radius(radius) {}

std::string Circle::getType() const {
    return "circle";
}

std::string Circle::getInfo() const {
    std::string inside = isFilled ? "fill" : "frame";
    return id + " " + getType() + " " + color + " " + inside + " " + std::to_string(x) +
           " " + std::to_string(y) + " " + std::to_string(radius);
}

bool Circle::containsPoint(int px, int py) const {
    double dx = static_cast<double>(px - x);
    double dy = static_cast<double>(py - y) * 2.0;
    double distSquared = dx * dx + dy * dy;
    double r = radius * 2.0;

    if (isFilled) {
        return distSquared <= r * r;
    } else {
        double dist = std::sqrt(distSquared);
        return std::abs(dist - r) < 1.5;
    }
}

void Circle::draw(std::vector<std::vector<char>> &grid, int boardWidth, int boardHeight) const {
    char symbol = getColorChar();

    for (int ry = -radius; ry <= radius; ++ry) {
        for (int rx = -2 * radius; rx <= 2 * radius; ++rx) {
            int currentX = x + rx;
            int currentY = y + ry;

            if (currentX < 0 || currentX >= boardWidth || currentY < 0 || currentY >= boardHeight) {
                continue;
            }

            double dx = rx;
            double dy = ry * 2.0;
            double distSquared = dx * dx + dy * dy;
            double r = radius * 2.0;

            if (isFilled) {
                if (distSquared <= r * r) {
                    grid[currentY][currentX] = symbol;
                }
            } else {
                double dist = std::sqrt(distSquared);
                if (std::abs(dist - r) < 1.5) {
                    grid[currentY][currentX] = symbol;
                }
            }
        }
    }
}

std::string Circle::serialize() const {
    return "circle " + std::to_string(x) + " " + std::to_string(y) + " " +
           (color.empty() ? "*" : color) + " " + (isFilled ? "fill" : "frame") + " " +
           std::to_string(radius);
}

bool Circle::edit(const std::string &args) {
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