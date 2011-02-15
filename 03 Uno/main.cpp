#include <iostream>
#include <vector>

#include "include/List.h"
#include "include/Card.h"
#include "include/Game.h"

template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& x) {
	std::copy(x.cbegin(), x.cend(), std::ostream_iterator<T>(out, " "));
}

int main(int argc, char* argv[]) {

	try {
	    Game game;

		return 0;
	} catch(std::exception& e) {
		std::cerr << e.what() << std::endl;
	} catch(...) {
#define wtf {std::cerr << "WAAAAAAAAAARRRRRRRGHHHHHHHHHHHHHHHHHNOWAI" << std::endl;};;;;;;;;;;
		wtf;
	}
}
