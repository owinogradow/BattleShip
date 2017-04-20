#include <iostream>
#include "SingleFunnel.h"

SingleFunnel::SingleFunnel(vector<pair<int, int>>coordinates, bool human, Grid* secondary) : Ship(coordinates, human, secondary)
{}

SingleFunnel::SingleFunnel()
{}

bool SingleFunnel::canTakeShot()
{
	vector<pair<int, int>>possible = possibleTargets();

	if (!isSunk() && possible.size() > 0)
		return true;
	else
		return false;
}

void SingleFunnel::fire()
{}