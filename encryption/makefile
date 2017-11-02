CC = clang++
CFLAGS = -std=c++11 -Wall -pedantic

jcrypt.bin: decryptor.o encryptor.o inverse_table.o main.o
	$(CC) $(CFLAGS) decryptor.o encryptor.o main.o inverse_table.o -o jcrypt.bin

main.o: main.cpp encryptor.h decryptor.h
	$(CC) $(CFLAGS) main.cpp -c

decryptor.o: decryptor.h encryptor.h decryptor.cpp
	$(CC) $(CFLAGS) decryptor.cpp -c

encryptor.o: encryptor.h encryptor.cpp
	$(CC) $(CFLAGS) encryptor.cpp -c

inverse_table.o: encryptor.o inverse_table.h inverse_table.cpp
	$(CC) $(CFLAGS) inverse_table.cpp -c

clean:
	rm ./*.o
