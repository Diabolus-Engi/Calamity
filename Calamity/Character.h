#pragma once

#include <string>
#include "Entity.h"
#include "Alignment.h"

class Character : public Entity {
public:
	std::string name;
	Alignment alignment;

	// Attributes
	int strength;
	int constitution;
	int wisdom;
	int dexterity;
	int intelligence;
	int charisma;

	Character();
	Character(std::string n, Alignment a, Point2D pos = { 0,0 });

};
	