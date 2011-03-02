#ifndef JN_TYPES_H
#define JN_TYPES_H

namespace JN {

// iets met 24 bits
struct icosatetrit {
	// 2x iets met 12bits, handig
	unsigned int first_dodecit : 12;
	unsigned int second_dodecit : 12;
};

std::ostream& operator<< (std::ostream& os, const icosatetrit& x) {
	uint32_t shift = x.first_dodecit | x.second_dodecit << 12;
	const char* bytes = reinterpret_cast<const char*>(&shift);
	os.write(bytes, 3);

	return os;
}

std::istream& operator>> (std::istream& is, icosatetrit& x) {
	uint32_t shift = 0;
	char* bytes = reinterpret_cast<char*>(&shift);
	is.read(bytes, 3);

	x.first_dodecit = shift;
	x.second_dodecit = shift >> 12;

	return is;
}

}

#endif // JN_TYPES_H
