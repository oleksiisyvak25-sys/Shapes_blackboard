//
// Created by alex on 14.09.26.
//

#include "Board.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include "Line.h"

Board::Board(int width, int height) {
    this->width = width;
    this->height = height;
    this->selectedShape = nullptr;
    this->nextId = 1;
}

std::string Board::generateId() {
    std::string result = std::to_string(this->nextId);

    while (result.length() < 4) {
        result = "0" + result;
    }

    this->nextId = this->nextId + 1;

    return result;
}

std::string Board::getNextId() {
    return this->generateId();
}

void Board::addShape(std::unique_ptr<Shape> shape) {
    this->shapes.push_back(std::move(shape));
}

void Board::draw() const {
    std::vector<std::vector<char>> grid(this->height, std::vector<char>(this->width, ' '));

    for (size_t i = 0; i < this->shapes.size(); i++ ) {
        this->shapes[i]->draw(grid,this->width, this->height);
    }

    std::cout << "    ";
    for (int c = 0; c < this->width; c++) {
        if (c % 10 == 0) {
            std::cout << (c / 10);
        } else {
            std::cout << " ";
        }
    }
    std::cout << "\n";

    std::cout << "    ";
    for (int c = 0; c < this->width; c++) {
        std::cout << (c % 10);
    }
    std::cout << "\n";

    std::cout << "   +";
    for (int c = 0; c < this->width; c++) {
        std::cout << "-";
    }
    std::cout << "+\n";

    for (int r = 0; r < this->height; r++) {
        if (r < 10) {
            std::cout << " " << r << " |";
        } else {
            std::cout << r << " |";
        }

        for (int c = 0; c < this->width; c++) {
            char cell = grid[r][c];
            if (cell == ' ') {
                std::cout << ' ';
            }
            else {
                std::string ansiColor = "\033[37m";
                if (cell == 'r' || cell == 'R') ansiColor = "\033[31m";
                else if (cell == 'g' || cell == 'G') ansiColor = "\033[32m";
                else if (cell == 'y' || cell == 'Y') ansiColor = "\033[33m";
                else if (cell == 'b' || cell == 'B') ansiColor = "\033[34m";
                else if (cell == 'm' || cell == 'M') ansiColor = "\033[35m";
                else if (cell == 'c' || cell == 'C') ansiColor = "\033[36m";
                else if (cell == 'o' || cell == 'O') ansiColor = "\033[38;5;208m";
                else if (cell == 'p' || cell == 'P') ansiColor = "\033[38;5;213m";
                else if (cell == 'a' || cell == 'A') ansiColor = "\033[90m";
                else if (cell == 'w' || cell == 'W') ansiColor = "\033[97m";
                else if (cell == '*') ansiColor = "\033[1m";

                std::cout << ansiColor << cell << "\033[0m";
            }
        }
        std::cout << "|\n";
    }

    std::cout << "   +";
    for (int c = 0; c < this->width; c++) {
        std::cout << "-";
    }
    std::cout << "+\n";
}

void Board::list() const {
    for (size_t i = 0; i < this->shapes.size(); i++) {
        std::cout << this->shapes[i]->getInfo() << "\n";
    }
}

void Board::clear() {
    this->shapes.clear();
    this->selectedShape = nullptr;
    std::cout << "Board is clear\n";
}

bool Board::selectById(const std::string &id) {
    for (size_t i = 0; i < this->shapes.size(); i++) {
        if (this->shapes[i]->getId() == id) {
            this->selectedShape = this->shapes[i].get();
            std::cout << this->selectedShape->getInfo() << "\n";
            return true;
        }
    }
    std::cout << "Shape was not found\n";
    return false;
}

bool Board::selectedByCoordinates(int px, int py) {
    if (this->shapes.empty()) {
        std::cout << "Shape was not found\n";
        return false;
    }

    for (int i = (int)this->shapes.size() - 1; i >= 0; i--) {
        if (this->shapes[i]->containsPoint(px, py)) {
            this->selectedShape = this->shapes[i].get();
            std::cout << this->selectedShape->getInfo() << "\n";
            return true;
        }
    }

    std::cout << "Shape was not found\n";
    return false;
}

