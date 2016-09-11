#ifndef game_h
#define game_h

#include <string>
#include <vector>

#include "player.h"

using namespace std;

class Game {
    string board[4][4];
    static bool contains(vector<string>*, string);
    bool isValidMove(int, int, string);
    static bool pairDoesNotExist(vector<string>*, char, char);
    void printBoard();
    vector<string> split(string, char);
public:
    bool checkForWinner();
    string makeMove(Player, string);
    void init();
};

#endif