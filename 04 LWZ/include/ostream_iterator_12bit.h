#ifndef JN_OSTREAM_ITERATOR_12BIT_H
#define JN_OSTREAM_ITERATOR_12BIT_H

#include <iterator>
#include <iostream>

namespace JN {

// iets met 24 bits
struct icosatetrit {
	// 2x iets met 12bits
	unsigned int first_dodecit : 12;
	unsigned int second_dodecit : 12;
};

std::ostream& operator<< (std::ostream &os, const icosatetrit &x){
	const char * bytes = reinterpret_cast<const char*>(&x);
	os << bytes[0] << bytes[1] << bytes[2];

	return os;
}

template < class T, class charT = char, class traits = std::char_traits<charT>>
class ostream_iterator_12bit : public std::iterator<std::output_iterator_tag, void, void, void, void> {
public:
	typedef charT char_type;
	typedef traits traits_type;
	typedef std::basic_ostream<charT, traits> ostream_type;

	ostream_iterator_12bit (ostream_type& s) : out_stream (&s), data({0, 0}), second_half(false) {}
	~ostream_iterator_12bit() {}

	ostream_iterator_12bit<T, charT, traits>& operator= (const T& value) {
		if (second_half) {
			data.second_dodecit = value;
			*out_stream << data;
		} else {
			data.first_dodecit = value;
		}

		second_half = !second_half;
		return *this;
	}

	ostream_iterator_12bit<T, charT, traits>& operator*() { return *this; }
	ostream_iterator_12bit<T, charT, traits>& operator++() { return *this; }
	ostream_iterator_12bit<T, charT, traits>& operator++(int) { return *this; }

private:
	ostream_type* out_stream;
	icosatetrit data;
	bool second_half;
};

}

#endif // JN_OSTREAM_ITERATOR_12BIT_H
