#include <iostream>

#include "include/WelchTree.h"

int main(){
	JN::WelchTree<unsigned int> dol;

	auto pair = dol.find("a");

	std::cout << pair << std::endl;

    return 0;
}
