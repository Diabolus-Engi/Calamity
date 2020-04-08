#pragma once
#include "Utility.h"

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
	Entity(Point2D p, char c);
	virtual ~Entity();
};


