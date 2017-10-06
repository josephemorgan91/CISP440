#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

const int MAX = 40;

struct Relation_matrix {
	int matrix[MAX][MAX];
	int size;

	Relation_matrix();
};

typedef struct Relation_matrix Relation_matrix;

struct Relation {
	private:
		Relation_matrix* m_matrix_ptr;
		int m_equiv_classes[MAX];

	public:
		Relation();
		Relation(std::string);
		~Relation();

		void print_matrix();
		bool is_reflexive();
		bool is_symetric();
		Relation_matrix square_matrix();
		bool is_transitive();
		void find_equiv_classes();
		void print_equiv_classes();
};

int main (int argc, char* argv[]) {
	if (argc != 2) {
		std::cout <<
			"Usage: pass a number as a command line argument\n"
			"corresponding to which input file you'd like to use.\n";
		exit(1);
	}

	std::string fn_start = "R";
	char* fn_number = argv[1];
	std::string fn_end = ".bin";
	std::string filename = fn_start + fn_number + fn_end;

	Relation test_relation(filename.c_str());
	test_relation.print_matrix();

	bool is_EQR = true;
	test_relation.is_reflexive() ?
		(std::cout << "Reflexive\n") :
		(is_EQR = false, std::cout << "Not Reflexive\n");
	test_relation.is_symetric() ?
		(std::cout << "Symetric\n") :
		(is_EQR = false, std::cout << "Not Symetric\n");
	test_relation.is_transitive() ?
		(std::cout << "Transitive\n") :
		(is_EQR = false, std::cout << "Not Transitive\n");

	if (is_EQR) {
		std::cout << "Detected Equivelance Relation! Finding equiv. classes...\n";

		test_relation.find_equiv_classes();
		test_relation.print_equiv_classes();
	}
}

Relation_matrix::Relation_matrix() {
	for (int i = 0; i < MAX; ++i) {
		for (int j = 0; j < MAX; ++j) {
			matrix[i][j] = 0;
		}
	}
}

Relation::Relation() {
	for (int i = 0; i < MAX; ++i) m_equiv_classes[i] = 0;
	m_matrix_ptr = new Relation_matrix();
}

Relation::Relation (std::string filename) {
	for (int i = 0; i < MAX; ++i) m_equiv_classes[i] = 0;
	m_matrix_ptr = new Relation_matrix();

	char c;
	std::ifstream fin(filename.c_str(), std::ios_base::binary);
	if ( !fin ) { std::cerr << "Input file could not be opened\n"; exit(1); }

	fin.read(&c, 1); m_matrix_ptr->size = c;

	int i, j;
	for(i = 0; i < m_matrix_ptr->size; i++)
		for(j = 0; j < m_matrix_ptr->size; j++)
		{
			fin.read(&c, 1);
			m_matrix_ptr->matrix[i][j] = c;
		}

	fin.close();
}

Relation::~Relation() {
	delete m_matrix_ptr;
}

void Relation::print_matrix() {
	int i, j;

	for(i = 0; i < m_matrix_ptr->size; i++) {
		for(j = 0; j < m_matrix_ptr->size; j++)
			std::cout << m_matrix_ptr->matrix[i][j];
		std::cout << std::endl;
	}
}

bool Relation::is_reflexive() {
	bool result = true;

	for (int i = 0; i < m_matrix_ptr->size; ++i) {
		if (m_matrix_ptr->matrix[i][i] != 1) {
			result = false;
		}
	}

	return result;
}

bool Relation::is_symetric() {
	bool result = true;

	for (int i = 0; i < m_matrix_ptr->size; ++i) {
		for (int j = 0; j < m_matrix_ptr->size; ++j) {
			if (m_matrix_ptr->matrix[i][j] == 1 &&
					m_matrix_ptr->matrix[j][i] != 1) {
				result = false;
			}
		}
	}

	return result;
}

Relation_matrix Relation::square_matrix() {
	Relation_matrix new_rm;
	new_rm.size = m_matrix_ptr->size;
	int temp = 0;

	for (int i = 0; i < m_matrix_ptr->size; ++i) {
		for (int j = 0; j < m_matrix_ptr->size; ++j) {
			for (int k = 0; k < m_matrix_ptr->size; ++k) {
				temp += m_matrix_ptr->matrix[i][k] * m_matrix_ptr->matrix[j][k];
			}
			new_rm.matrix[i][j] = temp;
			temp = 0;
		}
	}

	return new_rm;
}

bool Relation::is_transitive() {
	bool result = true;
	Relation_matrix squared_matrix = square_matrix();

	for (int i = 0; i < m_matrix_ptr->size; ++i) {
		for (int j = 0; j < m_matrix_ptr->size; ++j) {
			if (m_matrix_ptr->matrix[i][j] == 0 && squared_matrix.matrix[i][j] != 0) {
				result = false;
			}
		}
	}

	return result;
}

void Relation::find_equiv_classes() {
	m_equiv_classes[0] = 1;

	for (int i = 1; i < m_matrix_ptr->size; ++i) {
		m_equiv_classes[i] = 1;
		for (int j = i - 1; j >= 0; --j) {
			if (m_matrix_ptr->matrix[i][j]) m_equiv_classes[i] = 0;
		}
	}
}

void Relation::print_equiv_classes() {
	for (int i = 0; i < MAX; ++i) {
		if (m_equiv_classes[i]) {
			std::cout << "[" << i << "] : {";
			for (int j = 0; j < m_matrix_ptr->size; ++j) {
				if (m_matrix_ptr->matrix[i][j]) std::cout << " " << j;
			}
			std::cout << " } \n";
		}
	}

	std::cout << std::endl;
}
