#ifndef STRATEGY_H_
#define STRATEGY_H_
#include "ComputerPlayer.h"
#include "Ship.h"

class Strategy
{
protected:
	Player* aPlayer;
	vector<Ship*> shipsCapable;
public:
	Strategy(Player* aPlayer);
	Strategy();
	virtual ~Strategy();
	virtual Ship& selectShipToFire() = 0;
};

#endif