#include <iostream>

#include "Game.h"

int main() {
    setlocale(LC_ALL, "Russian");
    srand( time(nullptr) );

    Game game = initGame('x');
    updateDisplay(game);
    do {
        if (game.isUserTurn) userTurn(&game);
        else botTurn(&game);

        updateDisplay(game);
    } while(!updateGame(&game));
}