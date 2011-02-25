#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>

#include "include/WelchTree.h"

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

	std::vector<char> string(1000);
	std::generate(string.begin(), string.end(), []() { return rand()%4+'a'; });

	std::stringstream output;
	de.compress(string.begin(), string.end(), std::ostream_iterator<unsigned int>(output, " "));

	std::cout << "lengte is " << output.str().length()/4 << " en inhoud: " << output.str();

    return 0;
}
/*catch (std::exception const &e){
	std::cerr << e.what() << std::endl;
}*/
