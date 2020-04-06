#pragma once
#include "Region.h"

class Game {
public:
	void Update();

	void Render();
	
	// Constructors
	Game();


private:
	Region region;

};