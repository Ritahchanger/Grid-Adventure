#include "Player.h"

Player::Player(int startX, int startY) : x(startX), y(startY), symbol('@'), health(10) {}

void Player::takeDamage(int dmg) {
    health -= dmg;
    if (health < 0) health = 0;
}

bool Player::isAlive() const {
    return health > 0;
}
