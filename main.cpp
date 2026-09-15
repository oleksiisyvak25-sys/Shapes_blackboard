#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include "Board.h"
#include "Rectangle.h"

int main() {
    Board board (80,25);
    std::string line;
    std::cout << "The format has to be: add fill red rectangle 10 5 20 8\n";
    std::cout << "                     /   /     /     |      /  /  |   \\    \n";
    std::cout << "               action mode color shapeType x  y width height\n";
    std::cout << ">> ";

    while (std::getline(std::cin, line)) {
        if (line.empty()) {
            continue;
        }
        std::stringstream ss(line);
        std::string command;
        ss >> command;

        if (command == "break") {
            break;
        }

        else if (command == "draw") {
            board.draw();
        }

        else if (command == "list") {
            board.list();
        }

        else if (command == "clear") {
            board.clear();
        }

        else if (command == "add") {
            std::string mode, color, shapeType;
            ss >> mode >> color >> shapeType;

            bool isFilled = (mode == "fill");

            if (shapeType == "rectangle") {
                int x, y, width, height;
                if (ss >> x >> y >> width >> height) {
                    std::string id = board.getNextId();
                    board.addShape(std::make_unique<Rectangle>(id, x, y, color, isFilled, width, height));
                    std::cout << "< " << id << " " << shapeType << " " << color << " " << width << " " << height << "\n";
                }
                else {
                    std::cout << "Error: invalid number of arguments\n";
                }
            }
            else {
                std::cout << "Error: unknown shape, try again\n";
            }
        }

        else if (command == "select") {
            std::string firstArg;
            ss >> firstArg;

            int x;
            std::stringstream testNumber(firstArg);

            if (testNumber >> x && !(ss.eof() && firstArg.length() == 4)) {
                int y;
                if (ss >> y) {
                    board.selectedByCoordinates(x, y);
                }
                else {
                    board.selectById(firstArg);
                }
            }
        }

        else if (command == "paint") {
            std::string color;
            if (ss >> color) {
                board.paintSelected(color);
            }
        }

        else if (command == "move") {
            int newX, newY;
            if (ss >> newX >> newY) {
                board.moveSelected(newX, newY);
            }
        }

        else if (command == "remove") {
            board.removeSelected();
        }

        else {
            std::cout << "Unknown command, try again\n";
        }
        std::cout << ">> ";
    }
    return 0;
}







