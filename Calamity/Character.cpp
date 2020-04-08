#include "Character.h"

Character::Character() : Entity({0,0},'?')
{
	
}

Character::Character(std::string n, Alignment a, Point2D pos) : Entity(pos, '@')
{
	name = n;
	alignment = a;


}
