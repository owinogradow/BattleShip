#ifndef GRID_H_
#define GRID_H_
#include <vector>
#include <utility> 
#include "Square.h"
#include "GridDisplay.h"

using namespace std;

const int WIDTH = 10;
const int HEIGHT = 10;

class Grid
{
private:
	vector<vector<Square>> squares;

public:
	enum grid_value { HIT = 1, SHIP = 2, MISS = 3 };
	Grid();
	~Grid();
	void markShip(pair<int, int>segment);
	int valueAt(int i, int j);
	bool wasAHit(pair<int, int>target);
	bool wasAMiss(pair<int, int> target);
	bool wasAlreadyATarget(pair<int, int> target);
	void markTarget(pair<int, int> target);
	void markAttackingGrid(pair<int, int> target, bool wasSuccessful);
	vector<vector<Square>> getVector();
	void saveGrid(const string& filename);
	Square& Grid::squareAt(int i, int j);
	void writeToGrid(vector<vector<int>> v1);
};

#endif
