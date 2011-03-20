// Nick Overdijk	3029832
// Joshua Moerman	3009408

#ifndef LOGIC_H
#define LOGIC_H

#include <map>
#include <vector>
#include <queue>
#include <string>
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <typeinfo>

#include "arithmetic.h"

/**
	Variabelen in formules zijn van het type ID_t (als default string, dus mooie variabelenamen)
	Waarheidswaarden zijn van type T, default bool, maar kan ook ingezet worden bij n-waardige logica.
*/


/**
    interface/abstracte klasse voor nodes (die een formuleboom vormen).
    Zie grammar.h voor onze nodes. naamgeving spreekt voor zich.
 */
template <typename ID_t = std::string, typename T = bool>
struct node {
    /** Evalueer de formule met de waardes van de basis-formules */
	virtual T pwn(std::map<ID_t, T> const& evaluation) = 0;

    /** Print de boom, level geeft indenting aan */
	virtual void output(std::ostream& out, unsigned int level = 0) = 0;

    /** geef alle mogelijke reducties */
	virtual std::vector<std::pair<node<ID_t, T>>> reduce() = 0;

    /** en natuurlijk de destructor, besteden we geen aandacht aan */
	virtual ~node() {};
};


/** aka basisformule */
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
			// uit het dictaat van Wim Veldman :), dus werkt ook met n-waardige logica
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
		if(typeid(leaf<ID_t, T>) == typeid(*child)) {
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


/**
    Een sequent heeft links en rechts een rijtje proposities.
 */
template <typename ID_t = std::string, typename T = bool>
struct sequent {
	typedef node<ID_t, T> node_t;
	sequent(std::vector<node_t*> lh, std::vector<node_t*> rh) : left(lh), right(rh) {}

	/**
		returnt true als de sequent gesloten is, dwz als er links en rechts iets gelijks voorkomt.
	*/
	bool closed(){
		for(auto it = left.begin(); it != left.end(); ++it){
			for(auto it2 = right.begin(); it2 != right.end(); ++it2){
				if(**it == **it2) return true;
			}
		}
		return false;
	}

	/**
		returnt true als de sequent open is, dwz als uit links en rechts makkelijk een tegenvoorbeeld te maken is.
		(neem links true, rechts false)
	*/
	bool open(){
		for(auto it = left.begin(); it != left.end(); ++it)
			if(typeid(**it) != typeid(leaf<ID_t, T>)) return false;
		for(auto it = right.begin(); it != right.end(); ++it)
			if(typeid(**it) != typeid(leaf<ID_t, T>)) return false;
		return !closed();
	}

	std::vector<node_t*>  left;
	std::vector<node_t*> right;
};


/** Output voor een sequent */
template <typename ID_t = std::string, typename T = bool>
std::ostream& operator<<(std::ostream& os, const sequent<ID_t, T>& x){
	os << "Left:\n";
	std::for_each(x.left.begin(), x.left.end(), [&](node<ID_t, T>*x) { x->output(os, 1); });
	os << "Right:\n";
	std::for_each(x.right.begin(), x.right.end(), [&](node<ID_t, T>*x) { x->output(os, 1); });

	return os;
}


/** Vind een tegenvoorbeeld bij een counterexample */
template <typename ID_t, T>
std::map<ID_t, T> const& counterexample(sequent<ID_t, T> const& seq){
	std::queue<sequent<ID_t, T>> sequents_to_examine{seq};

	while(!queue.empty()){
		auto& current_sequent = sequents_to_examine.front();

		for(auto it = current_sequent.left.begin(); it != current_sequent.left.end(); ++it){
			//If it's a basic, we can't reduce it.
			node_t const* current_node;
			if(typeid(*current_node) == typeid(leaf<ID_t, T>)) continue;

			auto options = current_node->reduce();
			if(options.size() == 0){
				throw std::runtime_error("reduce() didn't give any options, and it wasn't a basic.");
			}

			auto new_sequent = current_sequent;
			new_sequent.left.erase(it);

			auto add_options = [](std::pair<node<ID_t, T>> const& option, sequent<ID_t, T>& sequent){
				sequent.left.push_back(option.first);
				sequent.right.push_back(option.second);
			}

			add_options(options[0], new_sequent);

			if(options.size() > 1){
				auto another_new_sequent = current_sequent;
				add_options(options[0], another_new_sequent);
			}
		}

		for(auto it = current_sequent.right.begin(); it != current_sequent.right.end(); ++it){
		}

	}


}


#endif // LOGIC_H
