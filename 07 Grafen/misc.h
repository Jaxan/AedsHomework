// Nick Overdijk	3029832
// Joshua Moerman	3009408

#ifndef MISC_H
#define MISC_H

#include <map>
#include <iostream>

template <typename KeyType, typename ValueType>
std::ostream& operator<<(std::ostream &os, const std::map<KeyType, ValueType> &x){
	if(x.empty()){
		os << "{ Empty map }";
		return os;
	}

	os << '{';
	for(auto it = x.begin(); it != x.end(); it++){
		os << it->first << " => " << it->second << ", ";
	}
	os << '}';

	return os;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &x){
	os << '{';

	auto it = x.begin();
	os << *it++;
	for(; it != x.end(); it++){
		os << " " << *it;
	}
	os << '}';

	return os;
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const std::set<T> &x){
	os << '{';

	auto it = x.begin();
	os << *it++;
	for(; it != x.end(); it++){
		os << " " << *it;
	}
	os << '}';

	return os;
}

#endif // MISC_H
