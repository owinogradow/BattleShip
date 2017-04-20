#ifndef SEGMENT_H_
#define SEGMENT_H_
#include <utility>
using namespace std;

class Segment
{
private:
	pair<int, int> coords;
	bool was_Hit;

public:
	Segment(int row, int column);
	~Segment();
	pair<int, int> getCoords();
	bool wasHit();

};

#endif