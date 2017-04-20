#include <iostream>
#include "GridDisplay.h"
#include <iomanip>

using namespace std;

	GridDisplay::GridDisplay()
	{}

	void GridDisplay::display(vector<vector<Square>> squares1, vector<vector<Square>> squares2)
	{
		cout << setw(10) << ' ';
		cout << "Ship Grid";
		cout << setw(25) << ' ';
		cout << "Attacking Grid" << endl;

		cout << setw(5) << ' ';

		for (char c = 'A'; c < 'K'; c++)
		{
			cout << ' ' << c;
		}

		cout << ' ' << setw(16);

		for (char c = 'A'; c < 'K'; c++)
		{
			cout << ' ' << c;
		}

		cout << endl;


		for (int i = 0; i < HEIGHT; i++)
		{
			cout << setw(5);
			cout << i << '|';

			for (int j = 0; j < WIDTH; j++)
			{
				Square aSquare1 = squares1[i][j];
				print_square(aSquare1);
			}

			cout << ' ' << setw(14);
			cout << i << '|';

			for (int j = 0; j < WIDTH; j++)
			{
				Square aSquare2 = squares2[i][j];
				print_square(aSquare2);
			}

			cout << endl;
		}

		cout << endl;
	}

	void GridDisplay::print_square(Square aSquare)
	{
		int value = aSquare.getState();
		char c;

		switch (value)
		{
		case 0:
			c = ' ';
			break;
		case 2:
			c = 'O';
			break;
		case 3:
			c = 'X';
			break;
		case 1:
			c = '$';
			break;
		}

		cout << c << '|';
	}
