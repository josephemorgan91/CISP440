#include <fstream>
#include "encryptor.h"

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
