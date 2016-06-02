#include <iostream>
#pragma once

class Entity
{
public:
	unsigned short UniqueID;
	unsigned short EntityTypeID;
	float PosX;
	float PosY;
	float Forward_NormalX;
	float Forward_NormalY;
	char padding[12];

	void CanSee(const Entity &e)
	{

	}

	void IsOverlapping(const Entity &e)
	{

	}
};