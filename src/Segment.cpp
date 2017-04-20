#include <iostream>
#include "Segment.h"

using namespace std;

Segment::Segment(int row, int column)
{
	this->coords = make_pair(row, column);
	this->was_Hit = 0;
}

Segment::~Segment()
{
	this->was_Hit = 0;
}

pair<int, int> Segment::getCoords()
{
	return coords;
}

bool Segment::wasHit()
{
	return was_Hit;
}