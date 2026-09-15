//
// Created by alex on 14.09.26.
//

#ifndef SHAPES_BLACKBOARD_BOARD_H
#define SHAPES_BLACKBOARD_BOARD_H

#include <vector>
#include <memory>
#include <string>
#include "Shape.h"


class Board {
protected:
    int width;
    int height;
    std::vector<std::unique_ptr<Shape>> shapes;
    Shape* selectedShape;
    int nextId;

    std::string generateId();

public:
    Board(int width = 80, int height = 25);

    void addShape(std::unique_ptr<Shape> shape);

    void draw() const;

    void clear();

    void list() const;

    bool selectedById(const std::string& id);

    bool selectedByCoordinates(int px, int py);

    bool removeSelected();

    bool moveSelected(int newX, int newY);

    bool paintSelected(const std::string& newColor);

    Shape* getSelectedShape() const {
        return selectedShape;
    }

    std::string getNextId();
};


#endif //SHAPES_BLACKBOARD_BOARD_H
