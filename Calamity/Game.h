#pragma once
#include "Region.h"

enum class GAME_STATE {
	RUNNING,
	CLOSING
};

class Game {
public:
	void Update();

	void Render();
	
	// Constructors
	Game();

	GAME_STATE game_state;

	// Mouse/Keyboard cursor
	char cursor = 'X';
	Point2D cursor_pos;

	// Player entity
	Entity * player;

private:
	Region region;

};