#include <cstdlib>
#include <iostream>

#include "game.h"

int main() {
    Game game;

    Player players[] = { Player("P1", "RED"), Player("P2", "BLK") };

    game.initBoard();
    string lastTile = game.makeMove(players[0], "");
    lastTile = game.makeMove(players[1], lastTile);

    for(int i = 0; i < 7; i++) {
        for(Player player: players) {
            lastTile = game.makeMove(player, lastTile);
            if(game.checkForWinner()) {
                cout << player.name << ": You win!" << endl;
                exit(0);
            }
        }
    }

    cout << "The match ends in tie!" << endl;

    return 0;
}