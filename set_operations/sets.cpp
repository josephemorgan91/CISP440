#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char Universe[8][10] = { "Bat", "Cat", "Chimp", "Dog", "Fish", "Liger", "Snake", "Turtle" };
typedef unsigned char set;

char BigUniverse[32][20] = {
	"Bat", "Cat", "Chimp", "Dog", "Fish", "Liger", "Snake", "Turtle",
	"Bear", "Dragon", "Horse", "Wolf", "Rat", "Gerbil", "Rabbit", "Monkey",
	"Donkey", "Llama", "Zebra", "Hippopotamus", "Rhiceros", "Gecko", "Frog", "Sloth",
	"Deer", "Kangaroo", "Gorilla", "Alligator", "Panda", "Squirrel", "Duck", "Platypus" };
typedef unsigned long int set32;

void printSet(set);
void printSet(set32);
void print8bits(unsigned char);
void print16bits(unsigned long int);
void insert(set&, char[]);
unsigned long hash_slinger (char[], int[]);
void insert(set32&, char[]);
int my_pow(int, int);
set Union(set, set);
set32 Union(set32, set32);
set Intersection(set, set);
set32 Intersection(set32, set32);
set Complement(set);
set32 Complement(set32);
set Difference(set, set);
set32 Difference(set32, set32);
int Cardinality(set);
int Cardinality(set32);
void printPowerSet(set);
void printPowerSet(set32);
bool IsSubset(set, set);
bool IsSubset(set32, set32);
bool IsProperSubset(set, set);
bool IsProperSubset(set32, set32);
void test_operations(set, set, set);
void test_operations(set32, set32, set32);

int main(void)
{
	set A = 0, B = 0, C = 0;

	// Fill A
	insert(A, "Cat");
	insert(A, "Dog");
	insert(A, "Fish");

	// Fill B
	insert(B, "Cat");
	insert(B, "Dog");
	insert(B, "Liger");

	// Fill C
	insert(C, "Dog");
	insert(C, "Liger");
	insert(C, "Snake");
	insert(C, "Turtle");

	printf("8 Bit Universe Operations: \n");
	printf("************************************************\n");
	printf("Set A: ");
	printSet(A);
	printf("\nSet B: ");
	printSet(B);
	printf("\nSet C: ");
	printSet(C);
	printf("\n************************************************\n");
	printf("\n");

	test_operations(A, B, C);

	A = 0;
	B = 0;
	C = 0;

	// Fill A
	insert(A, "Bat");
	insert(A, "Chimp");
	insert(A, "Liger");
	insert(A, "Snake");
	insert(A, "Turtle");

	// Fill B
	insert(B, "Bat");
	insert(B, "Cat");
	insert(B, "Chimp");
	insert(B, "Dog");
	insert(B, "Fish");

	// Fill C
	insert(C, "Dog");
	insert(C, "Fish");
	insert(C, "Liger");
	insert(C, "Snake");
	insert(C, "Turtle");

	printf("\n\n************************************************\n");
	printf("Set A: ");
	printSet(A);
	printf("\nSet B: ");
	printSet(B);
	printf("\nSet C: ");
	printSet(C);
	printf("\n************************************************\n");
	printf("\n");

	test_operations(A, B, C);

	printf("\n\n32 Bit Universe Operations: \n");
	set32 X = 0, Y = 0, Z = 0;

	// Fill X
	insert(X, "Bat");
	insert(X, "Dragon");
	insert(X, "Hippopotamus");
	insert(X, "Gecko");
	insert(X, "Sloth");
	insert(X, "Deer");
	insert(X, "Kangaroo");

	// Fill Y
	insert(Y, "Hippopotamus");
	insert(Y, "Gecko");
	insert(Y, "Sloth");
	insert(Y, "Bat");
	insert(Y, "Rhinoceros");
	insert(Y, "Squirrel");
	insert(Y, "Platypus");
	
	// Fill Z
	insert(Z, "Gecko");
	insert(Z, "Sloth");
	insert(Z, "Bat");
	insert(Z, "Rhinoceros");
	insert(Z, "Dog");
	insert(Z, "Fish");
	insert(Z, "Horse");
	insert(Z, "Snake");
	insert(Z, "Turtle");
	insert(Z, "Donkey");
	insert(Z, "Gorilla");
	insert(Z, "Llama");

	printf("************************************************\n");
	printf("Set A: ");
	printSet(X);
	printf("\nSet B: ");
	printSet(Y);
	printf("\nSet C: ");
	printSet(Z);
	printf("\n************************************************\n");
	printf("\n");

	test_operations(X, Y, Z);
}

