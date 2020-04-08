#pragma once
#include <string>
#include "Alignment.h"
#include "Character.h"


class Kingdom {
public:
	std::string name;
	Alignment alignment;
	
	// Positions
	Character * ruler;

	// Stats
	int build_points = 50; //Build points
	int consumption;
	int economy;
	int loyalty;
	int size;
	int stability;
	int treasury;
	int unrest;	

	Kingdom(std::string n, Alignment a);

private:


};