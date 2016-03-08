#include<vector>
#include<iostream>
using namespace std;

bool RecurseFind(vector<vector<int> > array, int begin_row, int end_row,
                 int begin_column, int end_column, int target)
{
	// begin from top-left position:
	for(; begin_row <= end_row; begin_row++)
	{
		for(begin_column = 0; begin_column <= end_column; begin_column++)
		{
			if(array[begin_row][begin_column] == target)  // find
			{
				return true;
			}
			if(array[begin_row][begin_column] > target)
				// delete itself column and all columns to its right
			{
				return RecurseFind(array, begin_row + 1, end_row, 0, begin_column - 1, target);
			}
		}
	}
	return false;
}

bool Find(vector<vector<int> > array,int target)
{
	int total_row = array.size();
	int total_column = array[0].size();
	return RecurseFind(array, 0, total_row - 1, 0, total_column - 1, target);
}

int main()
{
	vector<vector<int> > array =
	{
		{-9, -7, -2, 0, 3, 90},
		{-8, -4, -1, 7, 17, 91},
		{-7, -1, 0, 10, 27, 92},
		{1, 9, 13, 19, 38, 102},
		{3, 10, 22, 23, 46, 111},
		{24, 25, 29, 31, 55, 113},
		{53, 63, 70, 100, 103, 145},
	};
	while(1)
	{
		cout << "Input Target Number: ";
		int target;
		cin >> target;
		if(Find(array, target))
		{
			cout << "Find!\n";
		}
		else
		{
			cout << "Not Find!\n";
		}
	}

	return 0;
}

/*
Test numbers:
1. Numbers in array:
max: 145
min: -9
between max and min: 90 7 9 92 23 29 53
2. Numbers not in array:
bigger than max: 200 400
smaller than min: -10 -100
between max and min: 44 88
*/
