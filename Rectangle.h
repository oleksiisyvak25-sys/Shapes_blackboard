#ifndef SHAPES_BLACKBOARD_RECTANGLE_H
#define SHAPES_BLACKBOARD_RECTANGLE_H

#include "Shape.h"

class Rectangle : public Shape {
private:
    int width;
    int height;

public:
    Rectangle(std::string id, int x, int y, std::string color, bool isFilled, int width, int height);

    std::string getType() const override;
    std::string getInfo() const override;
    bool containsPoint(int px, int py) const override;
    void draw(std::vector<std::vector<char>> &grid, int boardWidth, int boardHeight) const override;
    std::string serialize() const override;
    bool edit(const std::string &args) override;
};

#endif //SHAPES_BLACKBOARD_RECTANGLE_H