void printSet(set A)
{
	printf("{ ");

	bool commaflag = false;
	int i = 0;
	unsigned char mask = 0x80;
	for (; mask; mask >>= 1, i++)
	{
		if (mask & A)
		{
			if (commaflag) printf(", ");
			printf("%s", Universe[i]);
			commaflag = true;
		}
	}
	printf(" }");
}

void printSet(set32 A)
{
	printf("{ ");

	bool commaflag = false;
	int i = 0;
	unsigned long int mask = 0x80000000;
	for (; mask; mask >>= 1, i++)
	{
		if (mask & A)
		{
			if (commaflag) printf(", ");
			printf("%s", BigUniverse[i]);
			commaflag = true;
		}
	}
	printf(" }");
}

void print8bits(unsigned char x)
{
	for (unsigned char mask = 0x80; mask; mask >>= 1) {
		if (mask & x)
			printf("1");
		else
			printf("0");
	}
}

void print32bits(unsigned long int x)
{
	for (unsigned long int mask = 0x80000000; mask; mask >>= 1) {
		if (mask & x)
			printf("1");
		else
			printf("0");
	}
}

void insert(set& A, char str[])
{
	int hash = (str[0] + str[2]) % 20;

	int g[20] = {6, -1, 0, 1, -1, 4, -1, -1, -1, -1, -1, 3, 2, -1, -1, -1, -1, -1, 7, 5};

	int index = g[hash];

	set mask = 0x80 >> index;

	A = A | mask;
}

unsigned long hash_slinger (char str[])
{ // cjb2 hashing algorithm
	unsigned long hash = 5281;
	int c;
	int magic_mod = 186; // After some testing, found to be the lowest modulus that
	                     // prevented collision.

	while ((c = *str++))\
	{
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}

	return (hash % magic_mod);
}

void tabler(int tbl[])
{
	tbl[104] = 0;
	tbl[77] = 1;
	tbl[154] = 2;
	tbl[127] = 3;
	tbl[95] = 4;
	tbl[36] = 5;
	tbl[101] = 6;
	tbl[137] = 7;
	tbl[21] = 8;
	tbl[86] = 9;
	tbl[110] = 10;
	tbl[177] = 11;
	tbl[44] = 12;
	tbl[138] = 13;
	tbl[89] = 14;
	tbl[34] = 15;
	tbl[25] = 16;
	tbl[4] = 17;
	tbl[31] = 18;
	tbl[10] = 19;
	tbl[70] = 20;
	tbl[72] = 21;
	tbl[91] = 22;
	tbl[131] = 23;
	tbl[45] = 24;
	tbl[123] = 25;
	tbl[79] = 26;
	tbl[54] = 27;
	tbl[169] = 28;
	tbl[60] = 29;
	tbl[98] = 30;
	tbl[157] = 31;
}

void insert(set32& A, char str[])
{
	int hash = hash_slinger(str);

	int g[186] = {-1};
	tabler(g);
	int index = g[hash];

	set32 mask = 0x80000000 >> index;

	A = A | mask;
}

int my_pow(int base, int  exp)
{
	int x = 1;
	for (int i = 0; i < exp; i++)
		x *= base;

	return x;
}

set Union(set A, set B)
{
	return (A | B);
}

set32 Union(set32 A, set32 B)
{
	return (A | B);
}

set Intersection(set A, set B)
{
	return (A & B);
}

set32 Intersection(set32 A, set32 B)
{
	return (A & B);
}

set Complement(set A)
{
	return ~A;
}

set32 Complement(set32 A)
{
	return ~A;
}

set Difference(set A, set B)
{
	return (A & (~B));
}

set32 Difference(set32 A, set32 B)
{
	return (A & (~B));
}

int Cardinality(set A)
{
	set mask = 0x01;
	unsigned int count = 0;

	while (mask) {
		if (A & mask) ++count;
		mask <<= 1;
	}

	return count;
}

int Cardinality(set32 A)
{
	set32 mask = 0x01;
	unsigned int count = 0;

	while (mask) {
		if (A & mask) ++count;
		mask <<= 1;
	}

	return count;
}

