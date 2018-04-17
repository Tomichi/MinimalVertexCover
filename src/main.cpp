#include <iostream>
#include "Individual.h"

int main() {

	Individual a(5);
	Individual b(5);
	Individual c(a,b);
	a.Print();
	std::cout << '\n';
	b.Print();
	std::cout << '\n';
	c.Print();

	return 0;
}

