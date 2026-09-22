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
    Shape(std::string id_, int x_, int y_, std::string color_, bool isFilled_);
    virtual ~Shape() = default;

    std::string getId() const;
    std::string getColor() const;
    int getX() const;
    int getY() const;
    void setColor(const std::string& newColor);
    void setPosition(int newX, int newY);
    char getColorChar() const;

    virtual void move(int dx, int dy);
    virtual void draw(std::vector<std::vector<char>>& grid, int boardWidth, int boardHeight) const = 0;
    virtual bool containsPoint(int px, int py) const = 0;
    virtual bool edit(const std::string &args) = 0;
    virtual std::string getInfo() const = 0;
    virtual std::string getType() const = 0;
    virtual std::string serialize() const = 0;
};

#endif //SHAPES_BLACKBOARD_SHAPE_H