// CISP440 Extra Credit
// by Joseph Morgan
//
// Originally, this was written using classes and object-oriented design, with
// which I'm much more comfortable than procedural C. I decided to modify this
// program to compile with no warnings with the --std=c99 flag, as well as
// -Wall, -pedantic, etc. in order to be sure to 100% within the assignment
// specifications. Professor Ross mentioned at one point that he wants
// assignments in this class to be written in C, without using features
// implemented exclusively in C++. Some of the provided code for other
// assignemnts uses C++ classes (iostream and fstream, for example), but I
// wanted to err on the side of caution. Also, it was more fun to do something
// I'm less familiar with.
//
// I included some functions mostly as they were written in the last homework
// assignment for testing purposes.
//
// My algorithm for pseudo-randomly generating equivilence classes was:
// 	1. Pseudo-randomly pick a matrix size between 2 and MAX.
// 	2. Fill all [x][y] positions where x == y, to satisfy reflexivity.
// 	3. Randomly fill positions throughout matrix.
// 	4. If [x][y] is filled randomly, also fill [y][x].
// 	5. Satisfy transitivity:
// 		a. Iterate through matrix, if [x][y] is filled...
// 		b. Iterate through [y][i]. If [y][i] is filled...
// 		c. Fill [x][i] if it is not already filled.
// 	6. Check for reflixivity, symetry and transitivity to make sure I didn't
// 		goof up.
// 	7. Find and print equiv. classes for completeness' sake.
//
// I'm not sure if this is a particularly elegant solution, but I feel like
// I was successful in avoiding a 'guess-and-check' method. Essentially, I'm
// generating a random matrix and then modifying it to make it an equiv.
// relation.

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

static const int MAX = 40;
static const int MAX_FILENAME = 20;

struct Relation
{
	int **matrix;
	int size;
	int *equiv_classes;
};
typedef struct Relation Relation;

Relation* init_relation_blank (int size);
Relation* init_relation_from_file (const char *filename);
void free_relation (Relation *r);
void print_matrix (Relation *r);
void print_relation (Relation *r);
int is_reflexive (Relation *r);
int is_symetric (Relation *r);
void square_matrix (Relation *r, Relation *s);
int is_transitive (Relation *r);
void find_equiv_classes (Relation *r);
void print_equiv_classes (Relation *r);
Relation* gen_random_relation();
void trans_vortex (Relation *r, int x, int y);

int main (int argc, char *argv[])
{
	char *filename;
	filename = malloc(20 * sizeof(char));
	strcpy(filename, "R1.bin");

	if (argc == 3 && strcmp (argv[1], "-f") == 0) {
		strcpy(filename, argv[2]);
	} else if (argc == 3 && strcmp (argv[1], "-n") == 0) {
		filename[1] = argv[2][0];
	} else if (argc != 1) {
		fprintf(stderr, "Usage: %s [-f filename] [-n file_number]\n", argv[0]);
		fprintf(stderr, "    -f filename: Name of binary file containing relation\n");
		fprintf(stderr, "    -n file_number: Number of file n following format Rn.bin\n");
		exit(1);
	}

	Relation *test_rand = gen_random_relation();
	print_matrix (test_rand);
	print_relation (test_rand);

	// Relation* test_relation = init_relation_from_file (filename);
	// print_matrix (test_relation);
	// Relation* square_test = init_relation_blank(test_relation->size);
	// square_matrix (test_relation, square_test);
	// print_matrix (square_test);

	// int is_EQR = 1;

	// is_reflexive(test_relation) ?
	//   (printf("Is Reflexive\n")) :
	//   (is_EQR = 0, printf("Isn't Reflexive\n"));
	// is_symetric(test_relation) ?
	//   (printf("Is Symetrical\n")) :
	//   (is_EQR = 0, printf("Isn't Symetrical\n"));

	// is_transitive(test_relation) ?
	//   (printf("Is Transitive\n")) :
	//   (is_EQR = 0, printf("Isn't Transitive\n"));
	return 0;
}

Relation* init_relation_blank (int size) {
	// Create 2d array
	Relation* new_relation = (Relation*)malloc(sizeof(Relation));
	new_relation->matrix = malloc(MAX * sizeof(int*));
	for (unsigned int i = 0; i < MAX; ++i)
		new_relation->matrix[i] = malloc(MAX * sizeof(int));

	// Zero out array
	for (unsigned int i = 0; i < MAX; ++i) {
		for (unsigned int j = 0; j < MAX; ++j) {
			new_relation->matrix[i][j] = 0;
		}
	}
	new_relation->size = size;

	// Init equiv classes
	new_relation->equiv_classes = malloc(MAX * sizeof(int));
	for (unsigned int i = 0; i < MAX; ++i)
		new_relation->equiv_classes[i] = 0;
	return new_relation;
}

