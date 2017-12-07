/*
	A state machine to find all occurances of the string "abab"

	input file "abab.txt":
	aaaaaababbaaaababababaabaabbbbaabbabbabababbbbbbbabbababaaabaabbab

	output:
	aaaaaabab8baaaabab16ab18ab20aabaabbbbaabbabbabab40ab42bbbbbbabbabab55aaabaabbab
	
	Dan Ross
	April 2013
*/
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

#define STATES 20    // room for cream
// State Table for:  "abab"
//            [state][ch] 
char nextState[STATES][2] = {
//     a  b   //input
       1, 0,  //state 0
	   1, 2,  //state 1
	   3, 0,  //state 2
	   1, 4,  //state 3
	   3, 0,  //state 4
};

char state = 0;
int count = 0;


//////////////////////////////////////////////////
//  BEGIN SECTION 42: STUFF YOU MAY NEED LATER
//////////////////////////////////////////////////

// hard code input string
char instr[80] = "abab";  


void print_StateTable()
{
	cout << "s\ta\tb\n\n";
	
	int l = strlen(instr) + 1;
	for(int s = 0; s < l; s++) {
		cout << s << "\t";
		for(int ch = 0; ch < 2; ch++)
			cout << (int) nextState[s][ch] << "\t";
		cout << endl;
	}
}


/*
Compares first n characters of str1,
with last n characters of str2.

Returns 0 (false) if they match

Copyright (c) 1981 Dan Ross
*/
int strncmp_olap(char * str1, char * str2, int n)
{
	int i, j;
	int l1 = strlen(str1);
	int l2 = strlen(str2);

	for(i = 0, j = l2 - n; i < n ; i++, j++)
		if(str1[i] != str2[j])
			return true;

	return false;
}


/*
Generate a state table for a sequence detector
*/
void generate_StateTable(void)
{
	// you write this

	/* you may need these things...
	char got[80];
	got[0] = 0;         // the null terminator starring the Governator!
	strncpy(...);       // handy, but it doesn't do this: got[zeroSpot] = 0;
	strcat(...);	    // for sticking on a's and b's
	strlen(...);		// is useful too
	strncmp_olap(..)	// an amazing function!  try it!
	*/
}


//////////////////////////////////////////////
//  END SECTION 42
//////////////////////////////////////////////



// A State Machine
void process(char ch)
{
	// print current char
	cout << ch;
	
	// move to next state
	state = nextState[state][ch - 'a'];

	// output count if we are in the accept state
	if(state == 4) cout << count + 2;  // +2 for notepad

	count++;  //another ch bites the dust!
}

int main()
{
	generate_StateTable();  // you write
	print_StateTable();

	char ch;
	
	// open a file
	ifstream in("abab.txt");
	if(!in){
		cout << "Error opening file";
	}

	// read characters from file and process them
	while(in){
		in.get(ch);
		if(in)
			process(ch);
	}

}
