#include <climits>
#include <iostream>
#include "decryptor.h"
#include "encryptor.h"

void fill_fi()
{
	unsigned char temp;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 256; ++j) {
			temp = f[i][j];
			fi[i][temp] = j;
		}
	}
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
