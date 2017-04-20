#include <iostream>
#include <fstream>
#include <windows.h>
#include "GameLogic.h"
#include "Square.h"
#include "functions.h"

GameLogic::GameLogic(int currentRound, int rounds, int nComputerPlayers,  const string& strategy1, const string& strategy2)
{
	this->currentRound = currentRound;
	this->rounds = rounds;
	this->nComputerPlayers = nComputerPlayers;
	this->strategy1_info = strategy1;
	this->strategy2_info = strategy2;

	if (nComputerPlayers == 1)
	{
		firstPlayer = new HumanPlayer;
		secondPlayer = new ComputerPlayer(strategy1);
	}

	else if (nComputerPlayers == 2)
	{
		firstPlayer = new ComputerPlayer(strategy1);
		secondPlayer = new ComputerPlayer(strategy2);
	}
}

GameLogic::~GameLogic()
{
	delete firstPlayer;
	delete secondPlayer;
}

void GameLogic::play()
{
	if (fileExists("firstplayer.txt") && fileExists("secondplayer.txt"))
	{
		firstPlayer->writeToGrids("firstplayer.txt");
		secondPlayer->writeToGrids("secondplayer.txt");
		firstPlayer->writeShips("ships1.txt");
		secondPlayer->writeShips("ships2.txt");
	}

	else
	{
		display();
		for (int i = 1; i <= 3; i++)
		{
			firstPlayer->createShips(i);
			display();
		}
		for (int i = 1; i <= 3; i++)
		{
			secondPlayer->createShips(i);
		}
	}
	display();
	while (gameOver() != true)
	{
		playRound();
	}
	system("pause");
	system("cls");
	cout << "END";
}

void GameLogic::playRound()
{
	display();
	cout << "Round no." << currentRound << "\n" <<endl;
	cout << "First player shot/s" << endl;
	turn(firstPlayer, secondPlayer);
	cout << "\n";
	cout << "Second player shot/s" << endl;
	turn(secondPlayer, firstPlayer);
	currentRound++;
	saveGameState();
	system("pause");
}

void GameLogic::turn(Player* A, Player* B)
{
	pair<int, int> target;
	target = A->move();

	if (target.first == -1)
	{
		cout << "here";
		return;
	}
	bool wasSuccessful = B->checkShot(target);

	A->markShot(target, wasSuccessful);

	if (A->getSelected().getSize() > 1)
	{
		bool decision = A->decide();

		if (decision)
		{
			pair<int, int> target2;
			target2 = A->setTarget();

			A->getSelected().fire();
			bool wasSuccessful = B->checkShot(target2);
			A->markShot(target2, wasSuccessful);
		}
	}
}

bool GameLogic::gameOver()
{
	bool anyRoundsLeft = currentRound <= rounds;
	bool firstCanHaveMove = firstPlayer->canDoAnything();
	bool secondCanHaveMove = secondPlayer->canDoAnything();

	if (anyRoundsLeft && firstCanHaveMove && secondCanHaveMove)
		return false;
	else
	{
		if (!anyRoundsLeft)
		{
			int firstShipCount = firstPlayer->countShips();
			int secondshipCount = secondPlayer->countShips();

			if (firstShipCount > secondshipCount)
				cout << "Player 1 wins!" << endl;
			else if (secondshipCount < firstShipCount)
				cout << "Player 2 wins!" << endl;
			else
				cout << "We have a draw." << endl;
		}
		if (!firstCanHaveMove && !secondCanHaveMove)
		{
			cout << "We have a draw." << endl;
		}
		else if (!firstCanHaveMove)
			cout << "Player 2 wins!" << endl;
		else if (!secondCanHaveMove)
			cout << "Player 1 wins!" << endl;

		return true;
	}
}

void GameLogic::display()
{
	if (nComputerPlayers == 1)
	{
		system("cls");
		vector<vector<Square>> primary = firstPlayer->getGrid(1).getVector();
		vector<vector<Square>> secondary = firstPlayer->getGrid(2).getVector();
		GD->display(primary, secondary);
	}
	else
	{
		system("cls");
		vector<vector<Square>> primary1 = firstPlayer->getGrid(1).getVector();
		vector<vector<Square>> secondary1 = firstPlayer->getGrid(2).getVector();
		GD->display(primary1, secondary1);

		vector<vector<Square>> primary2 = secondPlayer->getGrid(1).getVector();
		vector<vector<Square>> secondary2 = secondPlayer->getGrid(2).getVector();
		GD->display(primary2, secondary2);
		Sleep(2000);
	}
}


void GameLogic::saveGameState()
{
	//saving initial conditions
	ofstream myfile;
	myfile.open("gamestate.txt");
	myfile << currentRound << endl << rounds << endl << nComputerPlayers << endl << strategy1_info << endl << strategy2_info << endl;
	myfile.close();

	//saving grids' state
	firstPlayer->saveGrids("firstplayer.txt");
	secondPlayer->saveGrids("secondplayer.txt");

	//saving ships
	firstPlayer->saveShips("ships1.txt");
	secondPlayer->saveShips("ships2.txt");
}