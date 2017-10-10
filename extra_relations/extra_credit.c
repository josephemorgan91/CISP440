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
static int debug = 0;
static int verbose = 0;
static int g_size = 0;
static int g_density = 0;

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
int overlaps (int matrix[MAX][MAX], int x, int y);

int main (int argc, char *argv[])
{
	srand ((unsigned)time(NULL));
	for (int i = 1; i < argc; ++i) {
		if (strcmp (argv[i], "-s") == 0) {
			g_size = atoi(argv[i++ + 1]);
		} else if (strcmp (argv[i], "-e") == 0) {
			g_density = atoi (argv[i++ + 1]);
		} else if (strcmp (argv[i], "-d") == 0) {
			debug = 1;
		} else if (strcmp (argv[i], "-v") == 0) {
			verbose = 1;
		} else if (argc != 1) {
			fprintf(stderr, "Usage: %s [-s size] [-e density] [-v] [-d]\n", argv[0]);
			fprintf(stderr, "    -s size: Size of the matrix to be randomly generated\n");
			fprintf(stderr, "    -e density: Likelyhood that any given relation will exist. Higher means less likely\n");
			fprintf(stderr, "    -v: enable verbose output\n");
			fprintf(stderr, "    -d: enable debugging output\n");
			exit(1);
		}
	}

	Relation *test_rand = gen_random_relation();
	print_matrix (test_rand);
	if (verbose) {
		print_relation (test_rand);
		find_equiv_classes (test_rand);
		print_equiv_classes (test_rand);
		int is_EQR = 1;
		is_reflexive(test_rand) ?
			(printf("Is Reflexive\n")) :
			(is_EQR = 0, printf("Isn't Reflexive\n"));
		is_symetric(test_rand) ?
			(printf("Is Symetrical\n")) :
			(is_EQR = 0, printf("Isn't Symetrical\n"));
		is_transitive(test_rand) ?
			(printf("Is Transitive\n")) :
			(is_EQR = 0, printf("Isn't Transitive\n"));
	}
	return 0;
}

Relation* init_relation_blank (int size)
{
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
			printf(" %i", r->matrix[i][j]);
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
			printf(" } \n");
		}
	}
	printf("\n");
}

Relation* gen_random_relation()
{
	int size;
	if (g_size)
		size = g_size;
	else
		size = (rand() % (MAX - 3)) + 4;
	unsigned int density;
	if (g_density)
		density = g_density;
	else
		density = (rand() % 4) + 5;
	int eq_rel_found = 0;
	int ec_matrix[MAX][MAX];
	for (int i = 0; i < MAX; ++i)
		for (int j = 0; j < MAX; ++j)
			ec_matrix[i][j] = 0;
	int ec_matrix_row= 0;
	Relation* rand_relation = init_relation_blank (size);

	ec_matrix[0][0] = 1; // First, generate initial equivalence class.
	for (int i = 0; i < size; ++i)
		if (rand() % 10 >= density)
			ec_matrix[0][i] = 1;
	++ec_matrix_row;

	for (int r = 0; r < size; ++r) {// For each row in ec_matrix...
		if (debug)
			printf("Attempting to write row %i\n", r);
		for (int p = 0; !eq_rel_found && p <= r ; ++p) { // Scan ec_matrix...
			if (debug)
				printf("Scanning ec_matrix row %i\n", p);
			if (ec_matrix[p][r]) { // To see if (r, r) is already part of an equivalence class. If it is...
				if (debug)
					printf("(x, %i) is is row %i of ec_matrix\n", r, p);
				for (int c = 0; c < size; ++c) { // Copy the row from ec_matrix to rand_relation->matrix.
					rand_relation->matrix[r][c] = ec_matrix[p][c];
					if(debug) {
						printf("Copying %i from ec_matrix[%i, %i]", ec_matrix[p][c], p, c);
						printf(" to rand_relation->matrix[%i, %i]\n", r, c);
					}
				}
				eq_rel_found = 1;
			}
		}
		if (!eq_rel_found) { // If there isn't already an equiv. class cont (r, r)...
			ec_matrix[ec_matrix_row][r] = 1; // Randomly generate one
			for (int y = 1; y < size; ++y)
				if (rand() % 10 >= density && !overlaps(ec_matrix, ec_matrix_row, y))
					ec_matrix[ec_matrix_row][y] = 1;
			for (int c = 0; c < size; ++c) { // And copy it into rand_relation->matrix
				rand_relation->matrix[r][c] = ec_matrix[ec_matrix_row][c];
			}
			++ec_matrix_row;
		}
		eq_rel_found = 0;
	}
	return rand_relation;
}

int overlaps (int matrix[MAX][MAX], int x, int y)
{
	int result = 0;
	for (int i = 0; i < x; ++i)
		if (matrix[i][y])
			result = 1;
	return result;
}
