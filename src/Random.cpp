#include <iostream>
#include <cstdlib>
#include "Random.h"
#include "Player.h"




Random::Random(ComputerPlayer* aPlayer) : Strategy(aPlayer)
{}

Random:: ~Random()
{}

Random::Random()
{}

Ship& Random::selectShipToFire()
{
	shipsCapable.erase(shipsCapable.begin(), shipsCapable.end());
	Ship* to_check = NULL;

	for (int i = 0; i < 3; i++)
	{
		to_check = &(aPlayer->getShip(i));
		if (to_check->canTakeShot())
		{
			shipsCapable.push_back(to_check);
		}
	}
	int size = shipsCapable.size();

	int random_number = rand() % size;
	return *(shipsCapable.at(random_number));
}