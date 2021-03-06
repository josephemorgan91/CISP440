#ifndef _DECRYPTOR_H_
#define _DECRYPTOR_H_

#include <fstream>

unsigned char decrypt (unsigned char w, unsigned char key);
void decrypt_file (std::ifstream &infile, std::ofstream &outfile, unsigned char key);
void decrypt_without_key (std::ifstream &infile, std::ofstream &outfile);

#endif
