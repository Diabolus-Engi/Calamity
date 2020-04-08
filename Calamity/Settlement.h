#pragma once
#include "Utility.h"
#include <string>

class Settlement {
public:
	Settlement(Point2D pos);

	Point2D pos;

	// Settlement Stat Block
	std::string name;
	int population;
	int danger;


private:


public:


};