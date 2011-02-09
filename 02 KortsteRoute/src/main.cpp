// Nick Overdijk 3029832
// Joshua Moerman 3009408

#include <iostream>
#include "../include/NetwerkMatrix.h"
#include "../include/Verbinding.h"

/*
OUTPUT:
    Mijn netwerk heeft de grootte: 23
    kortste pad is 137km :D
    Volg het pad: 14, 9, 8, 6, 5, 11, 10 klaar!

    Mijn andere netwerk heeft de grootte: 23
    kortste pad is 137km :D
    Volg het pad: 14, 9, 8, 6, 5, 11, 10 klaar!
*/

int main() {

	try {

		NetwerkMatrix test("sporen.txt");
		Verbinding test2("sporen.txt");

		std::cout << std::endl << "Mijn netwerk heeft de grootte: " << test.getGrootte() << std::endl;
		test.kortsteRoute(14, 10);

		std::cout << std::endl << "Mijn andere netwerk heeft de grootte: " << test2.getGrootte() << std::endl;
		test2.kortsteRoute(14, 10);

	} catch(std::exception const& e) {

		std::cout << "De volgende foutd trad op:" << std::endl;
		std::cout << __func__ << ": " << e.what() << std::endl;

	}


	return 0;
}


