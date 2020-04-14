#pragma once
#include "BearLibTerminal.h"
#include "Entity.h"
#include "Settlement.h"
#include <vector>
#include "Kingdom.h"


// Terrain
class Ter {
public:
	Ter(const char ch, const char *col = "yellow", const char *bkcol = "black") {
		this->ch = ch;
		this->col = color_from_name(col);
		this->bkcol = color_from_name(bkcol);
		col_s = col;
		bkcol_s = bkcol;
	}

	char ch;
	color_t col;
	color_t bkcol;
	const char* bkcol_s;
	const char* col_s;
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


const Ter grassland = Ter(',', "green", "darker green");
const Ter forest = Ter('F', "green");


