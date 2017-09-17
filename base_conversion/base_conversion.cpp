#include <stdlib.h>
#include <stdio.h>
#include "./base_conversion.h"

const int MAX_BASE = 36;
const char char_lookup [MAX_BASE + 1] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '-'};

int my_pow(int base, int exp) {
	int x = 1;

	for (int i = 0; i < exp; i++) {
		x *= base;
	}

	return x;
}

long my_atoi(char* s, int base) {
	long i_number = 0;
	unsigned len = -1;
	bool is_negative = false;

	if (s[0] == '-') {
		is_negative = true;
		s = &s[1];
	}

	while (s[++len] != '\0');

	for (int i = (len - 1), j = 0; i >= 0; --i, ++j) {
		if (s[i] >= 48 && s[i] <= 57) { // if s[i] is between characters '0' and '9'
			i_number += (s[i] - 48) * my_pow(base, j);
		} else if (s[i] >= 65 && s[i] <= 90) { // if s[i] is between 'A' and 'Z'
			i_number += (s[i] - 55) * my_pow(base, j);
		} else {
			printf("Parsing Error: Bad Character: %c\n", s[i]);
			exit(1);
		}
	}

	return (is_negative ? i_number * -1 : i_number);
}

void my_itoa(long n, char* sOut, int base) {
	int values_in_reverse[100];
	int stepper = 0;
	bool is_negative = false;

	if (n < 0) is_negative = true, n *= -1;

	while (n) { // Mod/Div to pull out digits, they'll be stored in reverse order
		values_in_reverse[stepper++] = n % base;
		n /= base;
	}
	if (is_negative) values_in_reverse[++stepper] = 37;
	values_in_reverse[stepper] = '\0'; // Stepper now conveniently stores len

	for (int i = stepper -1 , j = 0; j < stepper; --i, ++j) {
		sOut[j] = char_lookup[values_in_reverse[i]];
	}
	sOut[stepper] = '\0';
}

int codontoi(char codon[4]) {
	int d0, d1, d2, value;

	switch (codon[2])
	{
		case 'C':
			d0 = 0; break;
		case 'T':
			d0 = 1; break;
		case 'A':
			d0 = 2; break;
		case 'G':
			d0 = 3; break;

	}

	switch (codon[1])
	{
		case 'C':
			d1 = 0; break;
		case 'T':
			d1 = 1; break;
		case 'A':
			d1 = 2; break;
		case 'G':
			d1 = 3; break;

	}

	switch (codon[0])
	{
		case 'C':
			d2 = 0; break;
		case 'T':
			d2 = 1; break;
		case 'A':
			d2 = 2; break;
		case 'G':
			d2 = 3; break;

	}

	//the base 4 value of the codon
	value = d2 * 16 + d1 * 4 + d0;

	return value;
}

void itocodon(char codon[4], int i) {
	char codon_table[4] = {'C', 'T', 'A', 'G'};
	for (int i = 0; i < 4; ++i) codon[i] = 'C';
	
	if (i >= 64) {
		printf("Value too large to store in single codon. Exiting");
		exit(1);
	}

	for (int x = 3; x >= 0; --x) {
		codon[x] = codon_table[i % 4];
		i /= 4;
	}
}

void add_in_base(char* s1, char* s2, char* sum, int base) {
	long x, y, z;

	x = my_atoi(s1, base);
	y = my_atoi(s2, base);
	z = x + y;
	my_itoa(z, sum, base);
}
