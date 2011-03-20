// Nick Overdijk	3029832
// Joshua Moerman	3009408

#include <iostream>
#include <sstream>
#include <iterator>

#include "include/tokenizor.h"
#include "include/parser.h"

/**
    inhoud project:
        grammar.h           grammatica van onze parser
        parser.h            de parser
        tokenizer.h         hulpje van de parser (een >> operator)
        logic.h             datastructuren voor proposities, sequenten en de bewijzer
        syntax_error.h      exception
        arithmetic.h        hulp units
 */

int main() {
	try {
		std::stringstream str("A, B, D -> Aap \\/ Beer . ~(~(~A -> B) /\\ D /\\ A), B, D");
		parser<std::istream_iterator<token>> pars0r = parser<std::istream_iterator<token>>(std::istream_iterator<token>(str));

		pars0r.parse();

		std::cout << "The sequent is:\n" << (*pars0r.root);

		//We didn't have the time to implement this.
		//counterexample(*pars0r.root);

	} catch (std::exception const & e) {
		std::cout << e.what();
	}

	return 0;
}
