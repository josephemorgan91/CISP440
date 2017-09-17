#include <iostream>

const int MAX_BASE = 36;
char char_lookup [MAX_BASE];

void fill_lookup();

int main() {
	fill_lookup();
	std::cout << "{\'"<< char_lookup[0] << "\', \'";
	for (int i = 1; i < 35; i++) {
		std::cout << char_lookup[i] << "\', \'";
	}	
	std::cout << char_lookup[35] << "\'}" << std::endl;
}

void fill_lookup() {
	for (int i = 0; i < 10; ++i) {
		char_lookup[i] = (i + 48);
	}

	for (int i = 10; i <= 35; ++i) {
		char_lookup[i] = (i + 55);
	}
}
