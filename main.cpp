#include <cstdlib>
#include <iostream>
#include "Game.h"

int main() {
    Game game;
    Player playerOne("P1", "RED");
    Player playerTwo("P2", "BLK");

    game.initBoard();
    string lastTile = game.makeMove(playerOne, "");
    lastTile = game.makeMove(playerTwo, lastTile);

    for(int i = 0; i < 7; i++) {
        lastTile = game.makeMove(playerOne, lastTile);
        if(game.checkForWinner()) {
            cout << playerOne.name << ": You win!" << endl;
            exit(0);
        }

        lastTile = game.makeMove(playerTwo, lastTile);
        if(game.checkForWinner()) {
            cout << playerTwo.name << ": You win!" << endl;
            exit(0);
        }
    }

    cout << "The match ends in tie!" << endl;
    return 0;
}