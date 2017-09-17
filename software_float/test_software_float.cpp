#include <cstdio>
#include "./float_software.h"

void get_number(char*);
void test_atof(char*);
void test_ftoa(char*);
void test_add(char*);
void test_multiply(char*);

const int INPUT_BUFFER_SIZE = 40;

int main() {
	char user_input[INPUT_BUFFER_SIZE];
	int selection;
	bool exit = false;
	char trash;

	printf(
			"\n\n**** Joseph Morgan's test main for software implementation of floats ****\n\n"
			);
	get_number(user_input);

	while (!exit) {
		printf(
				"Menu options:\n\n"
				"     1 - test atof\n"
				"     2 - test ftoa\n"
				"     3 - test add\n"
				"     4 - test multiply\n"
				"     5 - input new number\n"
				"     0 - exit\n\n"
				"Selection: "
				);

		while ((trash = getchar()) != '\n' && trash != EOF)
			/* discard */;

		scanf("%i", &selection);
		printf("\n");
		switch (selection) {
			case 0 :
				exit = true;
				break;

			case 1 :
				test_atof(user_input);
				break;

			case 2 :
				test_ftoa(user_input);
				break;

			case 3 :
				test_add(user_input);
				break;

			case 4 :
				test_multiply(user_input);
				break;

			case 5 :
				get_number(user_input);
				break;

			default :
				printf("That didn't seem like an acceptable option\n");
		}
	}
}

void get_number(char* user_input) {
	printf("Please enter a number to use in the test: ");
	scanf("%s", user_input);
	printf("\n");
}

void test_atof(char* user_input) {
	unsigned char f = software_atof(user_input);

	printf("Converting %s to floating-point format...\n\n", user_input);

	printf("* * * * * * * * * * * * * * * * *\n\n");
	print8bits(f);
	printf("\n* * * * * * * * * * * * * * * * *\n\n");
}

void test_ftoa(char* user_input) {
	printf(
			"This will show the exact value of your number as it's stored in memory in floating point format\n"
			"You can see how accurately your number is being represented in 8 bits!\n\n"
			"Converting %s to floating-point and back to a string...\n\n", user_input
			);

	unsigned char f = software_atof(user_input);
	char buffer[INPUT_BUFFER_SIZE];
	software_ftoa(f, buffer);

	printf("* * * * * * * * * * * * * * * * *\n\n");
	printf("%s\n\n", buffer);
	printf("* * * * * * * * * * * * * * * * *\n\n");
}

void test_add(char* user_input) {
	char second_input[INPUT_BUFFER_SIZE];
	unsigned char first_number;
	unsigned char second_number;
	unsigned char sum;
	char str_sum[INPUT_BUFFER_SIZE];;

	printf("What would you like to add to your number?\n");
	get_number(second_input);

	printf("\n"
			"* * * * * * * * * * * * * * * * *\n\n");
	first_number = software_atof(user_input);
	second_number = software_atof(second_input);

	printf("First Number:   %s\n", user_input);
	printf("Second Number:  %s\n", second_input);

	sum = software_float_add(first_number, second_number);
	software_ftoa(sum, str_sum);

	printf("\n* * * * * * * * * * * * * * * * *\n\n");
	printf("Sum: %s\n\n", str_sum);
	printf("* * * * * * * * * * * * * * * * *\n\n");
}

void test_multiply(char* user_input) {
	char second_input[INPUT_BUFFER_SIZE];
	unsigned char first_number;
	unsigned char second_number;
	unsigned char product;
	char str_sum[INPUT_BUFFER_SIZE];;

	printf("What would you like to multiply with your number?\n");
	get_number(second_input);

	printf("\n"
			"* * * * * * * * * * * * * * * * *\n\n");
	first_number = software_atof(user_input);
	second_number = software_atof(second_input);

	printf("First Number:   %s\n", user_input);
	printf("Second Number:  %s\n", second_input);

	product = software_float_multiply(first_number, second_number);
	software_ftoa(product, str_sum);

	printf("\n* * * * * * * * * * * * * * * * *\n\n");
	printf("Sum: %s\n\n", str_sum);
	printf("* * * * * * * * * * * * * * * * *\n\n");
}