bool Board::removeSelected() {
    if (this->selectedShape == nullptr) {
        std::cout << "There is no shape selected\n";
        return false;
    }

    for (size_t i = 0; i < this->shapes.size(); i++) {
        if (this->shapes[i].get() == this->selectedShape) {
            std::cout << this->selectedShape->getId() << " " << this->selectedShape->getType() << " was removed\n";
            this->shapes.erase(this->shapes.begin() + i);
            this->selectedShape = nullptr;
            return true;
        }
    }
    return false;
}

bool Board::paintSelected(const std::string &newColor) {
    if (this->selectedShape == nullptr) {
        std::cout << "There is no shape selected\n";
        return false;
    }

    this->selectedShape->setColor(newColor);
    std::cout << this->selectedShape->getId() << " " << this->selectedShape->getType() << " " << newColor << "\n";
    return true;
}

bool Board::moveSelected(int newX, int newY) {
    if (selectedShape != nullptr) {
        selectedShape->move(newX, newY);
        std::cout << selectedShape->getId() << " " << selectedShape->getType() << " moved\n";
        return true;
    }
    else {
        std::cout << "Error: no shape selected\n";
        return false;
    }
}

void Board::printSupportedShapes() const {
    std::cout << "Supported shapes:\n";
    std::cout << " - rectangle [x] [y] [width] [height]\n";
    std::cout << " - circle [x] [y] [radius]\n";
    std::cout << " - triangle [x] [y] [x2] [y2] [x3] [y3]\n";
    std::cout << " - line [x] [y] [x2] [y2]\n";
    std::cout << "Supported colors:\n"
                 "red\n"
                 "green\n"
                 "yellow\n"
                 "blue\n"
                 "magenta\n"
                 "cyan\n"
                 "orange\n"
                 "pink\n"
                 "grey\n"
                 "white\n";
}

bool Board::editSelected(std::stringstream &ss) {
    if (selectedShape == nullptr) {
        std::cout << "Error: no shape selected\n";
        return false;
    }
    std::string args;
    std::getline(ss, args);

    if (selectedShape->edit(args)) {
        std::cout << selectedShape->getId() << " " << selectedShape->getType() << " edited\n";
        return true;
    } else {
        std::cout << "Error: invalid parameters for edit\n";
        return false;
    }
}

bool Board::saveToFile(const std::string &filepath) const {
    std::ofstream out(filepath);
    if (!out.is_open()) {
        std::cout << "Error: could not open file for writing\n";
        return false;
    }
    for (const auto &s : shapes) {
        out << s->serialize() << "\n";
    }
    std::cout << "Board saved to " << filepath << "\n";
    return true;
}

bool Board::loadFromFile(const std::string &filepath) {
    std::ifstream in(filepath);
    if (!in.is_open()) {
        std::cout << "Error: could not open file for reading\n";
        return false;
    }

    clear();
    std::string type;
    while (in >> type) {
        std::string id = getNextId();
        if (type == "rectangle") {
            int x, y, w, h;
            std::string c, mode;
            in >> x >> y >> c >> mode >> w >> h;
            addShape(std::make_unique<Rectangle>(id, x, y, (c == "*" ? "" : c), (mode == "fill"), w, h));
        } else if (type == "circle") {
            int x, y, r;
            std::string c, mode;
            in >> x >> y >> c >> mode >> r;
            addShape(std::make_unique<Circle>(id, x, y, (c == "*" ? "" : c), (mode == "fill"), r));
        } else if (type == "triangle") {
            int x, y, x2, y2, x3, y3;
            std::string c, mode;
            in >> x >> y >> c >> mode >> x2 >> y2 >> x3 >> y3;
            addShape(std::make_unique<Triangle>(id, x, y, (c == "*" ? "" : c), (mode == "fill"), x2, y2, x3, y3));
        } else if (type == "line") {
            int x1, y1, x2, y2;
            std::string c;
            in >> x1 >> y1 >> c >> x2 >> y2;
            addShape(std::make_unique<Line>(id, x1, y1, (c == "*" ? "" : c), x2, y2));
        }
    }
    std::cout << "Board loaded from " << filepath << "\n";
    return true;
}