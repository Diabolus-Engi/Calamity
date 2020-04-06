#include "Game.h"
#include <libtcod.hpp>

Game::Game()
{
    TCODConsole::initRoot(80, 50, "Libtcod Test", false, TCOD_RENDERER_SDL2);
    TCODSystem::setFps(30);
    TCODMouse::showCursor(true);
}

void Game::Update()
{
	TCOD_key_t key;
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
    switch (key.vk) {
    case TCODK_UP:
       
        break;
    case TCODK_DOWN:

        break;
    case TCODK_LEFT:

        break;
    case TCODK_RIGHT:

        break;
    default:break;

    }
}

void Game::Render()
{
    TCODConsole::root->clear();

    TCODConsole::root->putChar(40, 25, '@');

    TCODConsole::root->flush();
}


