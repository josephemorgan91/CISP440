#include <iomanip>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <climits>

unsigned char f[4][256] = {
	// 0    1    2    3    4    5    6    7    8    9   10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   25   26   27   28   29   30   31
	{  1,  18, 121,  32, 127, 137, 132, 136, 144, 152, 159, 167, 175, 176, 178,   6, 149, 179, 186, 112,  59,  64,  12,   9,  81,  41,  29,  16,  10,   5,   0,  31,     //f[0]
		76, 115, 165, 168,  74, 105,  48, 124, 172,  51, 182, 195,  63, 123,  38, 200, 205, 210,  28,  53, 212, 215, 217, 220, 109,  72,  99, 148, 158, 222, 229, 230,
		57,  90, 104,  55,   8, 131, 169,  87, 180, 189, 213, 214, 194,  85, 133, 187,  73,  58,  66,  54, 141,  86,  15,  60,  82, 142,  47, 111, 157,  19,  36, 163,
		166, 184,  71, 199, 201, 100,  39,  40,  95, 101, 139, 155,  62,  33, 177, 202,  25, 216, 223, 150, 227, 232, 235, 237, 238,  43, 240, 241,   2, 183, 122, 236,
		24, 130, 161, 171,  23,  69, 181,  44, 190, 174, 219,  49,  75, 135, 208, 225, 234, 242, 243, 244,  67,  65, 146, 245, 239,  98,   7, 147, 120, 203, 207, 145,
		80, 221, 160, 107,  61,  22,  92, 143, 193,  35, 185, 196, 204, 224, 231, 246, 248, 249, 250,  52, 251, 192, 197, 103, 119,  37,  77,  21, 129, 151, 170, 191,
		198, 206, 209, 102,  11, 153,  88, 164, 226, 228, 116, 134, 233, 253, 126, 162,  42,   3, 138, 154,  78, 218, 247, 252, 211, 254,  96,  68, 110,  83, 125,  34,
		128,  97, 106, 255, 156,   4,  26,  27,  30, 108,  56,  13,  93, 140,  17,  45, 173,  50, 118, 188,  91, 114,  46,  84,  89,  20,  14,  79,  94,  70, 113, 117},

	{ 112, 103, 224, 128, 140, 156,  60, 219,  25,  44, 213, 180, 187, 171, 169, 197, 228, 221, 236,  84, 164, 117, 225,  71,   1,  85,  27,  87,  99, 249, 118, 250,     //f[1]
		214, 106, 239,  57,  92,  20, 138, 148, 181,  21, 185,  46, 226, 159, 240, 251,   2, 166, 252,  82, 253, 254,  65,   4, 105,  39, 177, 231, 255,  12,  64, 170,
		53,  36, 182,  26,  22,  42,   9,  54, 119, 137, 124,  37, 155,  31,  86,  35, 107, 186, 216, 101,  33,  69, 116, 136, 134,  30,  49, 142, 143, 160, 179, 193,
		220, 235, 176, 131,   0,  61,  47,  81, 108, 233,  18,  11,  28,  45,  95,  98, 162, 174, 175, 125,  67, 120, 194, 102, 201, 211,   8,  38,  62, 158, 163, 237,
		3,  79, 150, 205, 238,  58, 241,  68, 178,  40,  14, 114, 123, 129, 144, 195, 203, 243, 100, 199,  76, 157,  50, 167,  24, 208, 212, 196, 217, 121,  41,  59,
		115, 135, 127, 149, 184, 190,  29,  97, 189, 215,  90, 133,  83,  72, 244, 248,  94, 152,  23,  89, 139, 191, 200,  32,  91, 202, 227,  48, 209,  75,  80,   7,
		154, 210, 126, 141, 232,  70, 218, 165, 198,  55, 110, 147,   5,   6,  51, 153, 173, 204, 161, 206,  43, 207, 188,  19, 223, 234,  10,  63,  52,  66,  34,  93,
		130, 242,  88, 183,  13, 146, 230, 229,  17, 132, 168, 245, 246, 145, 111,  74,  16,  56, 104, 247, 109, 113,  73, 192, 222,  77, 172,  15, 122, 151,  78,  96},

	{  71,  68,  46, 109, 126, 147, 179,  62, 183, 195, 213,  67,  83, 191,  11,  37, 118, 193, 216,  14, 186,  73, 101, 114, 140, 142, 231,   0, 205, 232,  12,  40,     //f[2]
		123,  32, 137,  23,  25,  38, 132, 143,  27, 107, 121,  94, 203,  82, 131, 163, 196, 206, 149, 218,  50,  72,  81, 146, 111, 100, 219, 110,  75, 127,  44, 182,
		155,  48,  76, 189,  79, 210,  56, 116, 164, 198,  20, 209, 214, 113, 138,   1, 220, 221,  34, 158, 225, 229,  86,  98, 234,   3,  42, 236, 237, 238, 241, 243,
		16,  57,   9,   8,  28,  33,  13,   7,  80,  96, 103, 159,  17, 228, 150, 177, 184, 212, 239, 141, 244, 144,  90,  78, 171, 106, 152,  55, 176,  85, 122,  10,
		54, 102,  26,  60, 139, 148, 153,  53,   4,  65,  84, 161, 169,  49, 187,  58, 222, 224, 226, 130, 136,  43, 245, 207,  35, 157, 246, 248, 105,  21, 249, 250,
		251, 252, 253, 133,  41,  47,   6, 247, 254, 240, 128, 162,  63,  97, 173,  66,  15, 104,  69, 108, 119,  52, 129, 167, 170, 115,  59, 175, 180, 185, 145,  89,
		135, 181,  22, 165, 112,   5, 124, 160,  87, 192, 200,  92, 201, 215,  30, 217,  51, 174, 223, 230,  70, 233, 227, 235, 178, 197,  99, 204, 242,  19, 255,  93,
		64,  29,  18,  39,  95,  45, 151, 188, 190, 117, 194,  74, 199,  88, 168, 202, 125, 154, 208,  36, 134, 166,  77,  31, 156, 172,   2, 211, 120,  61,  24,  91},

	{ 224, 102, 161,  74, 213, 234, 212,  69, 246,  30,  64, 107,  66,  81,  82, 123,  76, 132, 112, 136, 105, 129, 194, 151, 215,  40, 120,  49,  83, 148, 100, 131,    //f[3]
		15,  65,  43, 134, 174, 189, 216, 138, 220, 214, 223, 225, 142,  71, 205,  48, 217, 227,  34,  12, 169,  17, 179, 237, 238, 218,   3,  16,  41,  61, 109,  45,
		198, 239, 119,  92,  25, 230, 243, 244, 247, 248, 249, 250, 150, 253,  58, 236,   8,  94, 121, 167, 251,  52,  44,  97,  21,  36,   5,  42, 114,  32,  95, 166,
		196, 201, 219,  26, 101,  57,  37, 140,  46,   7, 125,  77, 153, 171, 187, 203, 204,  56,  70, 207,  67, 115, 135, 173,  90, 195, 197, 209, 210, 211, 192, 221,
		226, 157, 162,  20,  96, 147, 199,  98, 126,  80, 178, 182, 228, 103, 229, 128, 156,  13, 144,  23,  51, 139, 172, 183,  63, 110, 202, 208, 231,  35, 235, 155,
		241, 252,  27, 254, 255,  68, 133,   9,  62,   1,  99,  87, 108, 130, 137,  54,  84, 149,   0, 104, 113,  93, 127, 145,  79, 154,  14, 164,  22, 143, 170, 177,
		180, 181, 163, 186,  60, 124, 191, 193, 190,  33,  53, 175,  91, 240, 117, 242, 245, 176, 185,  29,  73, 152, 233,  18, 111, 116, 146,  75,  78,  89, 141, 158,
		168, 200, 222,  50,  85,  88, 184,  86,  55, 232, 122,   6,  10,  38,   4,  39, 106, 118,   2,  19,  47, 160,  59,  24,  11,  31,  72, 165, 188, 206,  28, 159}
};

