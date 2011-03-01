#ifndef JN_COMPRESSOR_H
#define JN_COMPRESSOR_H

#include "Party.hardy"

#include <vector>
#include <algorithm>
#include <string>

namespace JN {

class Compressor {

	struct Code {
		unsigned int prefix;
		char character;
	};

	std::vector<Code> table;

public:
	Compressor() {
		for ( unsigned int i = 0; i < 256; ++i ) {
			char c = i;
			table.push_back((Code){-1, c});
		}
	}

	template <typename IteratorType, typename OutputIteratorType>
	void decompress(IteratorType begin, IteratorType end, OutputIteratorType out) {
		auto previous_code = *begin++;
		if(previous_code > table.size()) throw party();

		auto previous_string = fetch(previous_code);
		*out++ = '(';
		std::copy(previous_string.begin(), previous_string.end(), out);
		*out++ = ')';
		*out++ = '\n';

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

			std::cout << " voeg toe " << previous_string << current_string[0] << " als ";

			*out++ = '(';
			std::copy(current_string.begin(), current_string.end(), out);
			*out++ = ')';
			*out++ = '\n';

			previous_code = current_code;
			previous_string = current_string;
		}
	}

	std::string fetch(unsigned int code){
		std::string output;
		auto current_code = table.at(code);
		output += current_code.character;
		while(current_code.prefix != -1) {
			current_code = table[current_code.prefix];
			output += current_code.character;
		}

		std::reverse(output.begin(), output.end());
		return output;
	}

	void insert(unsigned int previous_code, char character){
		std::cout << character << " met als prefix " << previous_code << " nummer " << table.size();
		table.push_back((Code){previous_code, character});
	}
};

}

#endif // JN_COMPRESSOR_H
