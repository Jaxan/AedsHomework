#ifndef JN_ISTREAM_ITERATOR_12BIT_H
#define JN_ISTREAM_ITERATOR_12BIT_H

#include <iterator>
#include <iostream>
#include <iomanip>
#include "types.h"

namespace JN {

template < class T, class charT = char, class traits = std::char_traits<charT>, class Distance = std::ptrdiff_t >
class istream_iterator_12bit : public std::iterator<std::input_iterator_tag, T, Distance, const T*, const T&> {
public:
	typedef charT char_type;
	typedef traits traits_type;
	typedef std::basic_istream<charT, traits> istream_type;

	istream_iterator_12bit() : in_stream(0), data( {0, 0}), second_half(false) { }
	istream_iterator_12bit(istream_type& s) : in_stream(&s), data( {0, 0}), second_half(false) { ++*this; }
	istream_iterator_12bit(const istream_iterator_12bit<T, charT, traits, Distance>& x) : in_stream(x.in_stream), data(x.data), second_half(x.second_half) {}
	~istream_iterator_12bit() {}

	bool operator!= (const istream_iterator_12bit<T, charT, traits, Distance>& x) {
		return !(*this == x);
	}
	bool operator== (const istream_iterator_12bit<T, charT, traits, Distance>& x) {
		return in_stream == x.in_stream;
	}

	const T operator*() const {
		return !second_half ? data.second_dodecit : data.first_dodecit;
	}
	const T* operator->() const {
		return !second_half ? data.second_dodecit : data.first_dodecit;
	}

	istream_iterator_12bit<T, charT, traits, Distance>& operator++() {
		if(!second_half) {
			if(in_stream && !(*in_stream >> data)) {
				in_stream = 0;
			}
		}
		second_half = !second_half;
		return *this;
	}
	istream_iterator_12bit<T, charT, traits, Distance> operator++ (int) {
		istream_iterator_12bit<T, charT, traits, Distance> tmp(*this);
		++*this;
		return tmp;
	}
	istream_iterator_12bit<T, charT, traits, Distance>& operator=(const istream_iterator_12bit<T, charT, traits, Distance>& x) = default;

private:
	istream_type* in_stream;
	icosatetrit data;
	bool second_half;
};

}

#endif // JN_ISTREAM_ITERATOR_12BIT_H
