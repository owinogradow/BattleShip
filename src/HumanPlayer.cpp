#include <iostream>
#include "HumanPlayer.h"
#include "Ship.h"
#include "functions.h"

using namespace std;

HumanPlayer::HumanPlayer()
{
	is_Human = true;
	humanUI = new HumanUI;
}

HumanPlayer::~HumanPlayer()
{
	delete humanUI;
}

void HumanPlayer::createShips(int number)
{
	vector< pair <int, int> > coordinates;
	bool coords_ok = false;
	do 
	{
		try
		{
			coordinates = humanUI->askShipsPosition(number);
			coords_ok = checkCoordinates(coordinates);
		}
		catch (Player::IncorrectException &)
		{
			cout << "There was previously placed ship. Ships cannot overlap or touch each other." << endl;
		}
		catch (Player::BendException &)
		{
			cout << "The ship cannot be bend." << endl;
		}
		catch (Player::NegativeException &)
		{
			cout << "You cannot insert negative values for ship positions." << endl;
		}
		catch (Player::AdjacencyExeption &)
		{
			cout << "The segments are not adjacent." << endl;
		}
		catch (invalid_argument& e)
		{
			cerr << e.what() << endl;
		}
	} while (!coords_ok);

	Ship* newShip = NULL;
	if (number == 1)
		newShip = new SingleFunnel(coordinates, true, secondaryGrid);
	else
		newShip = new MultipleFunnel(coordinates, true, secondaryGrid);

	ships.push_back(newShip);
	markOwnShips(coordinates);
}

void HumanPlayer::setShipToFire()
{
	bool ship_ok = false;
	int shipToFire = 0;
	Ship* temp;
	do
	{
		try
		{
			shipToFire = humanUI->askShipToFire() - 1;
			temp = &(getShip(shipToFire));
			roundCounting(temp);
			ship_ok = temp->canTakeShot();
		}
		catch (Ship::ShipHaveToWaitException &)
		{
			cout << " You shot previously twice with multifunnel, so this ship have to wait 1 round. " << endl;
		}
		catch (invalid_argument& e)
		{
			cerr << e.what() << endl;
		}
	} while (!ship_ok);
	selected = ships[shipToFire];
}


pair<int, int> HumanPlayer::setTarget()
{
	pair <int, int> target;
	bool coords_ok = false;
	do
	{
		try
		{
		target = humanUI->askTarget();
			coords_ok = isShotPossible(target);
		}
		//this catch-block below catches wrong target input, and out of range shot, and the same target second time specifying
		catch (const invalid_argument& e) 
		{
			cerr << e.what() << endl;
		}
	} while (!coords_ok);
	return target;
}

bool HumanPlayer::decide()
{
	bool oneMoreShot = humanUI->askDecision();
	return oneMoreShot;
}

void HumanPlayer::roundCounting(Ship* temp)
{
	if (temp->getSize() == 3)
	{
		if (temp->get_roundCounter3() >= 1) temp->add_roundCounter3(0);
		else if (temp->isReloaded()) throw Ship::ShipHaveToWaitException();
		else if (ships[1]->isReloaded()) ships[1]->add_roundCounter2(1);
	}
	else if (temp->getSize() == 2)
	{
		if (temp->get_roundCounter2() >= 1) temp->add_roundCounter2(0);
		else if (temp->isReloaded()) throw Ship::ShipHaveToWaitException();
		else if (ships[2]->isReloaded()) ships[2]->add_roundCounter3(1);
	}
	if (ships[1]->isReloaded()) ships[1]->add_roundCounter2(1);
	if (ships[2]->isReloaded()) ships[2]->add_roundCounter3(1);

}