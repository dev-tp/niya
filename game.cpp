#include <ctime>
#include <iostream>
#include <sstream>

#include "game.h"
#include "tile.h"

void Game::printBoard() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            cout << board[i][j] + ' ';
        cout << endl;
    }
}

void Game::init() {
    vector<string> permutations;
    unsigned int seconds = time(NULL);
    for (int i = 0; i < 4; i++) {
        int j = 0;
        while (j < 4) {
            srand(++seconds);
            Tile tile;
            char l = tile.getTypeOne(), k = tile.getTypeTwo();
            if (l != k && pairDoesNotExist(&permutations, l, k))
                board[i][j++] = tile.toString();
        }
    }
    printBoard();
}

bool Game::checkForWinner() {
    if (board[0][0] == board[1][1] && board[2][2] == board[3][3]) {
        return true;
    } else if (board[0][3] == board[1][2] && board[2][1] == board[3][0]) {
        return true;
    } else if (board[1][1] == board[1][2] && board[2][1] == board[2][2]) {
        return true;
    } else {
        // Checks rows and columns
        for (int i = 0; i < 4; i++) {
            if (board[i][0] == board[i][1] && board[i][2] == board[i][3])
                return true;
            if (board[0][i] == board[1][i] && board[2][i] == board[3][i])
                return true;
        }

        // Check for squares
        for (int i = 0; i < 4; i += 2)
            for (int j = 0; j < 4; j += 2)
                if (board[i][j] == board[i][j+1] && board[i+1][j] == board[i+1][j+1])
                    return true;

        for (int i = 0; i < 4; i += 2) {
            if (board[i][1] == board[i][2] && board[i+1][1] == board[i+1][2])
                return true;
            if (board[1][i] == board[1][i+1] && board[2][i] == board[2][i+1])
                return true;
        }
    }
    return false;
}

bool Game::pairDoesNotExist(vector<string> *pairs, char a, char b) {
    string pairOne, pairTwo;
    pairOne += a; pairOne += ' '; pairOne += b;
    pairTwo += b; pairTwo += ' '; pairTwo += a;

    if (contains(pairs, pairOne) || contains(pairs, pairTwo))
        return false;

    pairs->push_back(pairOne);
    return true;
}

bool Game::contains(vector<string> *pairs, string pair) {
    for (string temp : *pairs)
        if (temp == pair)
            return true;
    return false;
}

vector<string> Game::split(string str, char delimiter) {
    vector<string> result;
    stringstream ss(str);
    string token;

    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

bool Game::isValidMove(int x, int y, string lastTile) {
    string tile = board[x][y];
    vector<string> a = split(tile, '/'), b = split(lastTile, '/');
    for (string str : a)
        if (str == b[0] || str == b[1])
            return true;
    return false;
}

string Game::makeMove(Player player, string lastTile) {
    int x, y;
    while (true) {
        cout << "Your turn: " << player.name << endl;
        cout << "x: ";
        cin >> x;
        cout << "y: ";
        cin >> y;
        if (!lastTile.empty()) {
            if (isValidMove(x, y, lastTile)) {
                lastTile = board[x][y];
                board[x][y] = player.color;
                cout << "\nLast tile: " << lastTile << endl;
                printBoard();
                return lastTile;
            } else {
                cout << "\n" << x << " and " << y << " are not valid: " <<
                "The tile you choose should contain one symbol of the previous tile." << endl;
            }
        } else {
            lastTile = board[x][y];
            board[x][y] = player.color;
            cout << "\nLast tile: " << lastTile << endl;
            printBoard();
            return lastTile;
        }
    }
}