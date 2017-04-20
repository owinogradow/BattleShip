#include <iostream>
#include "HumanUI.h"
#include <string>
#include "functions.h"

using namespace std;

HumanUI::HumanUI()
{}

HumanUI::~HumanUI()
{}

vector<pair<int, int>> HumanUI::askShipsPosition(int funnels_nr)
{
	vector< pair<int, int> >coordinates;
	string xy;
	pair <int, int> temp;

	cout << endl << "Building ship with " << funnels_nr << " segments." << endl;
	for (int i = 1; i <= funnels_nr; i++)
	{
		cout << "Enter coordinates of the " << i << " ship segment: ";
		cin >> xy;
		pair <int, int> temp = convert_input(xy);
		coordinates.push_back(temp);
	}
	return coordinates;
}

int HumanUI::askShipToFire()
{
	int i = 0;
	cout << "Enter the number of ship to fire: ";
	cin >> i;

	while (i != 1 && i != 2 && i != 3)
	{
		cin.clear();
		cin.ignore();
		cout << "The number of ship must be 1, 2 or 3!" << endl
			<< "Enter the number of ship to fire: ";
		cin >> i;
	}
	return i;
}

pair<int, int> HumanUI::askTarget()
{
	string xy;
	pair <int, int> target;
	cout << "Enter the target: ";
	cin >> xy;

	target = convert_input(xy);
	return target;
}


bool HumanUI::askDecision()
{
	char c;
	cout << "Multifunnel ship was selected. Do you want to take one more shot? y/n" << endl;
	cin >> c;

	while (c != 'y' && c != 'n')
	{
		cout << "Wrong input. Answer has to be y or n!" << endl;
		cin >> c;
	}
	if (c == 'y')
		return true;
	else if (c == 'n')
		return false;
}