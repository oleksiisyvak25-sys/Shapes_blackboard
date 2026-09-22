//
// Created by alex on 22.09.26.
//

#ifndef SHAPES_BLACKBOARD_MENU_H
#define SHAPES_BLACKBOARD_MENU_H

#include "Board.h"
#include <sstream>
#include <string>

class Menu {
private:
    Board &board;
    bool isRunning;

    void handleAdd(std::stringstream &ss);
    void handleSelect(std::stringstream &ss);
    void handleMove(std::stringstream &ss);
    void handlePaint(std::stringstream &ss);
    void handleEdit(std::stringstream &ss);
    void handleSave(std::stringstream &ss);
    void handleLoad(std::stringstream &ss);

    static bool isColor(const std::string &token);
    static bool isShapeType(const std::string &token);

public:
    explicit Menu(Board &b);

    void run();

    void processCommand(const std::string &line);

};


#endif //SHAPES_BLACKBOARD_MENU_H
