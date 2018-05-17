#include "Useful.h"

float Common::Getlength(Vec2 lhs, Vec2 rhs)
{
	return sqrt(pow(lhs.x - rhs.x, 2) + pow(lhs.y - rhs.y, 2));
}
