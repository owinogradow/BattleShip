#ifndef MULTI_H_
#define MULTI_H_
#include "Ship.h"

class MultipleFunnel : public Ship
{
private:
	int shotsCounter = 0;


public:
	MultipleFunnel(vector<pair<int, int>>coordinates, bool human = 1, Grid* secondary = NULL);
	MultipleFunnel();
	bool canTakeShot();
	void fire();
	
};
#endif