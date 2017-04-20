#include <iostream>
#include <exception>
#include <fstream>
#include "Grid.h"

using namespace std;

Grid::Grid()
{
	for (int i = 0; i < HEIGHT; i++)
	{
		vector<Square> row;

		for (int j = 0; j < WIDTH; j++)
		{
			row.push_back(Square());
		}
		squares.push_back(row);
	}
}

Grid::~Grid()
{}

void Grid::markShip(pair<int, int>segment)
{
	squares[segment.first][segment.second].setState(SHIP);
}

bool Grid::wasAHit(pair<int, int>target)
{
	if (squares[target.first][target.second].getState() == SHIP)
		return true;
	else
		return false;
}

bool Grid::wasAMiss(pair<int, int> target)
{
	if (squares[target.first][target.second].getState() != SHIP)
		return true;
	else
		return false;
}

bool Grid::wasAlreadyATarget(pair<int, int> target)
{
	if (squares[target.first][target.second].getState() == HIT || squares[target.first][target.second].getState() == MISS)
	{
		throw invalid_argument("You cannot shoot twice to the same place");
		return true;
	}
	else
		return false;
}


void Grid::markTarget(pair<int, int> target)
{
	if (wasAHit(target))
		squares[target.first][target.second].setState(HIT);
	else if (wasAMiss(target))
		squares[target.first][target.second].setState(MISS);
}


void Grid::markAttackingGrid(pair<int, int> target, bool wasSuccessful)
{
	if (wasSuccessful)
		squares[target.first][target.second].setState(HIT);
	else
		squares[target.first][target.second].setState(MISS);
}

int Grid::valueAt(int i, int j)
{
	return squares[i][j].getState();
}

vector<vector<Square>> Grid::getVector()
{
	return squares;
}

void Grid::saveGrid(const string& filename)
{
	ofstream myfile;
	myfile.open(filename.c_str(), ios::app);

	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			myfile << valueAt(i, j);
		}
		myfile << endl;
	}
	myfile << endl;
	myfile.close();
}

Square& Grid::squareAt(int i, int j)
{
	return squares[i][j];
}

void Grid::writeToGrid(vector<vector<int>> v1)
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			squareAt(i, j).setState(v1[i][j]);
		}
		cout << endl;
	}
}
