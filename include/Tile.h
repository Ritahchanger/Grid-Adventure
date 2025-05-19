#ifndef TILE_H
#define TILE_H

class Tile {
public:
    enum class Type {
        Grass,
        Wall,
        Water
    };

    Tile(Type type = Type::Grass);
    
    bool isWalkable() const;
    char getSymbol() const;

private:
    Type type;
};

#endif 
