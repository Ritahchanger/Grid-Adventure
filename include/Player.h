#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
    int x, y;          // Player position
    char symbol;       // Character representing the player on the map
    int health;        // Player health

public:
    // Constructor declaration only
    Player(int startX, int startY);

    // Getters
    int getX() const { return x; }
    int getY() const { return y; }
    char getSymbol() const { return symbol; }
    int getHealth() const { return health; }

    // Setters
    void setPosition(int newX, int newY) { x = newX; y = newY; }
    void setHealth(int h) { health = h; }

    // Health-related methods
    void takeDamage(int dmg);
    bool isAlive() const;
};

#endif
