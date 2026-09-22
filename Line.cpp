#include "Line.h"
#include <cmath>
#include <cstdlib>
#include <sstream>

Line::Line(std::string id, int x1, int y1, std::string color, int x2, int y2)
    : Shape(std::move(id), x1, y1, std::move(color), true), x2(x2), y2(y2) {}

std::vector<std::pair<int, int>> Line::getLinePoints() const {
    std::vector<std::pair<int, int>> points;
    int x0 = x;
    int y0 = y;
    int x1 = x2;
    int y1 = y2;

    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        points.push_back({x0, y0});
        if (x0 == x1 && y0 == y1) break;

        int e = 2 * err;
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

void Line::move(int dx, int dy) {
    Shape::move(dx, dy);
    x2 += dx;
    y2 += dy;
}

std::string Line::getType() const {
    return "line";
}

std::string Line::getInfo() const {
    return id + " " + getType() + " " + color + " " +
           std::to_string(x) + " " + std::to_string(y) + " " +
           std::to_string(x2) + " " + std::to_string(y2);
}

bool Line::containsPoint(int px, int py) const {
    auto points = getLinePoints();
    for (const auto& pt : points) {
        if (pt.first == px && pt.second == py) {
            return true;
        }
    }
    return false;
}

void Line::draw(std::vector<std::vector<char>> &grid, int boardWidth, int boardHeight) const {
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

std::string Line::serialize() const {
    return "line " + std::to_string(x) + " " + std::to_string(y) + " " +
           (color.empty() ? "*" : color) + " " +
           std::to_string(x2) + " " + std::to_string(y2);
}

bool Line::edit(const std::string &args) {
    std::stringstream ss(args);
    int nx1, ny1, nx2, ny2;
    if (ss >> nx1 >> ny1 >> nx2 >> ny2) {
        x = nx1;   y = ny1;
        x2 = nx2;  y2 = ny2;
        return true;
    }
    return false;
}