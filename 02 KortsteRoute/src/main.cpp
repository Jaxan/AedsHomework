#include <iostream>
#include "../include/NetwerkMatrix.h"
#include "../include/Verbinding.h"

int main() {

	try {

		NetwerkMatrix test("sporen.txt");
		Verbinding test2("sporen.txt");

		std::cout << std::endl << "Mijn netwerk heeft de grootte: " << test.getGrootte() << std::endl;
		test.kortsteRoute(1, 23);

		std::cout << std::endl << "Mijn andere netwerk heeft de grootte: " << test2.getGrootte() << std::endl;
		test2.kortsteRoute(1, 23);

	} catch(std::exception const& e) {

		std::cout << std::endl;
		std::cout << e.what() <<std::endl;

	}


	return 0;
}
