#pragma once
#include "BearLibTerminal.h"
#include "Entity.h"
#include "Settlement.h"
#include <vector>
#include "Kingdom.h"


// Terrain
class Ter {
public:
	Ter(char ch, color_t col = color_from_name("yellow")) {
		this->ch = ch;
		this->col = col;
	}

	char ch;
	color_t col;
};


// Tile
class Tile {
	Ter terrain;
};

class Region {
public:
	const static int MAX_X = 256;
	const static int MAX_Y = 256;
	const static int MAX_XY = MAX_X * MAX_Y;

	Region();
	~Region();

	// Get terrain at position
	const Ter * ter(int x, int y);
public:
	std::vector<const Ter *> terrain;
	std::vector<Tile*> tiles;
	std::vector<Entity*> entities;
	std::vector<Settlement> settlements;
	std::vector<Kingdom *> kingdoms;

};


const Ter grassland = Ter('.', color_from_name("red"));
const Ter forest = Ter('F', color_from_name("green"));


