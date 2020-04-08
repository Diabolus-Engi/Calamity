#include "Entity.h"

unsigned int EntityID::cur_id = 0;
Entity::Entity(Point2D p, char c)
{
	pos = p;
	ch = c;
}

Entity::~Entity()
{
}
