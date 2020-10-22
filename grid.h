#pragma once
#include "structs.h"
#include <vector>
class player;
#include "player.h"

class grid
{
public:
	grid();
	~grid();
	std::vector<player*> *players;

	Coordinate FirstAvailableCoordinate();
	bool CanMove(Coordinate pos);
	bool IsEmpty(Coordinate pos);

private:
};
