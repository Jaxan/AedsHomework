#include <iostream>
#include <sstream>

#include "include/tokenizor.h"
#include "include/parser.h"

int main() {

	std::stringstream str("A/\\B.->C");
	parser pars0r(str);

	return 0;
}
