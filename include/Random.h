#ifndef RANDOM_H_
#define RANDOM_H_
#include "Strategy.h"
#include "ComputerPlayer.h"

class Random: public Strategy
{
public:
	Random(ComputerPlayer* aPlayer);
	Random();
	~Random();
	Ship& selectShipToFire();
};

#endif