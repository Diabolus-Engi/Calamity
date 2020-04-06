#include <libtcod.hpp>
#include "Game.h"

int main() {
    Game game = Game();

    while (!TCODConsole::isWindowClosed()) {
        game.Update();
        game.Render();
    }
    return 0;
}