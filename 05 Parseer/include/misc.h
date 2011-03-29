/*
 *  Misc.h
 *  LeakIndexer
 *
 *  Created by Nick Overdijk on 1/27/11.
 *  Copyright 2011 Nick Overdijk. All rights reserved.
 *
 */

#ifndef MISC_H
#define MISC_H

#include <vector>
#include <string>
#include <cassert>
#include <iostream>
#include <map>

std::vector<std::string> explode( const std::string &delimiter, const std::string &str);

template <typename T>
void output_vector(std::vector<T> const& vec){
	for(typename std::vector<T>::const_iterator it = vec.begin();
		it != vec.end();
		it++){
		std::cout << "\"" + (*it) + "\"" << std::endl;
	}
}

char getline(std::istream &stream, std::string &str, std::string const &delimiters);

char ignoreline(std::istream &stream, std::string const &delimiters);

#pragma mark General output functions

template <typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &x){
	if(x.end() == x.begin()) return os;
	
	const std::string separator = ", ";
	typename std::vector<T>::const_iterator lastElement = x.end();
	--lastElement;
	
	for(typename std::vector<T>::const_iterator it = x.begin(); it != lastElement; it++){
		os << *it << separator;
	}
	os << *lastElement;
	
	return os;
}

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream &os, const std::map<T1, T2> &x){
	if(x.end() == x.begin()) return os;
	
	const std::string separator = ", ";
	typename std::map<T1, T2>::const_iterator lastElement = x.end();
	--lastElement;
	
	for(typename std::map<T1, T2>::const_iterator it = x.begin(); it != lastElement; it++){
		os << *it << separator;
	}
	os << *lastElement;
	
	return os;
}

//template <typename T1, typename T2>
//std::ostream& operator<< <template T1*> (std::ostream &os, const std::pair<T1*, T2> &x){
//	os << "(" << *x.first << ", " << x.second << ")";
//	
//	return os;
//}

template <typename T1, typename T2>
std::ostream& operator<< (std::ostream &os, const std::pair<T1, T2> &x){
	os << "(" << x.first << ", " << x.second << ")";
	
	return os;
}


bool isNotAlphaNumeric (const char c);
bool isNotAlpha (const char c);

#define static_assert(predicate) _static_assert<predicate>()

template <bool predicate> struct _static_assert;

template <> struct _static_assert<true>{};

#endif