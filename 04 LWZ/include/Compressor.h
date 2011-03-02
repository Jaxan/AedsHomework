#ifndef JN_COMPRESSOR_H
#define JN_COMPRESSOR_H

#include "Party.hardy"

#include <vector>
#include <algorithm>
#include <string>

namespace JN {

class Compressor {
public:
	struct Code {
		unsigned int prefix;
		char character;
	};

	std::vector<Code> table;

	Compressor() : table() {
		for(unsigned int i = 0; i < 256; ++i) {
			char c = i;
			table.push_back((Code) {-1, c});
		}
	}

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

	void insert(unsigned int previous_code, char character) {
		table.push_back((Code) {previous_code, character});
	}
};

std::ostream& operator<<(std::ostream& os, const Compressor::Code& x) {
	os << x.character << ", " << x.prefix;
	return os;
}

}


#endif // JN_COMPRESSOR_H
