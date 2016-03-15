#include <vector>
#include <string>

#include "Player.h"

using namespace std;

class GameBoard {
    string board[4][4];
    static bool contains(vector<string>*, string);
    bool isValidMove(int, int, string);
    static bool pairDoesNotExist(vector<string>*, char, char);
    void printBoard();
public:
    bool checkForWinner();
    string makeMove(Player, string);
    void initBoard();
};