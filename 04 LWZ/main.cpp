#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>

#include "include/Compressor.h"
#include "include/WelchTree.h"
#include "include/ostream_iterator_12bit.h"
#include "include/istream_iterator_12bit.h"

int main() try {
	/*
	JN::WelchTree<unsigned int> de;

	// willekeurige data (in vorm van vector, mag elke soort container zijn, ook pointer, of een bestand, of een stream, ALLES MAG)
	std::vector<char> string(60);
	std::generate(string.begin(), string.end(), []() { return rand()%26+'A'; });

	// Hierheen schrijven, mag ook een bestand zijn of een lijst of wat je maar wilt
	std::fstream output("test.data");
	if(!output) throw 37;
	de.compress(string.begin(), string.end(), JN::ostream_iterator_12bit<unsigned int>(output));	// we gebruiken een 12bit iterator :D

	// statistics
	//std::cout << "lengte is " << output.str().length() << " dat is " << (float)output.str().length() / (float)string.size() << " groter." << std::endl;
	//std::cout << output.str() << std::endl;

	output.seekg(0, std::ios_base::beg);
	std::copy(JN::istream_iterator_12bit<unsigned int>(output), JN::istream_iterator_12bit<unsigned int>(), std::ostream_iterator<unsigned int>(std::cout, " "));
	*/

	JN::Compressor poep;

	std::vector<unsigned int> a = { 97, 98, 97, 99, 256, 260 };
	poep.decompress(a.begin(), a.end(), std::ostream_iterator<char>(std::cout));

    return 0;
}
catch (std::exception const &e){
	std::cerr << e.what() << std::endl;
}
