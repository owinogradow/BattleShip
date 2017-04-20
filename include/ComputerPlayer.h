#ifndef COMPUTER_H_
#define COMPUTER_H_
#include <vector>
#include <utility> 
#include "Player.h"

#include <string>

class Strategy;

using namespace std;

class ComputerPlayer: public Player
{
private:
	Strategy* aStrategy;
public:
	ComputerPlayer(const string& sstrategy);
	ComputerPlayer();
	~ComputerPlayer();
	void createShips(int number);
	void setShipToFire();
	pair<int, int> setTarget();
	bool decide();
};
#endif
