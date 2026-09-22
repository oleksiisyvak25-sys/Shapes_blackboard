#include "Shape.h"
#include <cctype>

Shape::Shape(std::string id_, int x_, int y_, std::string color_, bool isFilled_)
    : id(std::move(id_)), x(x_), y(y_), color(std::move(color_)), isFilled(isFilled_) {}

std::string Shape::getId() const {
    return id;
}

std::string Shape::getColor() const {
    return color;
}

int Shape::getX() const {
    return x;
}

int Shape::getY() const {
    return y;
}

void Shape::setColor(const std::string& newColor) {
    color = newColor;
}

void Shape::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

void Shape::move(int dx, int dy) {
    x += dx;
    y += dy;
}

char Shape::getColorChar() const {
    if (color.empty()) return '*';
    if (color == "red") return 'r';
    if (color == "green") return 'g';
    if (color == "blue") return 'b';
    if (color == "yellow") return 'y';
    if (color == "cyan") return 'c';
    if (color == "magenta") return 'm';
    if (color == "orange") return 'o';
    if (color == "pink") return 'p';
    if (color == "gray" || color == "grey") return 'a';
    if (color == "white") return 'w';
    return static_cast<char>(std::tolower(static_cast<unsigned char>(color[0])));
}