#include "Region.h"

Region::Region()
{
	terrain.reserve(MAX_XY);
	// Fill terrain with grasslands.
	for (int x = 0; x < MAX_X; x++)
		for (int y = 0; y < MAX_Y; y++) {
			terrain.push_back(&grassland);
		}
}

Region::~Region()
{
	// TODO: Delete pointers for entities etc
	for (Entity * e : entities) {
		delete e;
	}

	for (Kingdom* k : kingdoms) {
		delete k;
	}
}

const Ter * Region::ter(int x, int y)
{
	return terrain.at(x + y * MAX_X);
}