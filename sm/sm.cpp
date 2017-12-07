#include <iostream>
#include <fstream>
#include <cstring>

#define STATES 40

char nextState[STATES][2]; // = {{1, 0},{1, 2},{3, 0},{1, 4},{3, 0},};
unsigned char state = 0;
int count = 0;
char instr[80];

void print_StateTable()
{ 
	printf ("    s    a    b\n\n");

	int l = strlen(instr) + 1;
	for(int s = 0; s < l; s++) {
		printf ("%5i", s);
		for(int ch = 0; ch < 2; ch++)
			printf ("%5i", (int)nextState[s][ch]);
		printf ("\n");
	}
}

int strncmp_olap(char * str1, char * str2, int n)
{
	// Compares first n characters of str1,
	// with last n characters of str2.
	// Returns 0 (false) if they match
	int i, j;
	//int l1 = strlen(str1);
	int l2 = strlen(str2);

	for(i = 0, j = l2 - n; i < n ; i++, j++)
		if(str1[i] != str2[j])
			return true;

	return false;
}

void strclean (char str[], int size)
{
	for (int i = 0; i < size; ++i)
		str[i] = '\0';
}

void generate_StateTable(void)
{
	char got[80];
	strclean (got, 80);
	int max_olap = 0;
	printf("Generating state table for %s...\n", instr);
	for (char c = 'a'; c <= 'b'; ++c) {
		for (unsigned s = 0; s < (strlen (instr) + 1); ++s) {
			strcpy (got, instr);
			got[s + 1] = '\0';
			got[s] = c;
			max_olap = 0;
			for (size_t x = 1; x <= strlen(instr) && x <= strlen(got); ++x)
				if (!strncmp_olap (instr, got, x))
					max_olap = x;
			printf ("State: %i  -  Input: %c  -  Next State: %i\n", s, c, max_olap);
			nextState[s][c - 97] = max_olap;
			strclean(got, 80);
		}
	}
}

void process(char ch)
{
	// move to next state
	state = nextState[state][ch - 'a'];

	// output count if we are in the accept state
	if(state == strlen(instr)) 
		printf("%i ", (count + 2));  // +2 for notepad

	count++;  //another ch bites the dust!
}

void clean_and_run (char str[])
{
	char ch;
	for (int i = 0; i < STATES; ++i)
		for (int j = 0; j < 2; ++j)
			nextState[i][j] = 0;
	count = 0;
	strcpy (instr, str);
	state = 0;
	generate_StateTable();
	print_StateTable();
	std::ifstream in("./monkeydata.txt");
	if(!in){
		printf ("Error opening file\n");
	}
	printf ("The search string was found in the following locations: ");
	while(in){
		in.get(ch);
		if(in)
			process(ch);
	}
	printf ("\n");
	in.close();
}

int main()
{
	char inputs[5][80] =
	{
		"abbbbbbaaaaaba",
		"abbbbaabbbbaaa",
		"aaaaaaabaaaaaaa",
		"aabbbababaaababbaaaa",
		"aaaabababaaaaabbaaaa"
	};

	for (int i = 0; i < 5; ++i)
		clean_and_run (inputs[i]);
}
