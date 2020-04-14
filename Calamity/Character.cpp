#include "Character.h"

Character::Character() : Entity({0,0},'?', nullptr)
{
	
}

Character::Character(std::string n, Alignment a, Point2D pos, Kingdom *owner) : Entity(pos, '@', owner)
{
	name = n;
	alignment = a;


}
