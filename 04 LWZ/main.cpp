#include <iostream>

#include "include/WelchTree.h"

template <typename T1, typename T2>
std::ostream& operator<< (std::ostream &os, const std::pair<T1, T2> &x){
	os << "(" << x.first << ", " << x.second << ")";

	return os;
}

std::ostream& operator<< (std::ostream &os, unsigned int * const &x){
	os << *x;
	return os;
}

int main(){
	JN::WelchTree<unsigned int> dol;

	std::string query = "(^_^)";
	auto pair = dol.find(query.begin(), query.end());

	std::cout << "(" << *pair.first << ", " << *pair.second << ")\n";

    return 0;
}
