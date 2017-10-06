#include <iostream>
#include <string.h>
#include <fstream>
#define MAX 40

using namespace std;

int R[MAX][MAX];   // a boolean array indicating members of a relation
int EC[MAX];       // a boolean array indicating representatives of equivalence classes
int size;

void printMatrix(int R[MAX][MAX]) {
	int i, j;

	for(i = 0; i < size; i++) {
		for(j = 0; j < size; j++)
			cout << R[i][j];
		cout << endl;
	}
}

int IsRefx(int R[MAX][MAX]) {
	bool result = true;

	for (int i = 0; i < size; ++i) {
		if (R[i][i] != 1) {
			result = false;
		}
	}

	return result;
}

int IsSymt(int R[MAX][MAX]) {
	bool result = true;

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++i) {
			if (R[i][j] == 1 && R[j][i] != 1) {
				result = false;
			}
		}
	}

	return result;
}

void SquareMatrix(int R[MAX][MAX], int R2[MAX][MAX]) {
}

int IsTrans(int R[MAX][MAX], int R2[MAX][MAX]) {
}

/*
	 Finds equivalence classes and elects representatives of each class.

	 EC will contain a list of class representatives aka "captians" represented
	 as an array of boolean flags.

	 Each row in a matrix represents an equivalence class.  But there may be
	 several duplicate rows.  Our task is to find the captian of each class,
	 which will be the first member of the class.

ALGORITHM:
0 is always a captian

For elements 1 thru N, assign each as a captian
then, go to that elements row and look backwards for members less than this.
If found, demote the captian.
This works because captains are the first members of their class.  Think about it.
*/
void FindECs(int R[MAX][MAX], int EC[MAX]) {
}


/*
	 Iterate thru the captains array.  For each captian, go to that row of
	 the matrix and print the members of the class.
	 */
void printECs(int R[MAX][MAX], int EC[MAX]) {
}


int main() {
	char c;

	// open source file
	ifstream fin( "R1.bin", ios_base::binary );
	if ( !fin ) { cerr << "Input file could not be opened\n"; exit(1); }

	// get the matrix size
	fin.read(&c, 1); size = c;

	// fill the matrix from the file
	int i, j;
	for(i = 0; i < size; i++)
		for(j = 0; j < size; j++)
		{
			fin.read(&c, 1);
			R[i][j] = c;
		}

	// close file
	fin.close();

	printMatrix(R);

	// more code....

}
