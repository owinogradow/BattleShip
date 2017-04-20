#ifndef GRIDDISPLAY_H_
#define GRIDDISPLAY_H_

#include <iostream>
#include <vector>
#include <string>
#include "Square.h"

using namespace std;

class Grid;

class GridDisplay
{
private:
	static const int WIDTH = 10;
	static const int HEIGHT = 10;

public:
	GridDisplay();
	void display(vector<vector<Square>> squares1, vector<vector<Square>> squares2);
	void print_square(Square aSquare);
};

#endif

