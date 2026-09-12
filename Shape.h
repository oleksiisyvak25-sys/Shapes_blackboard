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
    Shape(std::string id, int x, int y, std::string color, bool isFilled) {
        this.id = std::move(id);
        this.x = x;
        this.y = y;
        this.color = std::move(color);
        this.isFilled = isFilled;
    }
    
};


#endif //SHAPES_BLACKBOARD_SHAPE_H
