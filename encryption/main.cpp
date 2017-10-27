#include <string.h>
#include <iostream>
#include "encryptor.h"
#include "decryptor.h"

int main (int argc, char* argv[])
{
	fill_fi();
	char selection;
	std::ifstream infile;
	std::ofstream outfile;
	std::string filename;
	char key = 0;

	if (argc == 3 && strcmp(argv[1], "-f") == 0) {
		filename = argv[2];
		infile.open(filename, std::ios_base::binary);
		if (!infile)
			std::cout << "Invalid filename!\n", exit(1);
		outfile.open("cracked.bmp", std::ios_base::binary);
		decrypt_without_key (infile, outfile);
	} else {

		std::cout
			<< "*** miniDES encryption ***\n"
			<< "	e) Encrypt file\n"
			<< "	d) Decrypt file\n"
			<< "	u) Decrypt file with unknown key"
			<< "\nPlease make a selection: ";
		std::cin >> selection;
		std::cout << std::endl;

		switch (selection) {
			case ('e') :
				std::cout
					<< "You've selected 'encrypt file'\n"
					<< "Please input the filename: ";
				std::cin >> filename;
				std::cout << std::endl << "Please input the encryption key: ";
				std::cin >> key;
				std::cout << std::endl;
				infile.open (filename, std::ios_base::binary);
				if (!infile)
					std::cerr << "Input could not be opened\n";
				outfile.open ("encrypted.bmp", std::ios_base::binary);
				encrypt_file (infile, outfile, key);
				infile.close();
				outfile.close();
				break;

			case ('d') :
				std::cout
					<< "You've selected 'decrypt file'\n"
					<< "Please input the filename: ";
				std::cin >> filename;
				std::cout << std::endl << "Please input the encryption key: ";
				std::cin >> key;
				std::cout << std::endl;
				infile.open (filename, std::ios_base::binary);
				if (!infile)
					std::cerr << "Input could not be opened\n";
				outfile.open ("decrypted.bmp", std::ios_base::binary);
				decrypt_file (infile, outfile, key);
				infile.close();
				outfile.close();
				break;

			case ('u') :
				std::cout
					<< "You've selected 'decrypt file with unknown key'\n"
					<< "Please input the filename: ";
				std::cin >> filename;
				infile.open (filename, std::ios_base::binary);
				if (!infile)
					std::cerr << "Input could not be opened\n";
				outfile.open ("cracked.bmp", std::ios_base::binary);
				decrypt_without_key (infile, outfile);
				infile.close();
				outfile.close();
				break;

			default:
				std::cout << "Inavlid entry\n", exit(1);
		}
	}
}
