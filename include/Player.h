#ifndef PLAYER_H_
#define PLAYER_H_
#include <vector>
#include <utility> 
#include "Grid.h"
#include "SingleFunnel.h"
#include "MultipleFunnel.h"

using namespace std;

class Player
{
protected:
	bool is_Human;
	vector<Ship*> ships;
	Grid* primaryGrid;
	Grid* secondaryGrid;
	Ship* selected;

public:
	class Exception {};
	class IncorrectException : public Exception {};
	class NegativeException : public Exception {};
	class BendException : public Exception {};
	class AdjacencyExeption : public Exception {};
	class WrongInputException : public Exception{};

	Player();
	virtual ~Player();
	pair<int,int> move();
	bool checkShot(pair<int, int> target);
	void markShot(pair<int, int> target, bool wasSuccessful);
	virtual void createShips(int number) = 0;
	bool checkCoordinates(vector<pair<int, int>> coordinates);
	void markOwnShips(vector<pair<int, int>>coordinates);
	virtual void setShipToFire() = 0;
	virtual pair<int, int> setTarget() = 0;
	bool canDoAnything();
	bool isShotPossible(pair<int, int>target);
	virtual Ship& getShip(int a);
	Grid& getGrid(int a);
	virtual bool decide() = 0;
	virtual Ship& getSelected();
	int countShips();
	void saveGrids(const string& name);
	void saveShips(const string& name);
	void writeToGrids(const string& name);
	void writeShips(const string& name);
	bool isHuman();
};
#endif
