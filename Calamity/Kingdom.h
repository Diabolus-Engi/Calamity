#pragma once
#include <string>
#include "Alignment.h"

class Character;


class Kingdom {
public:
	std::string name;
	Alignment alignment;
	
	// Positions
	Character * ruler;

	// Color and visual details

	const char * col_s;


	Kingdom(std::string n, Alignment a, const char *c);

private:


};