#ifndef JN_OSTREAM_ITERATOR_12BIT_H
#define JN_OSTREAM_ITERATOR_12BIT_H

#include <iterator>
#include <iostream>
#include <iomanip>
#include "types.h"
#include "Party.hardy"

namespace JN {

template < class T, class charT = char, class traits = std::char_traits<charT > >
class ostream_iterator_12bit : public std::iterator<std::output_iterator_tag, void, void, void, void> {
public:
	typedef charT char_type;
	typedef traits traits_type;
	typedef std::basic_ostream<charT, traits> ostream_type;

	ostream_iterator_12bit(ostream_type& s) : out_stream(&s), data( {0, 0}), second_half(false) {}
	ostream_iterator_12bit(const ostream_iterator_12bit<T>&) : out_stream(0), data( {0, 0}), second_half(false) { throw party(std::string("JN::")+ __func__ +": copy not allowed"); }
	~ostream_iterator_12bit() {
		if(second_half) {
			this->operator= (0);
		}
	}

	ostream_iterator_12bit<T, charT, traits>& operator= (const T& value) {
		if(second_half) {
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
	ostream_iterator_12bit<T, charT, traits>& operator++ (int) { return *this; }

	ostream_iterator_12bit<T, charT, traits>& operator=(const ostream_iterator_12bit<T>&) {
		throw party();
	}

private:
	ostream_type* out_stream;
	icosatetrit data;
	bool second_half;
};

}

#endif // JN_OSTREAM_ITERATOR_12BIT_H
