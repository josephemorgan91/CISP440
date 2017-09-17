CC = clang
CFLAGS = -g -Wall -pedantic

test_software_float.out: float_software.o test_software_float.o float_software.h
	$(CC) $(CFLAGS) float_software.o test_software_float.o -o test_software_float.out

float_software.o: float_software.cpp float_software.h
	$(CC) $(CFLAGS) float_software.cpp -c

test_software_float.o: test_software_float.cpp float_software.h
	$(CC) $(CFLAGS) test_software_float.cpp -c
