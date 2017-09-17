#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "float_software.h"

unsigned char software_atof (char* input_str) {
	char formatted_str[20];
	bool negative = false;

	// Set negative flag
	if (input_str[0] == '-') {
		negative = true;
		strcpy(formatted_str, input_str + 1);
	} else {
		strcpy(formatted_str, input_str);
	}

	int len = strlen(formatted_str);

	// Variables to hold string representation of whole and fractional parts
	// of the number.
#	define S_WHOLE_SIZE 3
#	define S_FRACT_SIZE 9
	char string_whole[S_WHOLE_SIZE] = "00";
	char string_fract[S_FRACT_SIZE] = "00000000";

	// Store the index of the decimal in x
	int x = 0;
	while (formatted_str[x] != '.') {
		++x;
		if (x > len) printf("You need to include a decimal point - exiting\n"), exit(1);
	}

	// Reverse whole part of number, store as string.
	// ex. 3.1416 would be stored as: 30
	for (int i = x - 1, j = 0; i >= 0; --i, ++j) {
		string_whole[j] = formatted_str[i];
	}

	// Reverse fractional part of number, store as string.
	// ex: 3.1416 would be stored as: 00006141
	for (int i = x + 1, j = S_FRACT_SIZE - 2; i < len; ++i, --j) {
		string_fract[j] = formatted_str[i];
	}

	// Convert string representation of whole part to internal representation of
	// the integer.
	unsigned char integer_whole = 0;
	for (int i = 0; i < S_WHOLE_SIZE - 1; ++i) {
		integer_whole += (string_whole[i] - '0') * software_float_pow(10, i);
	}

	// Convert string representation of fractional part to binary representation
	// of the number times 100,000,000 in decimal
	unsigned long integer_fract = 0;
	for (int i = 0; i < S_FRACT_SIZE - 1; ++i) {
		integer_fract += (string_fract[i] - '0') * software_float_pow(10, i);
	}

	// This is some wacky voodoo magic. To manually find the bits needed to
	// represent the fractional point of a decimal number, we subtract by known
	// powers of two if the fractional part is greater than the known power of two.
	// Our integer_fract contains (fractional part of the integer * 1,000,000), which
	// means we can subtract by (known powers of two * 1,000,000) to find which
	// known powers of two it contains. Then mask off those specific bits.
	unsigned long power_of_two = 50000000;
	unsigned char binary_fract = 0; // Bits to the right of decimal point.
	unsigned char mask = 0x80; // initial bit to potentially mask.

	for (int i = 0; i < S_FRACT_SIZE - 1; ++i) {
		if (integer_fract >= power_of_two) {
			binary_fract |= mask;
			integer_fract -= power_of_two;
		}

		mask >>= 1;
		power_of_two >>= 1; // This is the same as multiplying by .5, ignoring remainder
	}

	//print8bits(integer_whole);
	//print8bits(binary_fract);

	unsigned short buffer = 0;
	buffer = integer_whole;
	buffer <<= 8;
	buffer |= binary_fract;

	//print16bits(buffer);

	// Normalize the fraction - find the first 1.
	int exponent = 7;
	unsigned short bitfinder_mask = 0x8000;
	while (!(buffer & bitfinder_mask)) {
		--exponent;
		bitfinder_mask >>= 1;
	}

	// Final packing of the float
	unsigned char the_float = 0;

	buffer <<= (7 - exponent);
	buffer >>= 8;
	the_float = buffer;
	the_float &= 0x78;
	exponent += 4;
	the_float |= exponent;
	if (negative) the_float |= 0x80;

	return the_float;
}