void printPowerSet(set A)
{
	int CardOfP = my_pow(2, Cardinality(A));
	set setB = 1;
	set subA = 0;

	for (; setB < CardOfP; ++setB)
	{
		unsigned char Amask = 0x01;
		unsigned char Bmask = 0x01;

		for (; Amask > 0; Amask <<= 1)
		{
			if (Amask & A)
			{
				if (Bmask & setB)
				{
					subA |= Amask;
				}
				Bmask <<= 1;
			}
			// Amask shifts left
		}
		printSet(subA);
		printf("\n");
		subA = 0;
	}
}

void printPowerSet(set32 A)
{
	int CardOfP = my_pow(2, Cardinality(A));
	set32 setB = 1;
	set32 subA = 0;

	for (; setB < CardOfP; ++setB)
	{
		unsigned long int Amask = 0x01;
		unsigned long int Bmask = 0x01;

		for (; Amask > 0; Amask <<= 1)
		{
			if (Amask & A)
			{
				if (Bmask & setB)
				{
					subA |= Amask;
				}
				Bmask <<= 1;
			}
			// Amask shifts left
		}
		printSet(subA);
		printf("\n");
		subA = 0;
	}
}

bool IsSubset(set ASubset, set ASet)
{
	return ((ASubset & ASet) == ASubset);
}

bool IsSubset(set32 ASubset, set32 ASet)
{
	return ((ASubset & ASet) == ASubset);
}

bool IsProperSubset(set ASubset, set ASet)
{
	return ((ASet != ASubset) && (ASubset != 0) && ((ASubset & ASet) == ASubset));
}

bool IsProperSubset(set32 ASubset, set32 ASet)
{
	return ((ASet != ASubset) && (ASubset != 0) && ((ASubset & ASet) == ASubset));
}

void test_operations(set A, set B, set C)
{
	set R = 0;

	printf("(A U B) ^ C: ");
	R = Intersection(Union(A, B), C);
	printSet(R);
	printf("\n\n");

	printf("A U (B ^ C): ");
	R = Union(A, Intersection(B, C));
	printSet(R);
	printf("\n\n");

	printf("~(A ^ B): ");
	R = Complement(Intersection(A, B));
	printSet(R);
	printf("\n\n");

	printf("(~A U ~B): ");
	R = Union(Complement(A), Complement(B));
	printSet(R);
	printf("\n\n");

	printf("A - B: ");
	R = Difference(A, B);
	printSet(R);
	printf("\n\n");

	printf("Powerset A: \n\n");
	printPowerSet(A);

	printf("\nA is a proper subset of B: ");
	IsProperSubset(A, B) ? printf("True\n\n") : printf("False\n\n");
	
	printf("A is a subset of B: ");
	IsSubset(A, B) ? printf("True\n\n") : printf("False\n\n");

	printf("(~C U A) ^ B: ");
	R = Intersection(Union(Complement(C), A), B);
	printSet(R);
	printf("\n\n");

	printf("(A ^ B) is a Proper Subset of B: ");
	IsProperSubset(Intersection(A, B), B) ? printf("True\n\n") : printf("False\n\n");
}

void test_operations(set32 A, set32 B, set32 C)
{
	set32 R = 0;

	printf("(A U B) ^ C: ");
	R = Intersection(Union(A, B), C);
	printSet(R);
	printf("\n\n");

	printf("A U (B ^ C): ");
	R = Union(A, Intersection(B, C));
	printSet(R);
	printf("\n\n");

	printf("~(A ^ B): ");
	R = Complement(Intersection(A, B));
	printSet(R);
	printf("\n\n");

	printf("(~A U ~B): ");
	R = Union(Complement(A), Complement(B));
	printSet(R);
	printf("\n\n");

	printf("A - B: ");
	R = Difference(A, B);
	printSet(R);
	printf("\n\n");

	printf("Powerset A: \n\n");
	printPowerSet(A);

	printf("\nA is a proper subset of B: ");
	IsProperSubset(A, B) ? printf("True\n\n") : printf("False\n\n");
	
	printf("A is a subset of B: ");
	IsSubset(A, B) ? printf("True\n\n") : printf("False\n\n");

	printf("(~C U A) ^ B: ");
	R = Intersection(Union(Complement(C), A), B);
	printSet(R);
	printf("\n\n");

	printf("(A ^ B) is a Proper Subset of B: ");
	IsProperSubset(Intersection(A, B), B) ? printf("True\n\n") : printf("False\n\n");
}
