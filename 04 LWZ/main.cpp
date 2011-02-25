#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>

#include "include/WelchTree.h"
#include "include/ostream_iterator_12bit.h"

template <typename T1, typename T2>
std::ostream& operator<< (std::ostream &os, const std::pair<T1, T2> &x){
	os << "(" << x.first << ", " << x.second << ")";

	return os;
}

std::ostream& operator<< (std::ostream &os, unsigned int * const &x){
	os << *x;
	return os;
}

int main() /*try*/ {
	JN::WelchTree<unsigned int> de;

	std::vector<char> string(100000);
	std::generate(string.begin(), string.end(), []() { return rand()%52+'A'; });

	std::stringstream output;
	de.compress(string.begin(), string.end(), JN::ostream_iterator_12bit<unsigned int>(output));

	std::cout << "lengte is " << output.str().length() << " en inhoud: " << output.str();

    return 0;
}
/*catch (std::exception const &e){
	std::cerr << e.what() << std::endl;
}*/
