#include <stdio.h>
#include "./base_conversion.h"

void test_my_atoi();
void test_my_itoa();
void test_itocodon();
void test_add_in_base();

char* alpha_values[6] = {"14", "FA", "63", "2G", "Z9R", "72"};
const int int_values[6] = {210, 87, 714, 93, 34, 218};
const int bases[6] = {25, 16, 29, 20, 36, 18};

int main() {
	test_my_atoi();
	test_my_itoa();
	test_itocodon();
	test_add_in_base();
}

void test_my_atoi() {
	long result;

	printf("Testing my_atoi(): \n");
	for (int i = 0; i < 6; ++i) {
		result = my_atoi(alpha_values[i], bases[i]);
		printf("Converting %s in base %i to base 10: %li\n", alpha_values[i], bases[i], result);
	}
}

void test_my_itoa() {
	char result[MAX_INPUT_LENGTH];

	printf("\n\nTesting my_itoa():\n");
	for (int i = 0; i < 6; ++i) {
		my_itoa(int_values[i], result, bases[i]);
		printf("Converting %i in base 10 to base %i: %s\n", int_values[i], bases[i], result);
	}
}

void test_itocodon() {
	char codon[4];

	printf("\n\nTesting itocodon(): \n");
	for (int i = 0; i < 6; ++i) {
		itocodon(codon, (int_values[i] % 64));
		printf("Converting %i to a DNA Codon: %s\n", (int_values[i] % 64), codon);
	}
}

void test_add_in_base() {
	char sum[MAX_INPUT_LENGTH];

	printf("\n\nTesting add_in_base(): \n");
	for (int i = 0; i <= 5; i += 2) {
		add_in_base(alpha_values[i], alpha_values[i+1], sum, bases[i]);
		printf("Adding %s and %s in base %i: %s\n", alpha_values[i], alpha_values[i+1], bases[i], sum);
	}
}
