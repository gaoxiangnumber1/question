/*
------------------------------Function Test Data------------------------------
nonempty array and arbitrary integer

---------------------------------Edge Test Data--------------------------------
none

------------------------------Negative Test Data------------------------------
empty array

*/

#include<vector>
#include<iostream>
using namespace std;

bool Find(vector<vector<int> > array, int target)
{
	// get the size of array's row and column
	int total_row = array.size();
	int total_column = total_row ? array[0].size() : 0;
	// negative data:
	if(!total_row || !total_column)
	{
		return false;
	}

	for(int row = 0, column = total_column - 1; row < total_row && column >= 0; )
	{
		if(array[row][column] == target)  // find the target
		{
			return true;
		}
		if(array[row][column] > target)  // move to left by one position
		{
			--column;
		}
		else  // move down by one position
		{
			++row;
		}
	}
	return false;
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