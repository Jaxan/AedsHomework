#ifndef LOGIC_H
#define LOGIC_H

#include <map>
#include <string>
#include <stdexcept>
#include <sstream>

#include "arithmetic.h"

template <typename ID_t = std::string, typename T = bool>
struct node {
	virtual T pwn(std::map<ID_t, T> const& evaluation) = 0;
};

template <typename ID_t = std::string, typename T = bool>
struct leaf : public node<T> {
	leaf(ID_t id) : id(id) {}

	virtual T pwn(std::map<ID_t, T> const& evaluation) {
		auto it = evaluation.find(id);

		if(it == evaluation.end()) {
			std::stringstream message;
			message << "Couldn't find value for id(" << id << ")";
			throw std::logic_error(message.str());
		}

		return *it;
	}

	ID_t const id;
};

template <typename ID_t = std::string, typename T = bool>
struct binary_operator_node : public node<T> {
	binary_operator_node(binary_operator_t op) : op(op) {}

	virtual T pwn(std::map<ID_t, T> const& evaluation) {
		T left_value = left->pwn(evaluation);
		T right_value = right->pwn(evaluation);

		switch(op) {
			// uit het dictaat van Wim Veldman :)
		case binary_operator_t::operator_and: return std::min(left_value, right_value);
		case binary_operator_t::operator_or: return std::max(left_value, right_value);
		case binary_operator_t::operator_implication:
			if(left_value <= right_value) return JN::one<T>();
			else return right_value;
		default: throw std::logic_error("Corrupted binary operator");
		}
	}

	binary_operator_t op;
	node<ID_t, T> * left;
	node<ID_t, T>* right;
};

template <typename ID_t = std::string, typename T = bool>
struct unary_operator_node : public node<T> {
	unary_operator_node(unary_operator_t op) : op(op) {}

	virtual T pwn(std::map<ID_t, T> const& evaluation) {
		T value = child->pwn(evaluation);
		switch(op) {
		case unary_operator_t::operator_not:
			if(value == JN::zero<T>()) return JN::one<T>();
			else return JN::zero<T>();
		default: throw std::logic_error("Corrupted unary operator");
		}
	}

	unary_operator_t  op;
	node<ID_t, T>* child;
};

template <typename ID_t = std::string, typename T = bool>
struct sequent {
	node<ID_t, T> * left;
	node<ID_t, T>* right;
};

#endif // LOGIC_H
