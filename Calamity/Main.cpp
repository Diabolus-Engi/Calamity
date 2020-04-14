#include "BearLibTerminal.h"
#include "Game.h"
#include <iostream>

int main() {
    // Init terminal
    int t_open = terminal_open();

    // Config
    std::string cfg_str;
    cfg_str = "window.title='Calamity';";
    cfg_str.append("window.size="+std::to_string(Game::SCREEN_WIDTH)+"x"+ std::to_string(Game::SCREEN_HEIGHT)+";");
    cfg_str.append("window.cellsize=16x16;");
    cfg_str.append("window.resizeable=true;");
    cfg_str.append("input.alt-functions=true;");
    cfg_str.append("input.precise-mouse=true;");
    cfg_str.append("input.filter=[keyboard, mouse+];");
    cfg_str.append("log.file='calamity_log';");

    terminal_set(cfg_str.c_str());
    terminal_refresh();

    Game game = Game();

    while (game.game_state != GAME_STATE::CLOSING && t_open != 0) {
        if (game.Update())
            game.Render();
    }
    terminal_close();
    return 0;
}