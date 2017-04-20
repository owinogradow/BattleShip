#ifndef HUMANUI_H_
#define HUMANUI_H_
#include <vector>
#include <utility> 

using namespace std;

class HumanUI
{
public:
	HumanUI();
	virtual ~HumanUI();
	virtual vector<pair<int,int>>askShipsPosition(int funnels_nr);
	virtual int askShipToFire();
	virtual pair<int, int> askTarget();
	bool askDecision();

};
#endif

