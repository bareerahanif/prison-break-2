#include <iostream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

#define maxRows 100
#define maxCols 100

void loadArray(ifstream& rdr, int PrisonMap[][maxCols], int& rows, int& cols)
{
	rdr >> rows >> cols;
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			rdr >> PrisonMap[r][c];
		}

	}

}
void printArray(const char MSG[], int PrisonMap[][maxCols], int rows, int cols)
{

	cout << endl << endl << MSG << endl;
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			cout << setw(2) << PrisonMap[r][c];
		}
		cout << endl;
	}
}
void Forward(int ri, int ci, int PrisonMap[][maxCols], int rows, int cols, bool& changeHappen)
{
	for (int r = ri - 1; r <= ri + 1; r++)
	{
		for (int c = ci - 1; c <= ci + 1; c++)
		{
			if ((r < 0 || r > rows - 1 || c < 0 || c > cols - 1) || (r == ri && c == ci))
				continue;
			else if (PrisonMap[r][c] == 0)
			{
				PrisonMap[r][c] = 3;
				changeHappen = true;
			}
		}
	}
}
void calculate_Strides(int PrisonMap[][maxCols], int rows, int cols)
{
	bool changeHappen;
	bool found = false;
	for (int r = 0; r < rows && !found; r++)
	{
		for (int c = 0; c < cols && !found; c++)
		{
			if (PrisonMap[r][c] == 2)
			{
				Forward(r, c, PrisonMap, rows, cols, changeHappen);
				found = true;  
			}
		}
	}
	do
	{
		changeHappen = false;  
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				if (PrisonMap[r][c] == 3)
				{
					Forward(r, c, PrisonMap, rows, cols,
						changeHappen);
				}
			}
		}
	} while (changeHappen);
}
bool ReachBoundary(int PrisonMap[][maxCols], int rows, int cols)
{
	for (int c = 0; c < cols; c++)
	{
		if (PrisonMap[1][c] == 2 || PrisonMap[1][c] == 3)
			return true;
	}
	for (int c = 0; c < cols; c++)
	{
		if (PrisonMap[rows - 1][c] == 2 || PrisonMap[rows - 1][c] == 3)
			return true;
	}
	for (int r = 0; r < rows; r++)
	{
		if (PrisonMap[r][0] == 2 || PrisonMap[r][0] == 3)
			return true;
	}
	for (int r = 0; r < rows; r++)
	{
		if (PrisonMap[r][cols - 1] == 2 || PrisonMap[r][0] == 3)
			return true;
	}
	return false;
}
bool isPrisonBreakable(int PrisonMap[][maxCols], int rows, int cols)
{
	calculate_Strides(PrisonMap, rows, cols);
	return ReachBoundary(PrisonMap, rows, cols);
}
void prison_BreakSolver(int PrisonMap[][maxCols], int rows, int cols)
{
	if (isPrisonBreakable(PrisonMap, rows, cols))
		cout << "Free";
	else
		cout << "Prisoned for Life...";
}
int main()
{
	int aPrisonMap[maxRows][maxCols], rows, cols;
	ifstream rdr("Maps.txt");
	int noOfMaps;
	rdr >> noOfMaps;
	for (int ci = 1; ci <= noOfMaps; ci++)
	{
		loadArray(rdr, aPrisonMap, rows, cols);
		printArray(("Prison " + to_string(ci) + ": ").c_str(), aPrisonMap, rows, cols);
		prison_BreakSolver(aPrisonMap, rows, cols);
		printArray(("After All Strides "), aPrisonMap, rows, cols);

		cout << endl;
	}
	return 0;
}