void free_relation (Relation* r)
{
	for (unsigned int i = 0; i < MAX; ++i)
		free (r->matrix[i]);
	free (r->matrix);
	free (r->equiv_classes);
	free (r);
}

Relation* init_relation_from_file (const char *filename)
{
	Relation *new_relation;

	// Read file for matrix values
	char c;
	FILE *infile;
	infile = fopen(filename, "rb");
	if (!infile) {
		fprintf(stderr, "Input file could not be opened\n");
		exit(1);
	}
	fscanf(infile, "%c", &c);
	new_relation = init_relation_blank ((int)c);
	for (int i = 0; i < new_relation->size; i++) {
		for (int j = 0; j < new_relation->size; j++) {
			fscanf(infile, "%c", &c);
			new_relation->matrix[i][j] = c;
		}
	}
	return new_relation;
}

void print_matrix (Relation *r)
{
	for (int i = 0; i < r->size; i++) {
		for (int j = 0; j < r->size; j++) {
			printf("%i", r->matrix[i][j]);
		}
		printf("\n");
	}
}

void print_relation (Relation *r)
{
	printf("R = {\n");
	for (int i = 0; i < r->size; ++i) {
		for (int j = 0; j < r->size; ++j) {
			if (r->matrix[i][j])
				printf(" (%i, %i)", i, j);
		}
		printf("\n");
	}
	printf("}\n");
}

int is_reflexive (Relation *r)
{
	int result = 1;

	for (int i = 0; i < r->size; ++i)
		if (r->matrix[i][i] != 1)
			result = 0;

	return result;
}

int is_symetric (Relation *r)
{
	int result = 1;

	for (int i = 0; i < r->size; ++i)
		for (int j = 0; j < r->size; ++j)
			if ((r->matrix[i][j] == 1 && r->matrix[j][i] != 1) ||
					(r->matrix[j][i] == 1 && r->matrix[i][j] != 1))
				result = 0;
	return result;
}

void square_matrix (Relation *r, Relation *s)
{
	int temp = 0;

	for (int i = 0; i < r->size; ++i) {
		for (int j = 0; j < r->size; ++j) {
			for (int k = 0; k < r->size; ++k) {
				temp += r->matrix[i][k] * r->matrix[j][k];
			}
			s->matrix[i][j] = temp;
			temp = 0;
		}
	}
}

int is_transitive (Relation *r)
{
	int result = 1;
	Relation* squared_r = init_relation_blank(r->size);
	square_matrix(r, squared_r);

	for (int i = 0; i < r->size; ++i) {
		for (int j = 0; j < r->size; ++j) {
			if (r->matrix[i][j] == 0 && squared_r->matrix[i][j] != 0) {
				result = 0;
			}
		}
	}
	free_relation (squared_r);
	return result;
}

void find_equiv_classes (Relation* r)
{
	r->equiv_classes[0] = 1;

	for (int i = 1; i < r->size; ++i) {
		r->equiv_classes[i] = 1;
		for (int j = i - 1; j >= 0; --j) {
			if (r->matrix[i][j]) r->equiv_classes[i] = 0;
		}
	}
}

void print_equiv_classes (Relation* r)
{
	for (int i = 0; i < MAX; ++i) {
		if (r->equiv_classes[i]) {
			printf("[%i] : {", i);
			for (int j = 0; j < r->size; ++j) {
				if (r->matrix[i][j]) printf(" %i", j);
			}
			printf("} \n");
		}
	}
	printf("\n");
}

Relation* gen_random_relation()
{
	srand ((unsigned)time(NULL));
	int size = (rand() % MAX) + 1;
	unsigned int density = (rand() % 6) + 1;

	Relation* rand_relation = init_relation_blank (size);
	for (int i = 0; i < size; ++i)
		rand_relation->matrix[i][i] = 1;

	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
			if (rand() % density == 0) {
				rand_relation->matrix[i][j] = 1;
				for (int k = 0; k < size; ++k) {
					if (rand_relation->matrix[k][i])
						rand_relation->matrix[k][j] = 1; // TODO: But wait... this is adding a new (b, c),
					// is there an (a, b) without an (a, c)?
				}
				rand_relation->matrix[j][i] = 1;
			}


	return rand_relation;
}

void trans_vortex (Relation *r, int b, int c) {
	// TODO
	// 	1. Add node to matrix
	// 	2. Check if node breaks transitivity
	// 	3. If it does, call trans_vortex to add correcting node to matrix.

	r->matrix[b][c] = 1; // (x, y) are the (b, c)
	for (int a = 0; a < r->size; ++a) { // search possible (a, b)'s
		if (r->matrix[a][b] && !r->matrix[a][c]) { // If there is an (a, b) with no (a, c)
			trans_vortex (r, a, c); // Add that (a, c), but be sure to check it too for transitivity violations
		}
	}
	// TODO:
	// We still have to think about the symetry of nodes we're adding...
}
