#include "BearLibTerminal.h"
#include "Game.h"
#include <iostream>

int main() {
    Game game = Game();

    // Init terminal
    int t_open = terminal_open();

    // Config
    std::string cfg_str;
    cfg_str = "window.title='Calamity';";
    cfg_str.append("window.size=144x48;");
    cfg_str.append("window.resizeable=true;");
    cfg_str.append("input.alt-functions=true;");
    cfg_str.append("log.file='calamity_log';");

    terminal_set(cfg_str.c_str());

    terminal_refresh();
    while (game.game_state != GAME_STATE::CLOSING && t_open != 0) {
        game.Update();
        game.Render();
    }
    terminal_close();
    return 0;
}