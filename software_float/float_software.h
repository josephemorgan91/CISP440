#ifndef H_FLOAT_SOFTWARE
#define H_FLOAT_SOFTWARE

unsigned char software_atof (char*);
void software_ftoa (unsigned char, char*);
void print_all_in_range();
void print8bits(unsigned char);
void print16bits(unsigned short);
void print32bits(unsigned long);
unsigned char software_float_add (unsigned char, unsigned char);
unsigned char software_float_multiply (unsigned char, unsigned char);
int software_float_pow (int base, int exp);

#endif
