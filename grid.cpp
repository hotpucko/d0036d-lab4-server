#include "grid.h"

grid::grid()
{
}

grid::~grid()
{
}

Coordinate grid::FirstAvailableCoordinate()
{
	Coordinate pos;
	pos.x = -100;
	pos.y = -100;

	while (!IsEmpty(pos))
	{
		pos.x++;
	}

	return pos;
}

bool grid::CanMove(Coordinate pos)
{
	if (IsEmpty(pos) && pos.x >= -100 && pos.x <= 100 && pos.y >= -100 && pos.y <= 100)
		return true;
}

bool grid::IsEmpty(Coordinate pos)
{
	for (int i = 0; i < players->size(); i++)
		if (pos.x == players->at(i)->client->pos.x && pos.y == players->at(i)->client->pos.y)
			return false;
	return true;
}
