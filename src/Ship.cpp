#include <iostream>
#include "Ship.h"
#include "functions.h"

Ship::Ship(vector<pair<int, int>>coordinates, bool human, Grid* secondaryGrid)
{
	this->human = human;
	attackGD = secondaryGrid;
	length = coordinates.size();
	range = length + 1;
	sunk = 0;
	is_reloaded = 0;
	roundCounter2 = 0;
	roundCounter3 = 0;
	if (length == 1)
		shots = 1;
	else
		shots = 2;

	for (auto it = coordinates.begin(); it != coordinates.end(); ++it)
	{
		Segment temp((*it).first, (*it).second);
		segments.push_back(temp);
	}
}

Ship::Ship()
{}

Ship::~Ship()
{}

bool Ship::isSunk()
{
	bool isSunk = 1;
	for (auto it = segments.begin(); it != segments.end(); ++it)
		if ((*it).wasHit() != true)
			isSunk = false;
	return isSunk; 
}

bool Ship::isInRange(pair<int, int>target)
{
	bool inRange = 0;
	int counter = 0;
	for (auto it = segments.begin(); it != segments.end(); ++it)
	{
		if (chessboard_distance(target, (*it).getCoords()) <= getRange())
			inRange = true;
		else
		{
			counter++;
			if (counter == segments.size())
				throw invalid_argument("Specified target is out of range");
		}
	}
	return inRange;
}

int Ship::getSize()
{
	return segments.size();
}

int Ship::getRange()
{
	return range;
}

vector<pair<int, int>> Ship::possibleTargets()
{
	vector<pair<int, int>> possibleTargets;
	pair<int, int> end1 = segments[0].getCoords();
	pair <int, int> end2 = segments[length - 1].getCoords();
	
	for (int x = end1.first - range; x <= end2.first + range; x++)
	{
		for (int y = end1.second - range; y <= end2.second + range; y++)
		{
			if (x >= 0 && y >= 0 && x < 10 && y < 10)
			{
				if (attackGD->valueAt(x, y) == 0)
					possibleTargets.push_back(make_pair(x, y));
			}
		}
	}
	return possibleTargets;
}

void Ship::set_is_reloaded(bool value)
{
	is_reloaded = value;
}
bool Ship::isReloaded()
{
	return is_reloaded;
}

int Ship::intactSegments()
{
	int intact = 0;

	for (int i = 0; i < getSize(); i++)
	{
		if (!segments[i].wasHit())
			intact++;
	}
	return intact;
}

bool Ship::belongsToHuman()
{
	return human;
}


void Ship::add_roundCounter2(int value)
{
	if (value == 0)
	{
		set_is_reloaded(false);
		roundCounter2 = 0;
	}
	else
		roundCounter2 += value;
}
void Ship::add_roundCounter3(int value)
{
	if (value == 0)
	{
		set_is_reloaded(false);
		roundCounter3 = 0;
	}
	else
		roundCounter3 += value;
}

int Ship::get_roundCounter2()
{
	return roundCounter2;
}

int Ship::get_roundCounter3()
{
	return roundCounter3;
}

vector<pair<int, int>> Ship::getLocation()
{
	vector<pair<int, int>> coords;

	for (int i = 0; i < segments.size(); i++)
	{
		coords.push_back(segments[i].getCoords());
	}
	return coords;
}