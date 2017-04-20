#include <iostream>
#include "ComputerPlayer.h"
#include "Ship.h"
#include "Greedy.h"
#include "Random.h"
#include "functions.h"

using namespace std;

ComputerPlayer::ComputerPlayer(const string& sstrategy)
{
	is_Human = false;
	if (sstrategy == "random")
		this->aStrategy = new Random(this);

	if (sstrategy == "greedy")
		this->aStrategy = new Greedy(this);
}

ComputerPlayer::ComputerPlayer()
{

}

ComputerPlayer::~ComputerPlayer()
{
	delete aStrategy;
}

void ComputerPlayer::createShips(int number)
{
	vector <pair<int, int>> coordinates = vector_of_pairs(number);

	bool coords_ok = false;

	while (!coords_ok)
	{
			try
		{
			coords_ok = checkCoordinates(coordinates);
		}

		catch (Player::Exception &)
		{
			coordinates.clear();
			coordinates = vector_of_pairs(number);
		}
	}
	Ship* newShip = NULL;

	if (number == 1)
		newShip = new SingleFunnel(coordinates, false, secondaryGrid);
	else
		newShip = new MultipleFunnel(coordinates, false, secondaryGrid);

	ships.push_back(newShip);
	markOwnShips(coordinates);
}



void ComputerPlayer::setShipToFire()
{
	selected = &(aStrategy->selectShipToFire());
}

pair<int, int> ComputerPlayer::setTarget()
{
	pair<int, int> target;
	vector<pair<int, int>> possible = getSelected().possibleTargets();
	int random = random_number(possible.size(), 0);
	target = possible[random];

	return target;
}


bool ComputerPlayer::decide()
{
	return true;
}