void software_ftoa (unsigned char f, char* strOut) { // This function copy/pasted from assignment
	int ch_p = 0;	// pointer to string chars

	if(f & 0x80) strOut[ch_p++] = '-';		// is it negative

	int exponent;
	exponent = (f & 0x07) - 4;				// get the exponent
	f &= 0x78;								// mask off everything except mantissa
	f |= 0x80;								// put on the leading 1

	//print8bits(f);	

	// now pack the normalized bits to a 'bit field' so
	// so we can de-normalize it
	unsigned short buffer = 0;
	buffer = f;
	buffer <<= 8;							// scoot into high byte
	buffer >>= (7 - exponent);				// de-normalize

	//print16bits(buffer);	 

	// get the whole part
	unsigned char i_whole;					// bits to left of decimal
	i_whole = (buffer & 0xFF00) >> 8;

	// get the fractional part
	unsigned char b_fract;					// bits to right of decimal
	b_fract = (buffer & 0x00FF);

	// add up the bit values in the mantissa using INTEGERS only
	// we are adding up negative powers of 2 scaled by 100,000,000 decimal
	// NOTE:  Could easily loopify this...
	unsigned long i_fract = 0;
	if(b_fract & 0x80) i_fract += 50000000;
	if(b_fract & 0x40) i_fract += 25000000;
	if(b_fract & 0x20) i_fract += 12500000;
	if(b_fract & 0x10) i_fract +=  6250000;
	if(b_fract & 0x08) i_fract +=  3125000;
	if(b_fract & 0x04) i_fract +=  1562500;
	if(b_fract & 0x02) i_fract +=   781250;
	if(b_fract & 0x01) i_fract +=   390625;

	// convert to decimal string format 00.00000000 with optional leading '-'
	// Note:  Could loopify this but need to calculate the subtractor
	// values. Could do that using integer division (expensive), or
	// integer multiplication (also expensive).
	// BUT, could use a (fast) lookup table for the subtractor values
	// to avoid division.

	// first do the integer part

	// do the tens
	strOut[ch_p] = '0';
	while(i_whole >= 10){	// tens
		strOut[ch_p]++;		// count by characters
		i_whole -= 10;
	}
	ch_p++;					// next write spot

	// do the ones
	strOut[ch_p] = '0';
	while(i_whole >= 1){ 
		strOut[ch_p]++;  
		i_whole -= 1;
	}
	ch_p++;

	strOut[ch_p] = '.';			// decimal point
	ch_p++;

	// now do the fractional part

	// do the '10,000,000'
	strOut[ch_p] = '0';
	while(i_fract >= 10000000){ 
		strOut[ch_p]++;  
		i_fract -= 10000000;
	}
	ch_p++;

	// do the '1,000,000'
	strOut[ch_p] = '0';
	while(i_fract >= 1000000){ 
		strOut[ch_p]++;  
		i_fract -= 1000000;
	}
	ch_p++;

	// do the '100,000'
	strOut[ch_p] = '0';
	while(i_fract >= 100000){ 
		strOut[ch_p]++;  
		i_fract -= 100000;
	}
	ch_p++;

	// do the '10,000'
	strOut[ch_p] = '0';
	while(i_fract >= 10000){ 
		strOut[ch_p]++;  
		i_fract -= 10000;
	}
	ch_p++;

	// do the 'thousands'
	strOut[ch_p] = '0';
	while(i_fract >= 1000){ 
		strOut[ch_p]++;  
		i_fract -= 1000;
	}
	ch_p++;

	// do the 'hundreds'
	strOut[ch_p] = '0';
	while(i_fract >= 100){ 
		strOut[ch_p]++;  
		i_fract -= 100;
	}
	ch_p++;

	// do the 'tens'
	strOut[ch_p] = '0';
	while(i_fract >= 10){ 
		strOut[ch_p]++;  
		i_fract -= 10;
	}
	ch_p++;

	// do the 'ones'
	strOut[ch_p] = '0';
	while(i_fract >= 1){ 
		strOut[ch_p]++;  
		i_fract -= 1;
	}
	ch_p++;

	strOut[ch_p] = 0;	// null terminator
}

void print_all_in_range() {
	unsigned char byte;
	char output[40];

	for (int i = 0; i <= 255; ++i) {
		byte = i;
		software_ftoa(i, output);
		printf("%s", output);
		if (i != 255) printf(", ");
	}
}

void print8bits (unsigned char buffer) {
	int counter = 1;
	for (unsigned char mask = 0x80; mask; mask >>= 1) {
		if (mask & buffer) printf("1");
		else printf("0");
		if(counter++ % 4 == 0) {
			printf(" ");
		}
	}
	printf("\n");
}

void print16bits (unsigned short buffer) {
	int counter = 1;
	for (unsigned short mask = 0x8000; mask; mask >>= 1) {
		if (mask & buffer) printf("1");
		else printf("0");
		if(counter++ % 4 == 0) {
			printf(" ");
		}
	}
	printf("\n");
}

void print32bits (unsigned long buffer) {
	int counter = 1;
	for (unsigned long mask = 0x800000; mask; mask >>= 1) {
		if (mask & buffer) printf("1");
		else printf("0");
		if(counter++ % 4 == 0) {
			printf(" ");
		}
	}
	printf("\n");
}

