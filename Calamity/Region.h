#pragma once
#include <libtcod.hpp>

// Terrain
class Ter {
public:
	Ter(int ch, TCODColor col = TCODColor::yellow) {
		this->ch = ch;
		this->col = col;
	}

	int ch;
	TCODColor col;
};

// Building
class Build {
	int ch;
	TCODColor col;
};

// Tile
class Tile {
	Ter terrain;
	Build building;
};

class Region {
public:
	const static int MAX_X = 256;
	const static int MAX_Y = 256;
	const static int MAX_XY = MAX_X * MAX_Y;

	Region();

	// Get terrain at position
	const Ter * ter(int x, int y);

private:
	std::vector<const Ter *> terrain;

};

const Ter grassland = Ter('.',TCODColor::desaturatedGreen);


