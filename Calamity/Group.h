#pragma once
#include "Alignment.h"
#include <string>
#include "Entity.h"

class Group : public Entity {
public:

	Group(std::string n, Alignment a, int s, Kingdom *owner);

	// Stat block for group

	std::string name;
	Alignment alignment;
	int exp; //Exp awarded
	int size; //Total units
	int type; //TODO: Change this to a class and apply CR into it.
	int speed;
	int morale;
	Character* commander;

};