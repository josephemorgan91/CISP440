#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

unsigned long hash_slinger(const char*);
bool is_hash_table_big_enough_for_the_both_of_us(std::vector<std::string>, int array_size = 32);

const char* uinit[] = {
	"Bat", "Cat", "Chimp", "Dog", "Fish", "Liger", "Snake", "Turtle",
	"Bear", "Dragon", "Horse", "Wolf", "Rat", "Gerbil", "Rabbit", "Monkey",
	"Donkey", "Llama", "Zebra", "Hippopotamus", "Rhiceros", "Gecko", "Frog", "Sloth",
	"Deer", "Kangaroo", "Gorilla", "Alligator", "Panda", "Squirrel", "Duck", "Platypus" };

int main() {
	// char* str = (char*)malloc(sizeof(char) * 256);
	// unsigned long hash;
	std::vector<std::string> BigUniverse(uinit, uinit + 32);

	is_hash_table_big_enough_for_the_both_of_us(BigUniverse);

}

unsigned long hash_slinger (const char* str) {
	unsigned long hash = 5281;
	int c;

	while ((c = *str++)) {
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}

	return hash;
}

bool is_hash_table_big_enough_for_the_both_of_us (std::vector<std::string> str, int array_size) {
	unsigned long hash_table[array_size];
	bool result = true;
	bool duped = true;
	int magic_number = 32;

	while (duped == true) {
		duped = false;
		for (int i = 0; i < array_size; ++i) {
			hash_table[i] = hash_slinger(str[i].c_str()) % magic_number;
			printf("%li ", hash_table[i]);
		}
		printf("\n");

		// Check for dupes
		// No one likes getting duped
		unsigned long hash_to_check;
		for (int i = 0; i < array_size; ++i) {
			hash_to_check = hash_table[i];
			for (int j = 0; j < array_size; ++j) {
				if (j != i) {
					if (hash_to_check == hash_table[j]) {
						result = false;
						printf("Y'all been duped: %li\n", hash_table[j]);
						duped = true;
						magic_number++;
						break;
					}
				}
			}
		}
	}
	printf("Magic Number: %i\n", magic_number);
	return result;
}
