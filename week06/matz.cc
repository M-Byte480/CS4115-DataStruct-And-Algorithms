#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[])
{
	// Check for correct amount of arguments
	if(argc != 3)
	{
		cout<< "incorrect format" << endl;
		return 0;
	}
	// Take the user input
	int mRow, mColumn;
	mRow = atoi(argv[1]);
	mColumn = atoi(argv[2]);

	// Declare an array, a row non-zero counter, position reference array, total non-zero numbers
	float matrix[mRow][mColumn];
	int occurence[mRow];
	int totalCount = 0;

	cout << mRow << endl;

	// For each row
	for(int i = 0; i < mRow; i++)
	{
		// initialise the values
		occurence[i] = 0;

		for(int j = 0; j < mColumn; j++)
		{
			// read input then check for it being 0
			cin >> matrix[i][j];
			if(matrix[i][j])
			{	// increment counter, occurence and assign position
				totalCount++;
				occurence[i]++;
			}
		}
	}


// / *
	for(int i = 0; i < mRow; i++){
		cout << occurence[i] << " ";
		for(int j = 0; j < mColumn; j++){
			if(matrix[i][j]) cout << j+1 << " " << matrix[i][j] << " " ;
		}
		cout << endl;
	}
// */
	cout << totalCount << endl;
	return 0;
}
