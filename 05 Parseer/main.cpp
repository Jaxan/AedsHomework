#include <iostream>
#include <sstream>
#include <iterator>

#include "include/tokenizor.h"
#include "include/parser.h"


int main() {
	try {
		std::stringstream str(". ~(~(~A -> Benis) /\\ D /\\ A), B, D");
		parser<std::istream_iterator<token>> pars0r = parser<std::istream_iterator<token>>(std::istream_iterator<token>(str));

		pars0r.parse();

		std::cout << "The sequent is:\n" << (*pars0r.root) << "leuk he\n";
	} catch (std::exception const & e) {
		std::cout << e.what();
	}

	return 0;
}
