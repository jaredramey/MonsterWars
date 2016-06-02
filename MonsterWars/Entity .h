#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#include "MWMath.h"
#pragma once



class Entity
{
public:
	unsigned short UniqueID;
	unsigned short EntityTypeID;
	float CollisionRadius = 0;
	float FOV;
	Vec2 Pos;
	Vec2 Fwd;
};