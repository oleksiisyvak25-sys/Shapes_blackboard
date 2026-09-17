#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include "Board.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include "Line.h"

int main() {
    Board board (80,25);
    std::string line;
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
            if (line.find("line") != std::string::npos) {
                std::stringstream lineStream(line);
                std::string action;
                lineStream >> action;

                std::string color = "";
                int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

                std::string t;
                std::vector<std::string> words;
                while (lineStream >> t) {
                    words.push_back(t);
                }

                for (size_t i = 0; i < words.size(); ++i) {
                    if (words[i] != "line" && words[i] != "add" && color.empty() && !std::isdigit(words[i][0])) {
                        color = words[i];
                    }
                }

                std::vector<int> coords;
                for (const auto& w : words) {
                    try {
                        coords.push_back(std::stoi(w));
                    } catch (...) {}
                }

                if (coords.size() >= 4) {
                    x1 = coords[coords.size() - 4];
                    y1 = coords[coords.size() - 3];
                    x2 = coords[coords.size() - 2];
                    y2 = coords[coords.size() - 1];

                    std::string id = board.getNextId();
                    board.addShape(std::make_unique<Line>(id, x1, y1, color, x2, y2));
                    std::cout << "< " << id << " line " << (color.empty() ? "*" : color) << " " << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";
                } else {
                    std::cout << "Error: invalid number of coordinates for line\n";
                }
            }
            else {
                std::string mode;
                if (!(ss >> mode)) {
                    std::cout << "Error: missing arguments\n";
                } else if (mode != "fill" && mode != "frame") {
                    std::cout << "Error: invalid mode, Use 'fill' or 'frame'\n";
                } else {
                    bool isFilled = (mode == "fill");

                    std::string nextWord;
                    ss >> nextWord;

                    std::string color = "";
                    std::string shapeType = "";

                    if (nextWord == "rectangle" || nextWord == "circle" || nextWord == "triangle") {
                        shapeType = nextWord;
                        color = "";
                    } else {
                        color = nextWord;
                        ss >> shapeType;
                    }

                    if (shapeType == "rectangle") {
                        int x, y, width, height;
                        if (ss >> x >> y >> width >> height) {
                            std::string id = board.getNextId();
                            board.addShape(std::make_unique<Rectangle>(id, x, y, color, isFilled, width, height));
                            std::cout << "< " << id << " " << shapeType << " " << (color.empty() ? "*" : color) << " " << width << " " << height << "\n";
                        } else {
                            std::cout << "Error: invalid number of arguments\n";
                        }
                    }
                    else if (shapeType == "circle") {
                        int x, y, radius;
                        if (ss >> x >> y >> radius) {
                            std::string id = board.getNextId();
                            board.addShape(std::make_unique<Circle>(id, x, y, color, isFilled, radius));
                            std::cout << "< " << id << " " << shapeType << " " << (color.empty() ? "*" : color) << " " << radius << "\n";
                        } else {
                            std::cout << "Error: invalid number of arguments\n";
                        }
                    }
                    else if (shapeType == "triangle") {
                        int x, y, x2, y2, x3, y3;
                        if (ss >> x >> y >> x2 >> y2 >> x3 >> y3) {
                            std::string id = board.getNextId();
                            board.addShape(std::make_unique<Triangle>(id, x, y, color, isFilled, x2, y2, x3, y3));
                            std::cout << "< " << id << " " << shapeType << " " << (color.empty() ? "*" : color) << " " << x2 << " " << y2 << " " << x3 << " " << y3 << "\n";
                        } else {
                            std::cout << "Error: invalid number of arguments for triangle\n";
                        }
                    }
                    else {
                        std::cout << "Error: unknown shape, try again\n";
                    }
                }
            }
        }
        else if (command == "select") {
            std::string arg1, arg2;
            if (ss >> arg1) {
                if (ss >> arg2) {
                    int x = std::stoi(arg1);
                    int y = std::stoi(arg2);
                    board.selectedByCoordinates(x, y);
                } else {
                    board.selectById(arg1);
                }
            } else {
                std::cout << "Error: missing select argument\n";
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
        else if (command == "shapes") {
            board.printSupportedShapes();
        }
        else if (command == "edit") {
            board.editSelected(ss);
        }
        else if (command == "save") {
            std::string filename;
            if (!(ss >> filename)) {
                filename = "File.txt";
            }
            board.saveToFile(filename);
        }
        else if (command == "load") {
            std::string filename;
            if (!(ss >> filename)) {
                filename = "File.txt";
            }
            board.loadFromFile(filename);
        }

        else {
            std::cout << "Unknown command, try again\n";
        }
        std::cout << ">> ";
    }
    return 0;
}
