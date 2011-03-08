#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>

#include "include/Compressor.h"
#include "include/Decompressor.h"
#include "include/ostream_iterator_12bit.h"
#include "include/istream_iterator_12bit.h"

int main() try {
	// willekeurige data (in vorm van vector, mag elke soort container zijn, ook pointer, of een bestand, of een stream, ALLES MAG)
	// Note: random is moeilijke te comprimeren
	std::vector<char> string(135*20);
	std::generate(string.begin(), string.end(), []() { return rand()%3+'<'; });

	// data outputten. voor verificatie
	std::copy(string.begin(), string.end(), std::ostream_iterator<char>(std::cout));

	// Hierheen schrijven, mag ook een bestand zijn of een lijst of wat je maar wilt, met onze ostream_iterator zorg je voor de 12bits-heid.
	std::stringstream output;
	JN::compress(string.begin(), string.end(), JN::ostream_iterator_12bit<unsigned int>(output));
	std::cout << std::endl;

	// weer decoden :D (meteen naar console schrijven)
	JN::decompress(JN::istream_iterator_12bit<unsigned int>(output), JN::istream_iterator_12bit<unsigned int>(), std::ostream_iterator<char>(std::cout));

	return 0;
} catch(std::exception const& e) {
	std::cerr << e.what() << std::endl;
}
