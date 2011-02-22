#include <iostream>

#include "include/WelchTree.h"

template <typename T1, typename T2>
std::ostream& operator<< (std::ostream &os, const std::pair<T1, T2> &x){
	os << "(" << x.first << ", " << x.second << ")";
	
	return os;
}

int main(){
	JN::WelchTree<unsigned int> dol;

	auto pair = dol.find("a");

	std::cout << pair << std::endl;

    return 0;
}
