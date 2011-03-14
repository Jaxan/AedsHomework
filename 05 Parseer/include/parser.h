#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <map>
#include "tokenizor.h"
#include "grammar.h"
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


struct parser {
	parser(std::istream& is) is(is) {
		parse();
	}

	node<std::string, bool>* parse(){
		node<std::string, bool>* root = parse_sequent();

		if(!is){
			throw JN::syntax_error("End of stream expected");
		}

		return root;
	}

	node<std::string, bool>* parse_sequent(){
		node<std::string, bool>* lh = parse_form();
		node<std::string, bool>* rh = 0;

		token current_token;
		is >> current_token;
		if(current_token.type != token_t::sequent){
			return lh;
		} else {
			rh = parse_form();
			return

		}
	}



	std::istream& is;
};

#endif // PARSER_H
