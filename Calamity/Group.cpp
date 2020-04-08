#include "Group.h"

Group::Group(std::string n, Alignment a, int s) : Entity({ 0,0 }, '?')
{
	name = n;
	alignment = a;
	size = s;
}
