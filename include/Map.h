#ifndef MAP_H
#define MAP_H

#include <vector>
#include "Tile.h"

class Map {
public:
    Map(int width, int height);
    void generateDefaultMap(); 
    void printMap() const;
    
    bool isWalkable(int x, int y) const;
    int getWidth() const;
    int getHeight() const;

private:
    int width, height;
    std::vector<std::vector<Tile>> grid;
};

#endif // MAP_H
