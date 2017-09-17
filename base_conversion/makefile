CC = clang
CFLAGS = -g -Wall -pedantic -std=c++98

base_conversion_test.out: base_conversion_test.o base_conversion.o base_conversion.h
	$(CC) $(CFLAGS) base_conversion.o base_conversion_test.o -o base_conversion_test.out

base_conversion_test.o: base_conversion_test.cpp base_conversion.h
	$(CC) $(CFLAGS) base_conversion_test.cpp -c

base_conversion.o: base_conversion.cpp base_conversion.h
	$(CC) $(CFLAGS) base_conversion.cpp -c
