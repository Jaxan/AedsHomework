#ifndef JN_DECOMPRESSOR_H
#define JN_DECOMPRESSOR_H

#include "Party.hardy"

#include <vector>
#include <algorithm>
#include <string>

namespace JN {

class Decompressor {
public:
	// ctor, vult de basis-codes
	Decompressor() : table() {
		for(unsigned int i = 0; i < 256; ++i) {
			char c = i;
			table.push_back((Code) {-1, c});
		}
	}

	// decomprimeert alles tussen begin en end, schrijft weg naar out
	template <typename IteratorType, typename OutputIteratorType>
	void decompress(IteratorType begin, IteratorType end, OutputIteratorType out) {
		auto previous_code = *begin++;
		if(previous_code > table.size()) throw party(std::string("JN::")+__func__+"Unexpected code");

		auto previous_string = fetch(previous_code);
		std::copy(previous_string.begin(), previous_string.end(), out);

		while(begin != end) {
			auto current_code = *begin++;
			std::string current_string;
			if(current_code == table.size()) {
				insert(previous_code, previous_string[0]);
				current_string = fetch(current_code);
			} else {
				current_string = fetch(current_code);
				insert(previous_code, current_string[0]);
			}

			std::copy(current_string.begin(), current_string.end(), out);

			previous_code = current_code;
			previous_string = current_string;
		}
	}

private:
	// Code, refereert terug, zodat je je prefix kan schrijven
	struct Code {
		unsigned int prefix;
		char character;
	};

	// lijst van codes (gevuld vanaf 0), een 'Code lijst[4096]' zou ook werken
	std::vector<Code> table;

	// zoek de string bij een code
	std::string fetch(unsigned int code) {
		std::string output;
		auto current_code = table.at(code);
		output += current_code.character;
		while(current_code.prefix != (unsigned int)-1) {
			current_code = table[current_code.prefix];
			output += current_code.character;
		}

		std::reverse(output.begin(), output.end());
		return output;
	}

	// voeg toe, heel simpel
	void insert(unsigned int previous_code, char character) {
		table.push_back((Code) {previous_code, character});
	}
};

// decomprimeert alles tussen begin en end, schrijft weg naar out
template <typename IteratorType, typename OutputIteratorType>
void decompress(IteratorType begin, IteratorType end, OutputIteratorType out){
	Decompressor decompressor;
	decompressor.decompress(begin, end, out);
}

}


#endif // JN_DECOMPRESSOR_H
