#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
#pragma once

#define Deg2Rad 0.0174533

struct Vec2 { float x, y; };

float dot(const Vec2 &a, const Vec2 &b){return a.x * b.x + a.y * b.y;}
Vec2 operator-(const Vec2 &a, const Vec2 &b){return{ a.x - b.x, a.y - b.y };}
Vec2 operator/(const Vec2 &a, float b){return{a.x/b, a.y/b};}
float mag(const Vec2 &a){return sqrtf(dot(a, a));}
Vec2 normal(const Vec2 &a){return a / mag(a);}

bool CanSee(const Vec2 &eye, const Vec2 &fwd, const Vec2 &target, float FOVdeg)
{
	return dot(normal(target - eye), fwd) >= cosf(FOVdeg*Deg2Rad/2);
}

bool IsOverlapping(const Vec2 &pos1, float CollRadi1, const Vec2 &pos2, float collRadi2)
{
	return mag(pos1 - pos2) <= CollRadi1 + collRadi2;
}