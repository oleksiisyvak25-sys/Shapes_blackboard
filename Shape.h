//
// Created by alex on 12.09.26.
//

#ifndef SHAPES_BLACKBOARD_SHAPE_H
#define SHAPES_BLACKBOARD_SHAPE_H
#include <string>
#include <vector>

class Shape {
protected:
    std::string id;
    int x;
    int y;
    std::string color;
    bool isFilled;

public:
    Shape(std::string id_, int x_, int y_, std::string color_, bool isFilled_) {
        id = std::move(id_);
        x = x_;
        y = y_;
        color = std::move(color_);
        isFilled = isFilled_;
    }

    virtual ~Shape() = default;

    std::string getId() const {
        return id;
    }

    std::string getColor() const {
        return color;
    }

    virtual void move(int dx, int dy) {
        x += dx;
        y += dy;
    }

    void setColor(const std::string& newColor) {
        color = newColor;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    void setPosition(int newX, int newY) {
        x = newX;
        y = newY;
    }

    char getColorChar() const {
        if (color.empty()) {
            return '*';
        }
        return color[0];
    }

    virtual void draw(std::vector<std::vector<char>>& grid, int boardWidth, int boardHeight) const = 0;
    virtual bool containsPoint(int px, int py) const = 0;
    virtual std::string getInfo() const = 0;
    virtual std::string getType() const = 0;
};


#endif //SHAPES_BLACKBOARD_SHAPE_H
