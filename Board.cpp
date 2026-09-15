//
// Created by alex on 14.09.26.
//

#include "Board.h"
#include <iostream>
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
    if (this->selectedShape == nullptr) {
        std::cout << "There is no shape selected\n";
        return false;
    }

    this->selectedShape->setPosition(newX, newY);

    for (size_t i = 0; i < this->shapes.size(); i++) {
        if (this->shapes[i].get() == this->selectedShape) {
            std::unique_ptr<Shape> movedShape = std::move(this->shapes[i]);
            this->shapes.erase(this->shapes.begin() + i);
            this->shapes.push_back(std::move(movedShape));
            this->selectedShape = this->shapes.back().get();
            break;
        }
    }

    std::cout << this->selectedShape->getId() << " " << this->selectedShape->getType() << " moved\n";
    return true;
}