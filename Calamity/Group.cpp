#include "Group.h"

Group::Group(std::string n, Alignment a, int s, Kingdom *owner) : Entity({ 0,0 }, '?', owner)
{
	name = n;
	alignment = a;
	size = s;
}
