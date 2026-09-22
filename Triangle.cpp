#include "Triangle.h"
#include <algorithm>
#include <sstream>

Triangle::Triangle(std::string id, int x1, int y1, std::string color, bool isFilled, int x2, int y2, int x3, int y3)
    : Shape(std::move(id), x1, y1, std::move(color), isFilled), x2(x2), y2(y2), x3(x3), y3(y3) {}

double Triangle::sign(double p1x, double p1y, double p2x, double p2y, double p3x, double p3y) const {
    return (p1x - p3x) * (p2y - p3y) - (p2x - p3x) * (p1y - p3y);
}

bool Triangle::isInside(double px, double py, double ax, double ay, double bx, double by, double cx, double cy) const {
    double d1 = sign(px, py, ax, ay, bx, by);
    double d2 = sign(px, py, bx, by, cx, cy);
    double d3 = sign(px, py, cx, cy, ax, ay);

    bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

void Triangle::move(int dx, int dy) {
    Shape::move(dx, dy);
    x2 += dx;
    y2 += dy;
    x3 += dx;
    y3 += dy;
}

std::string Triangle::getType() const {
    return "triangle";
}

std::string Triangle::getInfo() const {
    std::string mode = isFilled ? "fill" : "frame";
    return id + " " + getType() + " " + color + " " + mode + " " +
           std::to_string(x) + " " + std::to_string(y) + " " +
           std::to_string(x2) + " " + std::to_string(y2) + " " +
           std::to_string(x3) + " " + std::to_string(y3);
}

bool Triangle::containsPoint(int px, int py) const {
    double ax = static_cast<double>(x), ay = static_cast<double>(y);
    double bx = static_cast<double>(x2), by = static_cast<double>(y2);
    double cx = static_cast<double>(x3), cy = static_cast<double>(y3);
    double pfx = static_cast<double>(px), pfy = static_cast<double>(py);

    if (!isInside(pfx, pfy, ax, ay, bx, by, cx, cy)) {
        return false;
    }

    if (isFilled) {
        return true;
    }

    // Для frame перевіряємо, чи є точка контуром (сусід лежить зовні)
    for (int nx = -1; nx <= 1; ++nx) {
        for (int ny = -1; ny <= 1; ++ny) {
            if (!isInside(pfx + nx, pfy + ny, ax, ay, bx, by, cx, cy)) {
                return true;
            }
        }
    }
    return false;
}

void Triangle::draw(std::vector<std::vector<char>> &grid, int boardWidth, int boardHeight) const {
    char symbol = getColorChar();

    int minX = std::max(0, std::min({x, x2, x3}));
    int maxX = std::min(boardWidth - 1, std::max({x, x2, x3}));
    int minY = std::max(0, std::min({y, y2, y3}));
    int maxY = std::min(boardHeight - 1, std::max({y, y2, y3}));

    for (int py = minY; py <= maxY; ++py) {
        for (int px = minX; px <= maxX; ++px) {
            double ax = static_cast<double>(x), ay = static_cast<double>(y);
            double bx = static_cast<double>(x2), by = static_cast<double>(y2);
            double cx = static_cast<double>(x3), cy = static_cast<double>(y3);
            double pfx = static_cast<double>(px), pfy = static_cast<double>(py);

            if (isInside(pfx, pfy, ax, ay, bx, by, cx, cy)) {
                if (isFilled) {
                    grid[py][px] = symbol;
                } else {
                    bool isBorder = false;
                    for (int nx = -1; nx <= 1; ++nx) {
                        for (int ny = -1; ny <= 1; ++ny) {
                            if (!isInside(px + nx, py + ny, ax, ay, bx, by, cx, cy)) {
                                isBorder = true;
                                break;
                            }
                        }
                        if (isBorder) break;
                    }
                    if (isBorder) {
                        grid[py][px] = symbol;
                    }
                }
            }
        }
    }
}

std::string Triangle::serialize() const {
    return "triangle " + std::to_string(x) + " " + std::to_string(y) + " " +
           (color.empty() ? "*" : color) + " " + (isFilled ? "fill" : "frame") + " " +
           std::to_string(x2) + " " + std::to_string(y2) + " " +
           std::to_string(x3) + " " + std::to_string(y3);
}

bool Triangle::edit(const std::string &args) {
    std::stringstream ss(args);
    int nx1, ny1, nx2, ny2, nx3, ny3;
    if (ss >> nx1 >> ny1 >> nx2 >> ny2 >> nx3 >> ny3) {
        x = nx1;   y = ny1;
        x2 = nx2;  y2 = ny2;
        x3 = nx3;  y3 = ny3;
        return true;
    }
    return false;
}