#include <iostream>
#include <fstream>
#include <sstream>
#include "Player.h"
#include "functions.h"

const int NEWLINE = 10;

Player::Player()
{
	primaryGrid = new Grid;
	secondaryGrid = new Grid;
}

Player::~Player()
{
	for (auto it = ships.begin(); it != ships.end(); ++it)
		delete *it;
	delete primaryGrid;
	delete secondaryGrid;
}


pair<int, int> Player::move()
{
	if (canDoAnything())
	{
		setShipToFire();
		pair<int, int> target;
		target = setTarget();
		selected->fire();
		return target;
	}
	else
	{
		pair<int, int> no_target = make_pair(-1, -1);
		return no_target;
	}
}


bool Player::checkCoordinates(vector <pair<int, int>> coordinates)
{
	bool noShipThere = 1;
	for (auto it = coordinates.begin(); it != coordinates.end(); ++it)
	{
		for (int p = - 1; p < 2; p++)
		{
			for (int q = - 1; q < 2; q++)
			{
				int x = (*it).first + p;
				int y = (*it).second + q;

				if (x > -1 && x < 10 && y > -1 && y < 10)
				{
					if (primaryGrid->valueAt(x, y) == 2)
					{
						noShipThere = false;
						throw IncorrectException();
					}
				}
			}
		}
	}

		bool nonNegative = 1;
		for (auto it = coordinates.begin(); it != coordinates.end(); ++it)
		{
			if ((*it).first < 0 && (*it).second < 0)
			{
				nonNegative = false;
				throw NegativeException();
			}
		}
		if (coordinates.size() < 2 && noShipThere && nonNegative)
			return true;

		bool isNotBend = 1;
		if (coordinates.size() == 3)
		{
			if (euclidean_distance(coordinates[0], coordinates[2]) != 2) 
			{
				isNotBend = false;
				throw BendException();
			}
		}

		bool isAdjacent = 1;
		for (int i = 0; i < coordinates.size() - 1; i++)
		{
			if (euclidean_distance(coordinates[i], coordinates[i + 1]) != 1)
			{
				isAdjacent = false;
				throw AdjacencyExeption();
			}
		}

		if (noShipThere && isAdjacent && isNotBend && nonNegative)
			return true;
		else
			return false;
}

void Player::markOwnShips(vector<pair<int, int>>coordinates)
{
	for (auto it = coordinates.begin(); it != coordinates.end(); ++it)
		primaryGrid->markShip(*it);
}



bool Player::canDoAnything()
{
	bool cantHaveShot = true;
	for (auto it = ships.begin(); it != ships.end(); ++it)
	{
		try
		{
			if ((*it)->canTakeShot())
				cantHaveShot = false;
		}
		catch (Ship::ShipHaveToWaitException &){}
	}

	bool newSquaresLeft = false;
	for (auto it = ships.begin(); it != ships.end(); ++it)
	{
		vector<pair<int, int>>possibleTargets = (*it)->possibleTargets();
		if (possibleTargets.size() > 0)
		{
			newSquaresLeft = true;
			break;
		}
	}

	if (!cantHaveShot && newSquaresLeft)
		return true;
	else
		return false;
}

bool Player::isShotPossible(pair<int, int>target)
{
	if (selected->isInRange(target) && !(secondaryGrid->wasAlreadyATarget(target)))
		return true;
	else
		return false;
}

Ship& Player::getShip(int a)
{
	return *(ships[a]);
}


bool Player::checkShot(pair<int,int> target)
{
	if (target.first != -1)
	{
		if (primaryGrid->wasAHit(target))
		{
			cout << "Was a Hit!" << endl;
			primaryGrid->markTarget(target);
			return true;
		}

		else if (primaryGrid->wasAMiss(target))
		{
			cout << "Was a Miss!" << endl;
			primaryGrid->markTarget(target);
			return false;
		}
	}
}

void Player::markShot(pair<int, int> target, bool wasSuccessful)
{
	secondaryGrid->markAttackingGrid(target, wasSuccessful);
}

Grid& Player::getGrid(int a)
{
	if (a == 1)
		return *primaryGrid;
	else if (a == 2)
		return *secondaryGrid;
}

Ship& Player::getSelected()
{
	return *selected;
}


int Player::countShips()
{
	int shipCount = 0;

	for (auto it = ships.begin(); it != ships.end(); ++it)
	{
		shipCount += (*it)->intactSegments();
	}
	return shipCount;
}


void Player::saveGrids(const string& name)
{
	ofstream myfile;
	myfile.open(name.c_str(), ofstream::trunc);
	myfile.close();

	getGrid(1).saveGrid(name.c_str());
	getGrid(2).saveGrid(name.c_str());
}


void Player::saveShips(const string& name)
{
	if (!fileExists(name.c_str()))
	{
		ofstream myfile;
		myfile.open(name.c_str());

		for (int i = 0; i < 3; i++)
		{
			vector<pair<int, int>> location = ships[i]->getLocation();
			for (auto it = location.begin(); it != location.end(); ++it)
			{
				myfile << (*it).first << " " << (*it).second << " ";
			}
			myfile << endl;
		}
		myfile.close();
	}
}


void Player::writeToGrids(const string& name)
{
	vector<int> read;

	ifstream infile;
	infile.open(name.c_str());
	char value;

	while (infile.get(value))
	{
		if (value != NEWLINE)
		{
			int a = (int)value - '0';
			read.push_back(a);
		}
	}

	infile.close();

	vector<int> primary1D(read.begin(), read.begin() + 100);
	vector<vector<int>> primary = D_to_2D(primary1D);

	vector<int> secondary1D(read.begin() + 100, read.end());
	vector<vector<int>> secondary = D_to_2D(secondary1D);
	
	primaryGrid->writeToGrid(primary);
	secondaryGrid->writeToGrid(secondary);
}


void Player::writeShips(const string& name)
{
	vector<pair<int, int>> coordinates;

	ifstream myfile;
	myfile.open(name.c_str());
	string str;

	while (getline(myfile, str))
	{
		istringstream ss(str);
		int a, b;
		while (ss >> a >> b)
		{
			coordinates.push_back(make_pair(a, b));
		}
	}
	myfile.close();

	vector<pair<int, int>> v1(coordinates.begin(), coordinates.begin() + 1);
	vector<pair<int, int>> v2(coordinates.begin() + 1, coordinates.begin() + 3);
	vector<pair<int, int>> v3(coordinates.begin() + 3, coordinates.begin() + 6);
	bool is_human = isHuman();

	Ship* newShip1 = new SingleFunnel(v1, is_human, secondaryGrid);
	Ship* newShip2 = new MultipleFunnel(v2, is_human, secondaryGrid);
	Ship* newShip3 = new MultipleFunnel(v3, is_human, secondaryGrid);

	ships.push_back(newShip1);
	ships.push_back(newShip2);
	ships.push_back(newShip3);
}

bool Player::isHuman()
{
	return is_Human;
}