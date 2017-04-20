#ifndef SINGLE_H_
#define SINGLE_H_
#include "Ship.h"

using namespace std;

class SingleFunnel: public Ship
{
public:
	SingleFunnel(vector<pair<int, int>>coordinates, bool human = 1, Grid* secondary = NULL);
	SingleFunnel();
	bool canTakeShot();
	void fire();
};

#endif