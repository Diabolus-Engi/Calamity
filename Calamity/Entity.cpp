#include "Entity.h"

unsigned int EntityID::cur_id = 0;
Entity::Entity(Point2D p, char c, Kingdom *o)
{
	pos = p;
	ch = c;
	owner = o;
}

Entity::~Entity()
{
}
