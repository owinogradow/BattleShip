#ifndef HUMAN_H_
#define HUMAN_H_
#include <vector>
#include <utility> 
#include "Player.h"
#include "HumanUI.h"
#include "Ship.h"

using namespace std;

class HumanPlayer: public Player
{
private:
	HumanUI* humanUI;
public:
	HumanPlayer();
	~HumanPlayer();
	void createShips(int number);
	void setShipToFire();
	pair<int, int> setTarget();
	bool decide();
	void roundCounting(Ship* temp);
};
#endif