unsigned char software_float_add(unsigned char float1, unsigned char float2) {
	unsigned short buffer1;
	unsigned short buffer2;
	unsigned short sum_buffer;
	int exponent;
	bool is_negative_float1 = false;
	bool is_negative_float2 = false;
	bool is_negative_sum = false;

	if (float1 & 0x80) is_negative_float1 = true;
	if (float2 & 0x80) is_negative_float2 = true;

	exponent = (float1 & 0x07) - 4;
	float1 &= 0x78;
	float1 |= 0x80;

	buffer1 = float1;
	buffer1 <<= 8;
	buffer1 >>= (7 - exponent);

	exponent = (float2 & 0x07) - 4;
	float2 &= 0x78;
	float2 |= 0x80;

	buffer2 = float2;
	buffer2 <<= 8;
	buffer2 >>= (7 - exponent);


	// Maybe I'm totally missing something here, but I belive the addition of
	// some logic to deal with negative addends is required for this to
	// function properly.
	if (is_negative_float1 || is_negative_float2) {

		if (is_negative_float1 && is_negative_float2) {
			is_negative_sum = true;
			sum_buffer = buffer1 + buffer2;
		} 
		
		else if (buffer1 >= buffer2) {
			sum_buffer = buffer1 - buffer2;
			if (is_negative_float1) is_negative_sum = true;
		}
		
		else {
			sum_buffer = buffer2 - buffer1;
			if (is_negative_float2) is_negative_sum = true;
		}

	}

	else sum_buffer = buffer1 + buffer2;

	printf("#1 Expanded:    ");
	print16bits(buffer1);
	printf("#2 Expanded:    ");
	print16bits(buffer2);
	printf("Sum:            ");
	print16bits(sum_buffer);
	
	exponent = 7;
	unsigned short bitfinder_mask = 0x8000;
	while (!(sum_buffer & bitfinder_mask)) {
		--exponent;
		bitfinder_mask >>= 1;
	}

	if (exponent > 3 || exponent < -4) {
		printf("Exponent of sum not within valid bounds.");
		exit(0);
	}

	unsigned char the_float;

	sum_buffer <<= (7 - exponent);
	sum_buffer >>= 8;
	printf("Sum Normalized: ");
	print16bits(sum_buffer);
	the_float = sum_buffer;
	the_float &= 0x78;
	exponent += 4;
	the_float |= exponent;
	if (is_negative_sum) the_float |= 0x80;
	printf("Sum Packed:     ");
	print8bits(the_float);

	return the_float;
}

unsigned char software_float_multiply(unsigned char first_float, unsigned char second_float) {
	unsigned short buffer1;	
	unsigned short buffer2;
	unsigned long buffer_product;
	bool is_negative_first_float = false;
	bool is_negative_second_float = false;
	int exponent1 = 0;
	int exponent2 = 0;
	int exponent_product;

	if (first_float & 0x80) is_negative_first_float = true;
	if (second_float & 0x80) is_negative_second_float = true;

	buffer1 = first_float; // Pack into bit field
	exponent1 = (buffer1 & 0x07) - 4; // Retrieve exponent
	buffer1 &= 0x0078; // Mask off everything escept mantissa
	buffer1 <<= 1; // Move into normal position
	buffer1 |= 0x0100; // Restore leading bit
	printf("#1 Expanded:      ");
	print16bits(buffer1);
	printf("#1 Exponent:      %i\n", exponent1);

	buffer2 = second_float; // Pack into bit field
	exponent2 = (buffer2 & 0x07) - 4; // Retrieve exponent
	buffer2 &= 0x0078; // Mask off everything escept mantissa
	buffer2 <<= 1; // Move into normal position
	buffer2 |= 0x0100; // Restore leading bit
	printf("#2 Expanded:      ");
	print16bits(buffer2);
	printf("#2 Exponent:      %i\n", exponent2);

	buffer_product = buffer1 * buffer2; // Regular old arithmetic operation
	buffer_product >>= 8;

	printf("Product:          ");
	print16bits(buffer_product);
	int rollover = 7; // Find the exponent of the product
	unsigned short bitfinder_mask = 0x8000;
	while (!(buffer_product & bitfinder_mask)) {
		--rollover;
		bitfinder_mask >>= 1;
	}

	exponent_product = exponent1 + exponent2 + rollover;

	printf("Product Exponent: %i\n", exponent_product);

	if (exponent_product > 3 || exponent_product < -4) {
		printf("Product out of range,exiting.\n");
		exit(1);
	}

	buffer_product<<= (7 - rollover);
	buffer_product >>= 8; // Start to pack the product
	unsigned char float_product = 0x00;
	float_product = buffer_product & 0x78;
	float_product += (exponent_product + 4) & 0x07;

	if (!is_negative_first_float != !is_negative_second_float) {
		float_product |= 0x80;
	}

	printf("Pruduct Packed:   ");
	print8bits(float_product);
	
	return float_product; 
}

int software_float_pow(int base, int exponent) {
	int x = 1;
	for (int i = 0; i < exponent; ++i) {
		x *= base;
	}

	return x;
}
