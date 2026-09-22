#ifndef SHAPES_BLACKBOARD_LINE_H
#define SHAPES_BLACKBOARD_LINE_H

#include "Shape.h"
#include <utility>

class Line : public Shape {
private:
    int x2, y2;
    std::vector<std::pair<int, int>> getLinePoints() const;

public:
    Line(std::string id, int x1, int y1, std::string color, int x2, int y2);

    void move(int dx, int dy) override;
    std::string getType() const override;
    std::string getInfo() const override;
    bool containsPoint(int px, int py) const override;
    void draw(std::vector<std::vector<char>> &grid, int boardWidth, int boardHeight) const override;
    std::string serialize() const override;
    bool edit(const std::string &args) override;
};

#endif //SHAPES_BLACKBOARD_LINE_H