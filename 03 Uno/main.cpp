#include <iostream>
#include <vector>

#include "include/List.h"
#include "include/Game.h"


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
