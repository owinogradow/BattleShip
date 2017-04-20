#include <iostream>
#include "Square.h"

Square::Square()
{
	this->state = 0;
}

int Square::getState()
{
	return state;
}

void Square::setState(int aState)
{
	state = aState;
}