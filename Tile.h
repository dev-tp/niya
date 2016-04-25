#include <cstdlib>

class Tile {
    char typeOne, typeTwo;
    static string icons;
public:
    Tile() {
        this->typeOne = Tile::icons[rand() % 8];
        this->typeTwo = Tile::icons[rand() % 8];
    }

    char getTypeOne() { return this->typeOne; }
    char getTypeTwo() { return this->typeTwo; }

    /* friend ostream& operator<<(ostream& strm, const Tile& tile) {
        strm << tile.typeOne << '/' << tile.typeTwo;
        return strm;
    } */

    std::string toString() {
        std::string tile;
        tile += this->typeOne;
        tile += '/';
        tile += this->typeTwo;
        return tile;
    }

};

string Tile::icons = "ABCDEFGH";
