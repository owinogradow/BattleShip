#ifndef SQUARE_H_
#define SQUARE_H_
#include <iostream>



class Square
{
private:
	int state;
public:
	Square();
	int getState();
	void setState(int aState);
};
#endif
