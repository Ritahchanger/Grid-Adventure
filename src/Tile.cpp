#include "Tile.h"

Tile::Tile(Type type) : type(type) {}

bool Tile::isWalkable() const {
    return type == Type::Grass;
}

char Tile::getSymbol() const {
    switch(type) {
        case Type::Grass: return '.';
        case Type::Wall: return '#';
        case Type::Water: return '~';
        default: return '?';
    }
}