unsigned char fi[4][256];

void fill_fi()
{
	unsigned char temp;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 256; ++j) {
			temp = f[i][j];
			fi[i][temp] = j;
		}
	}

	// for (int i = 0; i < 4; ++i) {
	//   for (int j = 0; j < 256; ++j) {
	//     std::cout << (int)fi[i][j] << " ";
	//   }
	//   std::cout << std::endl;
	// }
}

unsigned char swapbytes(unsigned char cIn)
{
	unsigned char lownibble, highnibble, cOut = 0;

	lownibble = cIn & 0x0F;
	highnibble = cIn & 0xF0;

	cOut = highnibble >> 4;
	cOut = cOut | (lownibble << 4);

	return cOut;
}

unsigned char encrypt (unsigned char w, unsigned char key)
{
	unsigned char x0, y0, z0;
	unsigned char x1, y1, z1;
	unsigned char x2, y2, z2;
	unsigned char x3, y3, z3;

	unsigned char p, q, r, s;
	p = (key & 0x03);
	q = (key & 0x0C) >> 2;
	r = (key & 0x30) >> 4;
	s = (key & 0xC0) >> 6;

	x0 = f[s][w];
	y0 = swapbytes(x0);
	z0 = y0 ^ key;

	// Stage 1
	x1 = f[r][z0];
	y1 = swapbytes(x1);
	z1 = y1 ^ key;

	// Stage 2
	x2 = f[q][z1];
	y2 = swapbytes(x2);
	z2 = y2 ^ key;

	// Stage 3
	x3 = f[p][z2];
	y3 = swapbytes(x3);
	z3 = y3 ^ key;

	return z3;
}

