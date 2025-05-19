#ifndef CHARACTER_H
#define CHARACTER_H

class Character {
public:
    Character(int x, int y, char symbol);

    int getX() const;
    int getY() const;
    char getSymbol() const;

    void setPosition(int x, int y);

private:
    int x, y;
    char symbol;
};

#endif // CHARACTER_H
