#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

#pragma region RouteSearcher


class RouteSearcher
{
public:
	void dflt_map();
	void reset();
	void new_map(int);

	void position_initialization();
	int count_ways(int, int, int, int);
	void find_way(int, int, int, int, int, bool, bool, bool, bool);

	void print();

private:
	char map[10][10];
	int line_elements[10];

	bool position[4]; // used for skipping traversed route

	int newSRow;
	int newSColumn;

	int counter = 0;
};

void RouteSearcher::dflt_map()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			map[i][j] = 'X';

#pragma region def_map



	map[1][0] = '.';
	map[1][1] = '.';
	map[1][6] = '.';
	map[2][1] = '.';
	map[2][2] = '.';
	map[2][3] = '.';
	map[2][6] = '.';
	map[2][7] = '.';
	map[2][8] = '.';
	map[3][1] = '.';
	map[3][3] = '.';
	map[3][4] = '.';
	map[3][8] = '.';
	map[4][1] = '.';
	map[4][3] = '.';
	map[4][5] = '.';
	map[4][6] = '.';
	map[4][7] = '.';
	map[4][8] = '.';
	map[5][1] = '.';
	map[5][3] = '.';
	map[5][4] = '.';
	map[5][5] = '.';
	map[5][8] = '.';
	map[6][1] = '.';
	map[6][2] = '.';
	map[6][5] = '.';
	map[6][8] = '.';
	map[7][2] = '.';
	map[7][5] = '.';
	map[7][8] = '.';
	map[8][2] = '.';
	map[8][5] = '.';
	map[8][6] = '.';
	map[8][8] = '.';
	map[9][8] = '.';



#pragma endregion

}

void RouteSearcher::reset()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			map[i][j] = 'X';
}

void RouteSearcher::new_map(int i)
{
	cout << endl << "Enter \"99\" to Pass this Line\n" << "Enter \"55\" to Enter this Line Again\n" << "Enter \"11\" to Reset\n" << endl;
	cout << "Enter Open Routes Elements for Line \"" << i << "\"" << endl;	// how to Write commands in several lines ?

	for (int j = 0; j < 10; j++)
	{
		cin >> line_elements[j];

		if (line_elements[j] == 99 || j == 9)
		{
			print();
			if (i < 9)
				new_map(i += 1);
			break;
		}

		if (line_elements[j] == 55)
		{
			for (int k = 0; k < 10; k++)
				map[i][k] = 'X';

			new_map(i);
			break;
		}

		if (line_elements[j] == 11)
		{
			reset();
			new_map(0);
		}

		if (line_elements[j] >= 0 && line_elements[j] <= 9)
			map[i][line_elements[j]] = '.';
		else
		{
			cout << "Plz Enter a Number Between 0 & 9 !\n";
			j--;
		}
	}

	// how to delete line_elements (new int[100]) memory ? it returns itself !
}

void RouteSearcher::print()
{
	cout << endl;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << map[i][j] << " ";
		cout << endl;
	}
}

void RouteSearcher::position_initialization()
{
	for (int i = 0; i < 4; i++)
		position[i] = false;	// [0] = up, [1] = down, [2] = left, [3] = right
}

int RouteSearcher::count_ways(int SRow, int SColumn, int ERow, int EColumn)
{
	bool up = false, down = false, right = false, left = false;
	int count = 0;

	if (map[SRow][SColumn + 1] == '.')
	{
		if (position[3] == false)
		{
			count++;
			right = true;
		}
	}

	if (map[SRow][SColumn - 1] == '.')
	{
		if (position[2] == false)
		{
			count++;
			left = true;
		}
	}

	if (map[SRow + 1][SColumn] == '.')
	{
		if (position[1] == false)
		{
			count++;
			down = true;
		}
	}

	if (map[SRow - 1][SColumn] == '.')
	{
		if (position[0] == false)
		{
			count++;
			up = true;
		}
	}

	position_initialization();

	if (count == 0 && SRow != ERow && SColumn != EColumn)
		counter++;

	find_way(SRow, SColumn, ERow, EColumn, count, up, down, left, right);

	return counter;
}

void RouteSearcher::find_way(int SRow, int SColumn, int ERow, int EColumn, int count, bool up, bool down, bool left, bool right)
{
	switch (count)
	{
	case 1:

		if (down == true)
		{
			position[0] = true;
			count_ways(SRow += 1, SColumn, ERow, EColumn);
			break;
		}

		if (up == true)
		{
			position[1] = true;
			count_ways(SRow -= 1, SColumn, ERow, EColumn);
			break;
		}

		if (right == true)
		{
			position[2] = true;
			count_ways(SRow, SColumn += 1, ERow, EColumn);
			break;
		}

		if (left == true)
		{
			position[3] = true;
			count_ways(SRow, SColumn -= 1, ERow, EColumn);
			break;
		}

	case 2:
	case 3:

		if (map[SRow][SColumn + 1] == '.')
		{
			if (right == true)
			{
				newSRow = SRow;
				newSColumn = SColumn + 1;
				position[2] = true;
				count_ways(newSRow, newSColumn, ERow, EColumn);
			}
		}

		if (map[SRow][SColumn - 1] == '.')
		{
			if (left == true)
			{
				newSRow = SRow;
				newSColumn = SColumn - 1;
				position[3] = true;
				count_ways(newSRow, newSColumn, ERow, EColumn);
			}
		}

		if (map[SRow + 1][SColumn] == '.')
		{
			if (down == true)
			{
				newSRow = SRow + 1;
				newSColumn = SColumn;
				position[0] = true;
				count_ways(newSRow, newSColumn, ERow, EColumn);
			}
		}

		if (map[SRow - 1][SColumn] == '.')
		{
			if (up == true)
			{
				newSRow = SRow - 1;
				newSColumn = SColumn;
				position[1] = true;
				count_ways(newSRow, newSColumn, ERow, EColumn);
			}
		}

		/*default:;*/

	}
}


#pragma endregion

int main()
{
	int SRow = 1, SColumn = 0;
	int ERow = 9, EColumn = 8;
	bool choice;

	RouteSearcher RS;

	cout << "Default Map is: " << endl;
	RS.dflt_map();
	RS.print();

	cout << endl;

	cout << "Enter \"0\" for Default Map\n";
	cout << "Enter \"1\" to Create a Map\n";
	cout << "Your Choice: ";
	cin >> choice;

	cout << endl;

	if (choice == true)
	{
		cout << "Resetting Map ..." << endl;
		RS.reset();
		RS.print();

		cout << endl;

		cout << "Enter Starting Row: ";
		cin >> SRow;
		cout << "Enter Starting Column: ";
		cin >> SColumn;
		cout << "Enter Ending Row: ";
		cin >> ERow;
		cout << "Enter Ending Column: ";
		cin >> EColumn;

		cout << "==============================";

		RS.new_map(0);
	}

	RS.position_initialization();

	if (choice == true)
		cout << endl << "New Map is:" << endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	RS.print();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	int counter = RS.count_ways(SRow, SColumn, ERow, EColumn);
	cout << "\n  " << counter << " Wrong Ways !";

	_getch();
	return 0;
}
