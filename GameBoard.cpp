#include <iostream>
#include <sstream>
#include <time.h>

#include "GameBoard.h"
#include "Tile.h"

time_t seconds;

void GameBoard::printBoard() {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++)
            cout << this->board[i][j] + " ";
        cout << endl;
    }
}

void GameBoard::initBoard() {
    vector<string> permutations;
    seconds = time(NULL);
    for(int i = 0; i < 4; i++) {
        int j = 0;
        while(j < 4) {
            srand((unsigned int) ++seconds);
            Tile tile;
            char l = tile.getTypeOne(), k = tile.getTypeTwo();
            if(l != k && pairDoesNotExist(&permutations, l, k))
                this->board[i][j++] = tile.toString();
        }
    }
    this->printBoard();
}

bool GameBoard::checkForWinner() {
    if(board[0][0] == board[1][1] && board[2][2] == board[3][3]) {
        return true;
    } else if(board[0][3] == board[1][2] && board[2][1] == board[3][0]) {
        return true;
    } else if(board[1][1] == board[1][2] && board[2][1] == board[2][2]) {
        return true;
    } else {
        // Checks rows and columns
        for(int i = 0; i < 4; i++)
            if(board[i][0] == board[i][1] && board[i][2] == board[i][3])
                return true;
        for(int i = 0; i < 4; i++)
            if(board[0][i] == board[1][i] && board[2][i] == board[3][i])
                return true;

        // Checks for squares
        for(int i = 0; i < 4; i += 2)
            for(int j = 0; j < 4; j += 2)
                if(board[i][j] == board[i][j+1] && board[i+1][j] == board[i+1][j+1])
                    return true;
        for(int i = 0; i < 4; i += 2)
            if(board[i][1] == board[i][2] && board[i+1][1] == board[i+1][2])
                return true;
        for(int i = 0; i < 4; i += 2)
            if(board[1][i] == board[1][i+1] && board[2][i] == board[2][i+1])
                return true;
    }
    return false;
}

bool GameBoard::pairDoesNotExist(vector<string> *permutations, char a, char b) {
    string pairOne, pairTwo;
    pairOne += a; pairOne += ' '; pairOne += b;
    pairTwo += b; pairTwo += ' '; pairTwo += a;

    if(contains(permutations, pairOne) || contains(permutations, pairTwo))
        return false;

    permutations->push_back(pairOne);
    return true;
}

bool GameBoard::contains(vector<string> *container, string s) {
    for(string str: *container)
        if(str == s)
            return true;
    return false;
}

vector<string> split(string str, char delimiter) {
    vector<string> result;
    stringstream ss(str);
    string token;

    while(getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

bool GameBoard::isValidMove(int x, int y, string lastTile) {
    string tile = this->board[x][y];
    vector<string> a = split(tile, '/');
    vector<string> b = split(lastTile, '/');
    for(string str: a)
        if(str == b[0] || str == b[1])
            return true;
    return false;
}

string GameBoard::makeMove(Player player, string lastTile) {
    int x, y;
    while(true) {
        cout << "Your turn: " << player.name << endl;
        cout << "x: ";
        cin >> x;
        cout << "y: ";
        cin >> y;
        if(!lastTile.empty()) {
            if(isValidMove(x, y, lastTile)) {
                lastTile = this->board[x][y];
                this->board[x][y] = player.color;
                cout << "\nLast tile: " << lastTile << endl;
                this->printBoard();
                return lastTile;
            } else {
                cout << "\n" << x << " and " << y << " are not valid: " <<
                "The tile you choose should contain one symbol of the previous tile." << endl;
            }
        } else {
            lastTile = this->board[x][y];
            this->board[x][y] = player.color;
            cout << "\nLast tile: " << lastTile << endl;
            this->printBoard();
            return lastTile;
        }
    }
}