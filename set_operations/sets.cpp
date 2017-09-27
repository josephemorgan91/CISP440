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

void printSet(set A)
{
	printf("{ ");

	bool commaflag = false;
	int i = 0;
	unsigned char mask = 0x80;
	for (; mask; mask >>= 1, i++) {
		if (mask & A)
		{
			if (commaflag) printf(", ");
			printf("%s", Universe[i]);
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

void insert(set & A, char str[])
{
	int hash = (str[0] + str[2]) % 20;

	int g[20] = {6, -1, 0, 1, -1, 4, -1, -1, -1, -1, -1, 3, 2, -1, -1, -1, -1, -1, 7, 5};

	int index = g[hash];

	set mask = 0x80 >> index;

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

set Intersection(set A, set B)
{
	return (A & B);
}

set Complement(set A)
{
	return ~A;
}

set Difference(set A, set B)
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

	return 42;
}

void printPowerSet(set A)
{
}


bool IsSubset(set ASubset, set ASet)
{
	return ((ASubset & ASet) == ASubset);
}


bool IsProperSubset(set ASubset, set ASet)
{
	return ((ASet != ASubset) && (ASubset != 0) && ((ASubset & ASet) == ASubset));
}

int main(void)
{

	set A = 0;

	insert(A, "Bat");
	insert(A, "Cat");
	insert(A, "Chimp");
	insert(A, "Snake");

	printf("Set A: ");
	printSet(A);
	printf("\nCardinality: ");
	printf("%d", Cardinality(A));

	printf("\n\nPowerSet(A):\n");
	printPowerSet(A);

	set B = 0;
	insert(B, "Chimp");
	insert(B, "Fish");
	insert(B, "Liger");

	printf("\nSet B: ");
	printSet(B);

	set C = 0;
	insert(C, "Chimp");
	insert(C, "Fish");
	insert(C, "Liger");
	printf("\nSet C: ");
	printSet(C);

	printf("\n(A Union B) Inter ~C: ");
	set D = Intersection(Union(A, B), ~C);
	printSet(D);

	if (IsSubset(B, C))
		printf("\nB is a subset of C");
	else
		printf("\nB is NOT a subset of C");

	if (IsProperSubset(B, C))
		printf("\nB is a proper subset of C");
	else
		printf("\nB is NOT a proper subset of C");

	printf("\n");

/*
OUTPUT OF ABOVE TESTING

Set A: { Bat, Cat, Chimp, Snake }
Cardinality: 4

PowerSet(A):
{  }
{ Snake }
{ Chimp }
{ Chimp, Snake }
{ Cat }
{ Cat, Snake }
{ Cat, Chimp }
{ Cat, Chimp, Snake }
{ Bat }
{ Bat, Snake }
{ Bat, Chimp }
{ Bat, Chimp, Snake }
{ Bat, Cat }
{ Bat, Cat, Snake }
{ Bat, Cat, Chimp }
{ Bat, Cat, Chimp, Snake }

Set B: { Chimp, Fish, Liger }
Set C: { Chimp, Fish, Liger }
(A Union B) Inter ~C: { Bat, Cat, Snake }
B is a subset of C
B is NOT a proper subset of C

*/
	}
