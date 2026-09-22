//
// Created by alex on 22.09.26.
//

#include "Menu.h"

#include "Menu.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include "Line.h"
#include <iostream>

Menu::Menu(Board &b) : board(b), isRunning(true) {}

bool Menu::isColor(const std::string &token) {
    return (token == "red" || token == "green" || token == "blue" ||
            token == "yellow" || token == "magenta" || token == "cyan" ||
            token == "orange" || token == "pink" || token == "grey" ||
            token == "gray" || token == "white" || token == "*");
}

bool Menu::isShapeType(const std::string &token) {
    return (token == "rectangle" || token == "circle" ||
            token == "triangle" || token == "line");
}

void Menu::run() {
    std::string line;
    std::cout << ">> ";
    while (isRunning && std::getline(std::cin, line)) {
        processCommand(line);
        if (isRunning) {
            std::cout << ">> ";
        }
    }
}

void Menu::processCommand(const std::string &line) {
    if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos) {
        return;
    }

    std::stringstream ss(line);
    std::string command;
    if (!(ss >> command)) return;

    if (command == "draw") {
        board.draw();
    }
    else if (command == "list") {
        board.list();
    }
    else if (command == "clear") {
        board.clear();
    }
    else if (command == "shapes") {
        board.printSupportedShapes();
    }
    else if (command == "remove") {
        board.removeSelected();
    }
    else if (command == "add") {
        handleAdd(ss);
    }
    else if (command == "select") {
        handleSelect(ss);
    }
    else if (command == "move") {
        handleMove(ss);
    }
    else if (command == "paint") {
        handlePaint(ss);
    }
    else if (command == "edit") {
        handleEdit(ss);
    }
    else if (command == "save") {
        handleSave(ss);
    }
    else if (command == "load") {
        handleLoad(ss);
    }
    else if (command == "exit" || command == "quit") {
        isRunning = false;
    }
    else {
        std::cout << "Unknown command, try again\n";
    }
}

void Menu::handleAdd(std::stringstream &ss) {
    std::string token1, token2, token3;
    bool isFilled = false;
    std::string color = "";
    std::string shapeType = "";

    if (!(ss >> token1)) {
        std::cout << "Error: invalid add command\n";
        return;
    }

    if (token1 == "fill") {
        isFilled = true;
        if (!(ss >> token2)) { std::cout << "Error: missing shape type\n"; return; }
        if (isColor(token2)) {
            color = (token2 == "*" ? "" : token2);
            if (!(ss >> shapeType)) { std::cout << "Error: missing shape type\n"; return; }
        }
        else {
            shapeType = token2;
        }
    } else if (token1 == "frame") {
        isFilled = false;
        if (!(ss >> token2)) { std::cout << "Error: missing shape type\n"; return; }
        if (isColor(token2)) {
            color = (token2 == "*" ? "" : token2);
            if (!(ss >> shapeType)) { std::cout << "Error: missing shape type\n"; return; }
        }
        else {
            shapeType = token2;
        }
    } else if (isColor(token1)) {
        color = (token1 == "*" ? "" : token1);
        if (!(ss >> shapeType)) { std::cout << "Error: missing shape type\n"; return; }
    }
    else {
        shapeType = token1;
    }

    std::string id = board.getNextId();

    if (shapeType == "rectangle") {
        int x, y, w, h;
        if (ss >> x >> y >> w >> h) {
            board.addShape(std::make_unique<Rectangle>(id, x, y, color, isFilled, w, h));
            std::cout << "< " << id << " rectangle " << (color.empty() ? "*" : color) << " " << x << " " << y << " " << w << " " << h << "\n";
        }
        else {
            std::cout << "Error: invalid parameters for rectangle\n";
        }
    } else if (shapeType == "circle") {
        int x, y, r;
        if (ss >> x >> y >> r) {
            board.addShape(std::make_unique<Circle>(id, x, y, color, isFilled, r));
            std::cout << "< " << id << " circle " << (color.empty() ? "*" : color) << " " << x << " " << y << " " << r << "\n";
        }
        else {
            std::cout << "Error: invalid parameters for circle\n";
        }
    } else if (shapeType == "triangle") {
        int x1, y1, x2, y2, x3, y3;
        if (ss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3) {
            board.addShape(std::make_unique<Triangle>(id, x1, y1, color, isFilled, x2, y2, x3, y3));
            std::cout << "< " << id << " triangle " << (color.empty() ? "*" : color) << " " << x1 << " " << y1 << " " << x2 << " " << y2 << " " << x3 << " " << y3 << "\n";
        }
        else {
            std::cout << "Error: invalid parameters for triangle\n";
        }
    } else if (shapeType == "line") {
        int x1, y1, x2, y2;
        if (ss >> x1 >> y1 >> x2 >> y2) {
            board.addShape(std::make_unique<Line>(id, x1, y1, color, x2, y2));
            std::cout << "< " << id << " line " << (color.empty() ? "*" : color) << " " << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";
        }
        else {
            std::cout << "Error: invalid parameters for line\n";
        }
    } else {
        std::cout << "Error: unknown shape type " << shapeType << "\n";
    }
}

void Menu::handleSelect(std::stringstream &ss) {
    std::string arg1;
    if (ss >> arg1) {
        int y;
        if (ss >> y) {
            try {
                int x = std::stoi(arg1);
                board.selectedByCoordinates(x, y);
            }
            catch (...) {
                std::cout << "Error: invalid coordinates\n";
            }
        }
        else {
            board.selectById(arg1);
        }
    }
    else {
        std::cout << "Error: missing select parameter\n";
    }
}

void Menu::handleMove(std::stringstream &ss) {
    int dx, dy;
    if (ss >> dx >> dy) {
        board.moveSelected(dx, dy);
    }
    else {
        std::cout << "Error: missing move parameters (dx dy)\n";
    }
}

void Menu::handlePaint(std::stringstream &ss) {
    std::string color;
    if (ss >> color) {
        board.paintSelected(color);
    }
    else {
        std::cout << "Error: missing color\n";
    }
}

void Menu::handleEdit(std::stringstream &ss) {
    board.editSelected(ss);
}

void Menu::handleSave(std::stringstream &ss) {
    std::string filename;
    if (ss >> filename) {
        board.saveToFile(filename);
    }
    else {
        std::cout << "Error: missing filename for save\n";
    }
}

void Menu::handleLoad(std::stringstream &ss) {
    std::string filename;
    if (ss >> filename) {
        board.loadFromFile(filename);
    }
    else {
        std::cout << "Error: missing filename for load\n";
    }
}