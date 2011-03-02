#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>

#include "include/Compressor.h"
#include "include/WelchTree.h"
#include "include/ostream_iterator_12bit.h"
#include "include/istream_iterator_12bit.h"

int main() try {
	JN::WelchTree<unsigned int> de;

	// willekeurige data (in vorm van vector, mag elke soort container zijn, ook pointer, of een bestand, of een stream, ALLES MAG)
	std::vector<char> string(135*20);
	std::generate(string.begin(), string.end(), []() { return rand()%3+'<'; });
	std::copy(string.begin(), string.end(), std::ostream_iterator<char>(std::cout));

	// Hierheen schrijven, mag ook een bestand zijn of een lijst of wat je maar wilt
	std::stringstream output;
	de.compress(string.begin(), string.end(), JN::ostream_iterator_12bit<unsigned int>(output));

	std::cout << "\n\n";

	JN::Compressor poep;
	poep.decompress(JN::istream_iterator_12bit<unsigned int>(output), JN::istream_iterator_12bit<unsigned int>(), std::ostream_iterator<char>(std::cout));

	return 0;
}
catch (std::exception const &e){
	std::cerr << e.what() << std::endl;
}
