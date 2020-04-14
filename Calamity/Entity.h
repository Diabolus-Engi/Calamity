#pragma once
#include "Utility.h"
#include "Kingdom.h"

class Kingdom;

struct EntityID {
	int guid;
	static unsigned int cur_id;
	EntityID() { guid = cur_id++; };
}; 

class Entity {
public:
	Point2D pos;
	EntityID id;
	char ch;
	Kingdom *owner;
	Entity(Point2D p, char c, Kingdom *owner);
	virtual ~Entity();


};


