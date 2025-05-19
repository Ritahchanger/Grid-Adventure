#include "Map.h"
#include <iostream>

Map::Map(int width, int height) : width(width), height(height) {
    grid.resize(height, std::vector<Tile>(width, Tile(Tile::Type::Grass)));
}

void Map::generateDefaultMap() {
    // Simple default map: border walls, inside grass
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
                grid[y][x] = Tile(Tile::Type::Wall);
            else
                grid[y][x] = Tile(Tile::Type::Grass);
        }
    }
}

void Map::printMap() const {
    for (const auto& row : grid) {
        for (const auto& tile : row) {
            std::cout << tile.getSymbol();
        }
        std::cout << "\n";
    }
}

bool Map::isWalkable(int x, int y) const {
    if (x < 0 || y < 0 || x >= width || y >= height) return false;
    return grid[y][x].isWalkable();
}

int Map::getWidth() const {
    return width;
}

int Map::getHeight() const {
    return height;
}
