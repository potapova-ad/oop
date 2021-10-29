#include <iostream>
#include <utility>
#include <set>
#include <map>


int main () {


	std::pair p {std::string{"Moscow"}, 1147};
	auto [name1, age1] = p;
	std::cout << name1 << " " << age1 << std::endl; 

	std::string &name = p.first;
	int &age = p.second;
	name = "M";
	auto [name1, age1] = p; 
	std::cout << name1 << " " << age1 << std::endl ;


	std::cout << std::endl;


	std::set s {1, 2, 4, 5, 9};
	std::pair result = s.insert(5);
	if (result.second == true) {
		std::cout << "Element added successfully" << std::endl;
	}
	else {
		std::cout << "Element already existed" << std::endl;
	}
	for (auto it = s.begin(); it != result.first; ++it) {
		std::cout << *it << " ";
	}


	std::cout << std::endl;


	std::map<std::string, int> word_count;
	while (true) {
	std::string word;
	std::cin >> word;
	std::pair wc {word, 1};
	auto p = word_count.insert(wc);
	
	if (p.second == false) {
		word_count[word] += 1;
	}
	std::cout << "Dictionary:" << std::endl;
	for (auto it : word_count) {
		std::cout << it.first << ": " << it.second << std::endl;
	}
	std::cout << std::endl;
	}

	return 0;
}