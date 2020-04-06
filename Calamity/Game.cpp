#include "Game.h"
#include <libtcod.hpp>

Game::Game()
{
    TCODConsole::initRoot(80, 50, "Libtcod Test", false, TCOD_RENDERER_SDL2);
    TCODSystem::setFps(30);
    TCODMouse::showCursor(true);

    region = Region();
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

    // Render all terrain for the region
    for (int x = 0; x < region.MAX_X; x++)
        for (int y = 0; y < region.MAX_Y; y++) {
            TCODConsole::root->putChar(x, y, region.ter(x, y)->ch);
        }

    TCODConsole::root->putChar(40, 25, '@');

    TCODConsole::root->flush();
}


