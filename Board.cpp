//
// Created by alex on 14.09.26.
//

#include "Board.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

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

    for (int r = 0; r < this->height; r++) {
        for (int c = 0; c < this-> width; c++) {
            std::cout << grid[r][c];
        }
        std::cout << "\n";
    }
}
