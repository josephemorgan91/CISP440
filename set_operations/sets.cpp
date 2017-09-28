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

bool IsSubset(set ASubset, set ASet)
{
	return ((ASubset & ASet) == ASubset);
}

bool IsProperSubset(set ASubset, set ASet)
{
	return ((ASet != ASubset) && (ASubset != 0) && ((ASubset & ASet) == ASubset));
}

void test_operations(set A, set B, set C)
{
	set R = 0;

	printf("(A U B) ^ C: ");
	R = Intersection(Union(A, B), C);
	printSet(R);
	printf("\n");

	printf("A U (B ^ C): ");
	R = Union(A, Intersection(B, C));
	printSet(R);
	printf("\n");

	printf("~(A ^ B): ");
	R = Complement(Intersection(A, B));
	printSet(R);
	printf("\n");

	printf("(~A U ~B): ");
	R = Union(Complement(A), Complement(B));
	printSet(R);
	printf("\n");

	printf("A - B: ");
	R = Difference(A, B);
	printSet(R);
	printf("\n");

	printf("Powerset A: \n");
	printPowerSet(A);

	printf("A is a proper subset of B: ");
	IsProperSubset(A, B) ? printf("True\n") : printf("False\n");
	
	printf("A is a subset of B: ");
	IsSubset(A, B) ? printf("True\n") : printf("False\n");

	printf("(~C U A) ^ B: ");
	R = Intersection(Union(Complement(C), A), B);
	printSet(R);
	printf("\n");

	printf("(A ^ B) is a Proper Subset of B: ");
	IsProperSubset(Intersection(A, B), B) ? printf("True\n") : printf("False\n");
}

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
}
