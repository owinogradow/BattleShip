#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <utility>
#include <regex>
#include <cstdlib>
#include <exception>

#include "Player.h"
#include "functions.h"

using namespace std;
using std::regex;


pair<int, int> operator+(const pair<int, int> &a, const pair<int, int> &b)
{
	return make_pair(a.first + b.first, a.second + b.second);
}



int chessboard_distance(pair<int,int> a, pair<int,int> b)
{
	int x_difference = abs(a.first - b.first);
	int y_difference = abs(a.second - b.second);

	if (x_difference > y_difference)
		return x_difference;
	else
		return y_difference;
}

double euclidean_distance(pair<int, int> a, pair<int, int> b)
{
	int x_difference = abs(a.first - b.first);
	int y_difference = abs(a.second - b.second);

	return sqrt(pow(x_difference, 2) + pow(y_difference, 2));
}

int random_number(int a, int b)
{
	return rand() % a + b;
}

vector<pair<int, int>> vector_of_pairs(int a)
{
	pair <int, int > tab[4]{ {0,-1},{0,1},{-1,0},{1,0} };
	vector< pair <int, int> > random_vector;
	pair <int, int> temp;

	int x = random_number(6, 2);
	int y = random_number(6, 2);
	temp = make_pair(x, y);
	random_vector.push_back(temp);

	if (a >= 2)
	{
		int random_shift = random_number(4, 0);
		pair<int, int> to_add = temp + tab[random_shift];
		random_vector.push_back(to_add);

		if (a == 3)
		{
			pair<int, int> next_to_add = to_add + tab[random_shift];
			random_vector.push_back(next_to_add);
		}
	}
	return random_vector;
}

options resumeGame()
{
	options temp;

	if (fileExists("firstplayer.txt") && fileExists("secondplayer.txt") && fileExists("gamestate.txt"))
	{
		ifstream infile;
		infile.open("gamestate.txt");

		while (!infile.eof())
		{
			infile >> temp.currentRound >> temp.rounds >> temp.nComputerPlayers >> temp.strategy1 >> temp.strategy2;
		}

		infile.close();
	}
	return temp;
}



options parse_args(int argc, char* argv[])
{
	options temp;

	if (argc == 2 && strcmp(argv[1], "--resume") == 0)
	{
		temp = resumeGame();
	}

	else if (argc < 3 || argc > 4)
	{
		cout << "Wrong number of arguments" << endl;
		exit(0);
	}
	else if (atoi(argv[1]) > 20) 
	{
		cout << "rounds number can be maximum equal to 20" << endl;
		exit(0);
	}

	else
	{
		if (fileExists("firstplayer.txt") && fileExists("secondplayer.txt") && fileExists("gamestate.txt") && 
			fileExists("ships1.txt") && fileExists("ships2.txt"))
		{
			remove("firstplayer.txt");
			remove("secondplayer.txt");
			remove("gamestate.txt");
			remove("ships1.txt");
			remove("ships2.txt");
		}

		temp.currentRound = 1;
		temp.rounds = atoi(argv[1]);
		temp.strategy1 = argv[2];

		if (argc == 3)
		{
			temp.nComputerPlayers = 1;
		}

		else if (argc == 4)
		{
			temp.nComputerPlayers = 2;
			temp.strategy2 = argv[3];
		}
	}
	return temp;
}

pair<int, int> convert_input(const string& input)
{
	regex rgx1("^[0-9]{1}[a-zA-Z]{1}$");
	regex rgx2("^[a-zA-Z]{1}[0-9]{1}$");
	std::cmatch match;

	char a, b;
	a = toupper(input[0]);
	b = toupper(input[1]);

	if (regex_match(input, rgx1))
	{
		int x = (int)a - '0';
		int y = (int)b - 'A';
		pair<int, int> temp;
		temp = make_pair(x, y);
		return temp;
	}
	else if (regex_match(input, rgx2))
	{
		int x = (int)a - 'A';
		int y = (int)b - '0';
		pair<int, int> temp;
		temp = make_pair(y, x);
		return temp;
	}
	else
		throw invalid_argument("Please input your coordinates carefully");
}

bool fileExists(const char* fileName)
{
	ifstream infile(fileName);
	return infile.good();
}
	
vector<vector<int>> D_to_2D(vector<int> to_process)
{
	vector <vector<int>> result;
	int t = 0;

	for (int i = 0; i < 10; i++)
	{
		vector <int> row;
		for (int j = 0; j < 10; j++)
		{
			row.push_back(to_process[t]);
			t++;
		}
		result.push_back(row);
	}
	return result;
}