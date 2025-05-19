// Game.cpp
#include "Game.h"
#include <iostream>
#include <cstdlib>   // system()
#include <limits>
#include <cctype>
#include <unistd.h>  // for read()
#include <termios.h> // for terminal mode
#include <cmath>     // for abs()

// Terminal raw mode for arrow keys (Linux/macOS)
char getInput() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(STDIN_FILENO, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON; // disable buffering
    old.c_lflag &= ~ECHO;   // disable echo
    if (tcsetattr(STDIN_FILENO, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(STDIN_FILENO, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON; // restore buffering
    old.c_lflag |= ECHO;   // restore echo
    if (tcsetattr(STDIN_FILENO, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}

// --- Player class additions ---

// Add these in your Player class in Player.h / Player.cpp (not shown here):
// int health = 10;
// int getHealth() const { return health; }
// void takeDamage(int dmg) { health -= dmg; if (health < 0) health = 0; }

// ---------------------------------------------------------

Game::Game()
    : map(40, 20), player(1, 1), running(true), score(0)
{
    player.setHealth(10);  // Set initial health (add this setter in Player class)
    map.generateDefaultMap();

    enemies.emplace_back(10, 10);
    enemies.emplace_back(20, 15);
    enemies.emplace_back(30, 18);
}

void Game::draw() {
    const int consoleWidth = 80;
    int mapWidth = map.getWidth();

    // Helper to create centered padding for any text
    auto centerText = [&](const std::string& text) {
        int padding = (consoleWidth - static_cast<int>(text.size())) / 2;
        if (padding < 0) padding = 0;
        return std::string(padding, ' ') + text;
    };

    // Game title centered
    std::cout << centerText("=== DUNGEON ADVENTURE ===") << "\n\n";

    // Centered instructions and status
    std::cout << centerText("Use WASD / Arrows to move, F to attack, Q to quit.") << "\n";
    std::cout << centerText("Health: " + std::to_string(player.getHealth()) + "    Score: " + std::to_string(score)) << "\n";
    std::cout << centerText("Reach enemies (E) and attack them!") << "\n\n";

    // Map drawing with padding on left to center horizontally
    int padding = (consoleWidth - mapWidth) / 2;
    std::string pad(padding, ' ');

    for (int y = 0; y < map.getHeight(); ++y) {
        std::cout << pad;
        for (int x = 0; x < map.getWidth(); ++x) {
            if (player.getX() == x && player.getY() == y) {
                std::cout << player.getSymbol();
            } else {
                bool enemyHere = false;
                for (const auto& e : enemies) {
                    if (e.getX() == x && e.getY() == y) {
                        std::cout << e.getSymbol();
                        enemyHere = true;
                        break;
                    }
                }
                if (!enemyHere) {
                    std::cout << (map.isWalkable(x, y) ? '.' : '#');
                }
            }
        }
        std::cout << "\n";
    }
}


bool Game::isPositionFree(int x, int y) const {
    if (player.getX() == x && player.getY() == y) return false;
    for (const auto& e : enemies) {
        if (e.getX() == x && e.getY() == y)
            return false;
    }
    return true;
}

void Game::movePlayer(int dx, int dy) {
    int newX = player.getX() + dx;
    int newY = player.getY() + dy;

    if (map.isWalkable(newX, newY) && isPositionFree(newX, newY)) {
        player.setPosition(newX, newY);
    } else {
        std::cout << "Can't move there!\nPress Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    }
}

void Game::attack() {
    int px = player.getX();
    int py = player.getY();

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue; // skip player pos

            int tx = px + dx;
            int ty = py + dy;

            for (auto it = enemies.begin(); it != enemies.end(); ++it) {
                if (it->getX() == tx && it->getY() == ty) {
                    enemies.erase(it);
                    score += 10;
                    std::cout << "Enemy defeated! Score: " << score << "\n";
                    std::cout << "Press Enter to continue...";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();
                    return;
                }
            }
        }
    }
    std::cout << "No enemy adjacent to attack!\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void Game::enemyTurn() {
    for (auto& enemy : enemies) {
        // Calculate direction towards player
        int dx = player.getX() - enemy.getX();
        int dy = player.getY() - enemy.getY();

        int stepX = (dx != 0) ? (dx / std::abs(dx)) : 0;
        int stepY = (dy != 0) ? (dy / std::abs(dy)) : 0;

        int newX = enemy.getX() + stepX;
        int newY = enemy.getY() + stepY;

        // Move enemy if possible (not onto player or other enemy)
        if (map.isWalkable(newX, newY) && isPositionFree(newX, newY) && !(newX == player.getX() && newY == player.getY())) {
            enemy.setPosition(newX, newY);
        }

        // Check if enemy is adjacent to player to attack
        if (std::abs(enemy.getX() - player.getX()) <= 1 && std::abs(enemy.getY() - player.getY()) <= 1) {
            player.takeDamage(1);
            std::cout << "Enemy attacks you! Health: " << player.getHealth() << "\n";
            if (player.getHealth() <= 0) {
                running = false;
                std::cout << "You died! Game Over.\n";
                std::cout << "Press Enter to exit...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
            } else {
                std::cout << "Press Enter to continue...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
            }
        }
    }
}

void Game::handleInput() {
    char input = getInput();

    if (input == '\x1b') {  // Escape sequence for arrow keys
        char seq[2];
        if (read(STDIN_FILENO, &seq[0], 1) == 0) return;
        if (read(STDIN_FILENO, &seq[1], 1) == 0) return;

        if (seq[0] == '[') {
            switch (seq[1]) {
                case 'A': movePlayer(0, -1); break; // Up arrow
                case 'B': movePlayer(0, 1); break;  // Down arrow
                case 'C': movePlayer(1, 0); break;  // Right arrow
                case 'D': movePlayer(-1, 0); break; // Left arrow
            }
        }
    } else {
        char c = std::tolower(static_cast<unsigned char>(input));
        switch (c) {
            case 'w': movePlayer(0, -1); break;
            case 'a': movePlayer(-1, 0); break;
            case 's': movePlayer(0, 1); break;
            case 'd': movePlayer(1, 0); break;
            case 'f': attack(); break;  // Attack
            case 'q': running = false; break;
            default:
                // Ignore other input
                break;
        }
    }
}

void Game::gameLoop() {
    while (running) {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        draw();

        std::cout << "\n> ";
        handleInput();

        // After player's turn, enemies move and attack
        if (running) {
            enemyTurn();
        }

        // Check win condition: all enemies defeated
        if (enemies.empty()) {
            std::cout << "Congratulations! You defeated all enemies!\n";
            std::cout << "Final Score: " << score << "\n";
            std::cout << "Press Enter to exit...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            running = false;
        }
    }
}
