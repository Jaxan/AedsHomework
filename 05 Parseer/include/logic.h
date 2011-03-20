#ifndef LOGIC_H
#define LOGIC_H

#include <map>
#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>
#include <algorithm>

#include "arithmetic.h"

template <typename ID_t = std::string, typename T = bool>
struct node {
	virtual T pwn(std::map<ID_t, T> const& evaluation) = 0;

	virtual void output(std::ostream& out, unsigned int level = 0) = 0;

	virtual ~node() {};
};

template <typename ID_t = std::string, typename T = bool>
struct leaf : public node<ID_t, T> {
	leaf(ID_t id) : id(id) {}

	virtual T pwn(std::map<ID_t, T> const& evaluation) {
		auto it = evaluation.find(id);

		if(it == evaluation.end()) {
			std::stringstream message;
			message << "Couldn't find value for id(" << id << ")";
			throw std::logic_error(message.str());
		}

		return it->second;
	}

	virtual void output(std::ostream& out, unsigned int level){
		while(level--) out << "  ";
		out << id << '\n';
	}

	ID_t const id;
};

template <typename ID_t = std::string, typename T = bool>
struct binary_operator_node : public node<ID_t, T> {
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

	virtual void output(std::ostream& out, unsigned int level){
		auto higher_level = level + 1;
		left->output(out, higher_level);
		while(level--) out << "  ";
		out << op << '\n';
		right->output(out, higher_level);
	}

	binary_operator_t op;
	node<ID_t, T> * left;
	node<ID_t, T>* right;
};

template <typename ID_t = std::string, typename T = bool>
struct unary_operator_node : public node<ID_t, T> {
	unary_operator_node(unary_operator_t op) : op(op) {
		switch(op){
			case unary_operator_t::operator_not:
			break;

			default: throw std::logic_error("Corrupted unary operator");
		}
	}

	virtual T pwn(std::map<ID_t, T> const& evaluation) {
		T value = child->pwn(evaluation);
		switch(op) {
		case unary_operator_t::operator_not:
			if(value == JN::zero<T>()) return JN::one<T>();
			else return JN::zero<T>();
		default: throw std::logic_error("Corrupted unary operator");
		}
	}

	virtual void output(std::ostream& out, unsigned int level){
		auto higher_level = level + 1;
		while(level--) out << "  ";\
		if(dynamic_cast<leaf<ID_t, T>*>(child) != 0) {
			out << op;
			child->output(out, 0);
		} else {
			out << op << '\n';
			child->output(out, higher_level);
		}
	}

	unary_operator_t  op;
	node<ID_t, T>* child;
};

template <typename ID_t = std::string, typename T = bool>
struct sequent {
	typedef node<ID_t, T> node_t;
	sequent(std::vector<node_t*> lh, std::vector<node_t*> rh) : left(lh), right(rh) {}

	std::vector<node_t*>  left;
	std::vector<node_t*> right;
};

template <typename ID_t = std::string, typename T = bool>
std::ostream& operator<<(std::ostream& os, const sequent<ID_t, T>& x){
	os << "Left:\n";
	std::for_each(x.left.begin(), x.left.end(), [&](node<ID_t, T>*x) { x->output(os, 1); });
	os << "Right:\n";
	std::for_each(x.right.begin(), x.right.end(), [&](node<ID_t, T>*x) { x->output(os, 1); });

	return os;
}

#endif // LOGIC_H