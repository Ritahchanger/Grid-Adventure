#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Map.h"
#include "Player.h"
#include "Enemy.h"

class Game {
private:
    Map map;
    Player player;
    std::vector<Enemy> enemies;
    bool running;
    int score;

    bool isPositionFree(int x, int y) const;

    void movePlayer(int dx, int dy);
    void attack();
    void enemyTurn();

public:
    Game();

    void draw();
    void handleInput();
    void gameLoop();
};

#endif // GAME_H
