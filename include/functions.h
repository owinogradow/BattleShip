#include <iostream>
#include <utility>
using namespace std;

struct options
{
	int currentRound;
	int rounds;
	int nComputerPlayers;
	string strategy1;
	string strategy2;
};

int chessboard_distance(pair<int, int> a, pair<int, int> b);

double euclidean_distance(pair<int, int> a, pair<int, int> b);
int random_number(int a, int b);
vector<pair<int, int>> vector_of_pairs(int a);
options resumeGame();
options parse_args(int argc, char* argv[]);
pair<int, int> convert_input(const string& input);
bool fileExists(const char* fileName);
vector <vector<int>> D_to_2D(vector<int> to_process);

