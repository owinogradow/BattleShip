#ifndef GREEDY_H_
#define GREEDY_H_
#include "Strategy.h"
#include "ComputerPlayer.h"

class Greedy: public Strategy
{
public:
	Greedy(ComputerPlayer* aPlayer);
	Greedy();
	~Greedy();
	Ship& selectShipToFire();
};

#endif