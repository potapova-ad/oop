#include <iostream>
#include "number.hpp"

int main() {

	Number *F = new Number [1000];
	F[0] = 1;
	F[1] = 1;
	for (int i = 2; i < 1000; i++)
		F[i] = F[i - 1] + F[i - 2];
	std::cout << F[999] << std::endl;

	Number fact = 1;
	for (int i = 2; i <= 1000; ++i) {
		fact *= i;
	}

	std::cout << fact << std::endl;

	std::string str = "" ;
	std::cin >> str ;

	Number current(str.data()), mx = current;
	int steps = 0;

	while (current != Number(1)) {
		++steps;
		if (current > mx)
			mx = current;
		if (current.isEven())
			current.div2();
		else {
			current = 3 * current + 1 ;
		}
	}
	std::cout << "steps = " << steps << " ; max = " << mx << std::endl;

	return 0;
}
