#include <iostream>
#include "Greedy.h"
#include "ComputerPlayer.h"

Greedy::Greedy(ComputerPlayer* aPlayer) : Strategy(aPlayer)
{}

Greedy::Greedy()
{}

Greedy:: ~Greedy()
{}

Ship& Greedy::selectShipToFire()
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

	return *shipsCapable[size-1];
}