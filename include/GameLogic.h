#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_
#include "HumanPlayer.h"
#include "ComputerPlayer.h"


class GameLogic
{
private:
	int currentRound;
	int rounds;
	int nComputerPlayers;
	string strategy1_info;
	string strategy2_info;
	void playRound();
	Player* firstPlayer;
	Player* secondPlayer;
	GridDisplay* GD;

public:
	GameLogic(int currentRound, int rounds, int nComputerPlayers,  const string& strategy1, const string& strategy2 = 0);
	~GameLogic();
	void play();
	bool gameOver();
	void display();
	void turn(Player* A, Player* B);
	void saveGameState();
};
#endif