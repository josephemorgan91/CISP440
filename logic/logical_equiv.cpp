#include <cstdio>

bool implication (bool a, bool b);
bool bicondition (bool a, bool b);
bool maybe (bool a, bool b);
bool because (bool a, bool b);
bool logic_and (bool a, bool b);
bool logic_or (bool a, bool b);
bool logic_xor (bool a, bool b);
bool logic_not (bool a);

int main()
{
	bool r1;
	bool r2;
	bool equiv = true;
	// a
	printf("| p q | p or q | ~(~p and ~q) |\n");
	printf("-------------------------------\n");
	for (int p = 0; p < 2; ++p) {
		for (int q = 0; q < 2; ++q) {
			r1 = logic_or (p, q);
			r2 = logic_not(logic_and(logic_not(p), logic_not(q)));
			if (r1 != r2)
				equiv = false;
			printf ("| %i %i | %6i | %12i |\n", p, q, r1, r2);
		}
	}
	equiv ? printf("\nExpressions are equivalent\n") : printf("\nExpressions are not equivalent\n");
	printf("\n\n");
	equiv = true;

	// b

	printf("| p q r | p & (q -> r) | (p & q) ^ r |\n");
	printf("--------------------------------------\n");
	for (int p = 0; p < 2; ++p) {
		for (int q = 0; q < 2; ++q) {
			for (int r = 0; r < 2; ++r) {
				r1 = logic_and (p, implication (q, r));
				r2 = logic_xor (logic_and (p, q), r);
				if (r1 != r2)
					equiv = false;
				printf ("| %i %i %i | %12i | %11i |\n", p, q, r, r1, r2);
			}
		}
	}
	equiv ? printf("\nExpressions are equivalent\n") : printf("\nExpressions are not equivalent\n");
	printf("\n\n");
	equiv = true;

	// c

	printf("| p q | p bicondition q | ~(p xor q) |\n");
	printf("--------------------------------------\n");
	for (int p = 0; p < 2; ++p) {
		for (int q = 0; q < 2; ++q) {
			r1 = bicondition (p, q);
			r2 = logic_not (logic_xor (p, q));
			if (r1 != r2)
				equiv = false;
			printf ("| %i %i | %15i | %10i |\n", p, q, r1, r2);
		}
	}
	equiv ? printf("\nExpressions are equivalent\n") : printf("\nExpressions are not equivalent\n");
	printf("\n\n");
	equiv = true;

	// d

	printf("| p q r | (p <-> q) -> r | p & (~q | r) |\n");
	printf("---------------------------------------\n");
	for (int p = 0; p < 2; ++p) {
		for (int q = 0; q < 2; ++q) {
			for (int r = 0; r < 2; ++r) {
				r1 = implication (bicondition (p, q), r);
				r2 = logic_and (p, logic_or (logic_not(q), r));
				if (r1 != r2)
					equiv = false;
				printf ("| %i %i %i | %14i | %12i |\n", p, q, r, r1, r2);
			}
		}
	}
	equiv ? printf("\nExpressions are equivalent\n") : printf("\nExpressions are not equivalent\n");
	printf("\n\n");
	equiv = true;

	// e

	printf("| p q r | ~(p -> (q & r)) | p & ~(q & r) |\n");
	printf("----------------------------------------\n");
	for (int p = 0; p < 2; ++p) {
		for (int q = 0; q < 2; ++q) {
			for (int r = 0; r < 2; ++r) {
				r1 = logic_not (implication (p, logic_and (q, r)));
				r2 = logic_and (p, logic_not (logic_and (q, r)));
				if (r1 != r2)
					equiv = false;
				printf ("| %i %i %i | %15i | %12i |\n", p, q, r, r1, r2);
			}
		}
	}
	equiv ? printf("\nExpressions are equivalent\n") : printf("\nExpressions are not equivalent\n");
	printf("\n\n");
	equiv = true;

	// f p | (p ? q) ≡ p & (p @ q)k

	printf("| p q | p | (p ? q) | p & (p @ q) |\n");
	printf("-----------------------------------\n");
	for (int p = 0; p < 2; ++p) {
		for (int q = 0; q < 2; ++q) {
			r1 = logic_or (p, maybe (p, q));
			r2 = logic_and (p, because (p, q));
			if (r1 != r2)
				equiv = false;
			printf ("| %i %i | %11i | %11i |\n", p, q, r1, r2);
		}
	}
	equiv ? printf("\nExpressions are equivalent\n") : printf("\nExpressions are not equivalent\n");
	printf("\n\n");
	equiv = true;
}

bool implication (bool a, bool b)
{
	return ((!a) || b);
}

bool bicondition (bool a, bool b)
{
	return logic_and(implication (a, b), implication (b, a));
}

bool maybe (bool a, bool b)
{
	if (!a && b)
		return true;
	return false;
}

bool because (bool a, bool b)
{
	b = b % 2;
	if (a)
		return true;
	return false;
}

bool logic_and (bool a, bool b)
{
	return (a && b);
}

bool logic_or (bool a, bool b)
{
	return (a || b);
}

bool logic_xor (bool a, bool b)
{
	return (a != b);
}

bool logic_not (bool a)
{
	return (!a);
}
