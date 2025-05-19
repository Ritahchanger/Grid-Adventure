#include "Character.h"

Character::Character(int x, int y, char symbol) : x(x), y(y), symbol(symbol) {}

int Character::getX() const {
    return x;
}

int Character::getY() const {
    return y;
}

char Character::getSymbol() const {
    return symbol;
}

void Character::setPosition(int x, int y) {
    this->x = x;
    this->y = y;
}
