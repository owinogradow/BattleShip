#include <iostream>
#include <string>
#include <ctime>
#include "GameLogic.h"
#include "functions.h"

using namespace std;

int main(int argc, char* argv[])
{
	srand(time(NULL));

	options opt = parse_args(argc, argv);
	GameLogic gl(opt.currentRound, opt.rounds, opt.nComputerPlayers, opt.strategy1, opt.strategy2);
	gl.play();
	return 0;
}


