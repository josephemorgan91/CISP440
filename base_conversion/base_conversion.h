#ifndef H_BASE_CONVERSION
#define H_BASE_CONVERSION

int my_pow(int, int);
long my_atoi(char*, int);
void my_itoa(long, char*, int);
int codontoi(char*);
void itocodon(char*, int);
void add_in_base(char*, char*, char*, int);

const unsigned char MAX_INPUT_LENGTH = 255;
#endif
