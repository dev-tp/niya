#ifndef tile_h
#define tile_h

#include <cstdlib>

class Tile {
    char typeOne, typeTwo;
    static string icons;
public:
    Tile() {
        this->typeOne = Tile::icons[rand() % 8];
        this->typeTwo = Tile::icons[rand() % 8];
    }

    char getTypeOne() { return typeOne; }
    char getTypeTwo() { return typeTwo; }

    std::string toString() {
        std::string tile;
        tile += typeOne;
        tile += '/';
        tile += typeTwo;
        return tile;
    }

};

string Tile::icons = "ABCDEFGH";

#endif