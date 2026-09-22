#ifndef SHAPES_BLACKBOARD_CIRCLE_H
#define SHAPES_BLACKBOARD_CIRCLE_H

#include "Shape.h"

class Circle : public Shape {
private:
    int radius;

public:
    Circle(std::string id, int x, int y, std::string color, bool isFilled, int radius);

    std::string getType() const override;
    std::string getInfo() const override;
    bool containsPoint(int px, int py) const override;
    void draw(std::vector<std::vector<char>> &grid, int boardWidth, int boardHeight) const override;
    std::string serialize() const override;
    bool edit(const std::string &args) override;
};

#endif //SHAPES_BLACKBOARD_CIRCLE_H