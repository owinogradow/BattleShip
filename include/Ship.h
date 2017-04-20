#ifndef SHIP_H_
#define SHIP_H_
#include <vector>
#include <utility>
#include <exception>
#include "Segment.h"
#include "Grid.h"

using namespace std;

class Ship
{
private:
	bool human;
	int length;
	int range;
	bool sunk;
	int shots;
	vector<Segment> segments;
	bool is_reloaded;
	int roundCounter2;
	int roundCounter3;
	Grid* attackGD;

public:
	class Exception {};
	class ShipHaveToWaitException : Exception {};

	Ship(vector<pair<int, int>>coordinates, bool human, Grid* secondary);
	Ship();
	~Ship();
	bool isSunk();
	bool isInRange(pair<int, int>target);
	virtual void fire() = 0;
	virtual bool canTakeShot() = 0;
	int getRange();
	int getSize();
	vector<pair<int, int>>possibleTargets();
	void set_is_reloaded(bool value);
	bool isReloaded();
	int intactSegments();
	bool belongsToHuman();
	void add_roundCounter2(int value);
	void add_roundCounter3(int value);
	int get_roundCounter2();
	int get_roundCounter3();
	vector<pair<int, int>> getLocation();

};
#endif