unsigned char decrypt (unsigned char w, unsigned char key)
{
	unsigned char o_char = 0;
	unsigned char x0, y0, z0 = 0;
	unsigned char x1, y1, z1 = 0;
	unsigned char x2, y2, z2 = 0;
	unsigned char x3, y3 = 0;
	unsigned char p, q, r, s = 0;

	p = (key & 0x03);
	q = (key & 0x0C) >> 2;
	r = (key & 0x30) >> 4;
	s = (key & 0xC0) >> 6;

	y3 = w ^ key;
	x3 = swapbytes (y3);
	z2 = fi[p][x3];

	y2 = z2 ^ key;
	x2 = swapbytes (y2);
	z1 = fi[q][x2];

	y1 = z1 ^ key;
	x1 = swapbytes (y1);
	z0 = fi[r][x1];

	y0 = z0 ^ key;
	x0 = swapbytes (y0);
	o_char = fi[s][x0];

	return o_char;
}

void encrypt_file (std::ifstream &infile, std::ofstream &outfile, unsigned char key)
{
	char c;
	while (!infile.eof())
	{
		infile.read(&c, 1);
		if (!infile.eof())
		{
			c = encrypt(c, key);
			outfile.write(&c, 1);
		}
	}

}

void decrypt_file (std::ifstream &infile, std::ofstream &outfile, unsigned char key)
{
	char c;
	while (!infile.eof())
	{
		infile.read(&c, 1);
		if (!infile.eof())
		{
			c = decrypt(c, key);
			outfile.write(&c, 1);
		}
	}
}

void decrypt_without_key (std::ifstream &infile, std::ofstream &outfile)
{
	short key;
	char *c = (char*)malloc(2 * sizeof(char));
	char *d = (char*)malloc(2 * sizeof(char));
	infile.read (c, 2);
	for (key = 0; key <= UCHAR_MAX; ++key) {
		d[0] = decrypt (c[0], key);
		d[1] = decrypt (c[1], key);
		if (d[0] == 'B' && d[1] == 'M') {
			std::cout << "Key found as: " << (char)key << std::endl;
			break;
		}
	}
	if (key > UCHAR_MAX) {
		std::cout << "Key could not be found\n";
		exit(1);
	} else {
		infile.seekg(0, infile.beg);
		decrypt_file (infile, outfile, key);
	}
}

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
