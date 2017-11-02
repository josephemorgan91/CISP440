#include "encryptor.h"
#include "inverse_table.h"

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
