#include <iostream>
#include <string.h>
#include <fstream>
#include <cstdlib>
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
		for (int j = 0; j < size; ++j) {
			if (R[i][j] == 1 && R[j][i] != 1) {
				result = false;
			}
		}
	}

	return result;
}

void SquareMatrix(int R[MAX][MAX], int R2[MAX][MAX]) {
	int temp = 0;

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			for (int k = 0; k < size; ++k) {
				temp += R[i][k] * R[j][k];
			}

			R2[i][j] = temp;
			temp = 0;
		}
	}
}

int IsTrans(int R[MAX][MAX], int R2[MAX][MAX]) {
	bool result = true;

	SquareMatrix(R, R2);

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (R[i][j] == 0 && R2[i][j] != 0) {
				result = false;
			}
		}
	}

	return result;
}

void FindECs(int R[MAX][MAX], int EC[MAX]) {
	for (int x = 0; x < MAX; ++x) EC[x] = 0;

	EC[0] = 1;

	for (int i = 1; i < size; ++i) {
		EC[i] = 1;
		for (int j = i - 1; j >= 0; --j) {
			if (R[i][j]) EC[i] = 0;
		}
	}
}

void printECs(int R[MAX][MAX], int EC[MAX]) {
	for (int i = 0; i < MAX; ++i) {
		if (EC[i]) {
			cout << "[" << i << "] : {";
			for (int j = 0; j < size; ++j) {
				if (R[i][j]) cout << " " << j;
			}
			cout << " } \n";
		}
	}

	cout << endl;
}

int main (int argc, char* argv[]) {
	if (argc != 2) {
		std::cout
			<< "Usage: pass a number as a command line argument\n"
			<< "corresponding to which input file you'd like to use.";
		exit(1);
	}

	char c;
	std::string start = "R";
	std::string end = ".bin";
	std::string filename = start + argv[1] + end;
	ifstream fin(filename.c_str(), ios_base::binary);
	if ( !fin ) { cerr << "Input file could not be opened\n"; exit(1); }

	fin.read(&c, 1); size = c;

	int i, j;
	for(i = 0; i < size; i++)
		for(j = 0; j < size; j++)
		{
			fin.read(&c, 1);
			R[i][j] = c;
		}

	fin.close();

	printMatrix(R);
	cout << endl;

	bool is_EQR = true;

	IsRefx(R) ?
		(cout << "Is Reflexive\n") :
		(is_EQR = false, cout << "Isn't Reflexive\n");
	IsSymt(R) ?
		(cout << "Is Symetrical\n") :
		(is_EQR = false, cout << "Isn't Symetrical\n");

	int trans_test[MAX][MAX] = {{0}};
	IsTrans(R, trans_test) ?
		(cout << "Is Transitive\n") :
		(is_EQR = false, cout << "Isn't Transitive\n");

	int temp[MAX][MAX] = {{0}};
	SquareMatrix(R, temp);
	cout << endl;
	printMatrix(temp);

	if (is_EQR) {
		FindECs(R, EC);
		cout << "\nEquiv. classes: \n";
		printECs(R, EC);
	}
}
