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
	virtual T pwn(std::map<ID_t, T> const& evaluation) const = 0;

    /** Print de boom, level geeft indenting aan */
	virtual void output(std::ostream& out, unsigned int level = 0) const = 0;

	//We return a list of options
	// An option is a pair
	//  with in  first what node_t*s go on the left
	//  with in second what node_t*s go on the right
	typedef node<ID_t, T> node_t;
	virtual std::vector<std::pair<std::vector<node_t*>, std::vector<node_t*>>> reduce(bool left) const = 0;

    /** en natuurlijk de destructor, besteden we geen aandacht aan */
	virtual ~node() {};
};


/** aka basisformule */
template <typename ID_t = std::string, typename T = bool>
struct leaf : public node<ID_t, T> {
	typedef node<ID_t, T> node_t;
	leaf(ID_t id) : id(id) {}

	virtual T pwn(std::map<ID_t, T> const& evaluation) const {
		auto it = evaluation.find(id);

		if(it == evaluation.end()) {
			std::stringstream message;
			message << "Couldn't find value for id(" << id << ")";
			throw std::logic_error(message.str());
		}

		return it->second;
	}

	virtual std::vector<std::pair<std::vector<node_t*>, std::vector<node_t*>>> reduce(bool left) const {
		return std::vector<std::pair<std::vector<node_t*>, std::vector<node_t*>>>{};
	}

	virtual void output(std::ostream& out, unsigned int level) const {
		while(level--) out << "  ";
		out << id << '\n';
	}

	ID_t const id;
};


template <typename ID_t = std::string, typename T = bool>
struct binary_operator_node : public node<ID_t, T> {
	typedef node<ID_t, T> node_t;

	binary_operator_node(binary_operator_t op) : op(op) {}

	virtual T pwn(std::map<ID_t, T> const& evaluation) const {
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

	virtual std::vector<std::pair<std::vector<node_t*>, std::vector<node_t*>>> reduce(bool left) const {
		typedef std::vector<node_t*> NodeList;
		typedef std::pair<NodeList, NodeList> ReturnOption;
		typedef std::vector<ReturnOption> ReturnType;

		switch(op) {
		case binary_operator_t::operator_and:
			if(left){
//				This doesn't work for some reason.
//				NodeList a = NodeList{left, right};
//				NodeList b = NodeList{};
//				ReturnOption c = std::make_pair(a, b);
//				ReturnType d = {c};
//				return d;
			} else {
				return ReturnType{
					ReturnOption(NodeList{}, NodeList{left}),
					ReturnOption(NodeList{}, NodeList{right})
				};
			}
		case binary_operator_t::operator_or:
			if(left){

			} else {

			}

		case binary_operator_t::operator_implication:
			if(left){

			} else {

			}

		default: throw std::logic_error("Corrupted binary operator");
		}
	}

	virtual void output(std::ostream& out, unsigned int level) const {
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
	typedef node<ID_t, T> node_t;

	unary_operator_node(unary_operator_t op) : op(op) {
		switch(op){
			case unary_operator_t::operator_not:
			break;

			default: throw std::logic_error("Corrupted unary operator");
		}
	}

	virtual T pwn(std::map<ID_t, T> const& evaluation) const {
		T value = child->pwn(evaluation);
		switch(op) {
		case unary_operator_t::operator_not:
			if(value == JN::zero<T>()) return JN::one<T>();
			else return JN::zero<T>();
		default: throw std::logic_error("Corrupted unary operator");
		}
	}

	virtual std::vector<std::pair<std::vector<node_t*>, std::vector<node_t*>>> reduce(bool left) const {
		return std::vector<std::pair<std::vector<node_t*>, std::vector<node_t*>>>{};
	}

	virtual void output(std::ostream& out, unsigned int level) const {
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
	bool closed() const {
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
	bool open() const {
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
template <typename ID_t, typename T>
std::map<ID_t, T> const& counterexample(sequent<ID_t, T> const& seq){
	typedef node<ID_t, T> node_t;

	std::queue<sequent<ID_t, T>> sequents_to_examine;
	sequents_to_examine.push(seq);

	//While there are still sequents that may be expanded (i.e. are not closed or open)
	while(!sequents_to_examine.empty()){
		auto& current_sequent = sequents_to_examine.front();

		//For every seperate (i.e. comma seperated) value on the left, reduce it
		for(auto it = current_sequent.left.begin(); it != current_sequent.left.end(); ++it){
			//If it's a basic, we can't reduce it.
			node_t const* current_node;
			if(typeid(*current_node) == typeid(leaf<ID_t, T>)) continue;

			//Get every reduction option for the first node
			auto options = current_node->reduce(true);
			if(options.size() == 0){
				throw std::runtime_error("reduce() didn't give any options, and it wasn't a basic.");
			}

			//The new sequent is a copy of the current sequent without the current node (which is reduced)
			auto new_sequent = current_sequent;
			new_sequent.left.erase(it);

			//A function for adding the options given by the reduce() function of the node
			auto add_options = [](std::pair<std::vector<node_t*>, std::vector<node_t*>> const& option, sequent<ID_t, T>& sequent){
				std::for_each(option.first.begin(), option.first.end(), [&](node_t* x) {sequent.left.push_back(x);});
				std::for_each(option.second.begin(), option.second.end(), [&](node_t* x) {sequent.right.push_back(x);});
			};

			//Add options to the new sequent
			add_options(options[0], new_sequent);
			std::cout << new_sequent;
			sequents_to_examine.push(new_sequent);

			//Some reductions give 2 branches, here we handle that case, by copying the sequent again and applying the second option
			if(options.size() > 1){
				auto another_new_sequent = current_sequent;
				add_options(options[0], another_new_sequent);
				std::cout << another_new_sequent;
				sequents_to_examine.push(another_new_sequent);
			}
		}

//		Do the same for right, but pass "false" to the reduce() function of the node.
//		for(auto it = current_sequent.right.begin(); it != current_sequent.right.end(); ++it){
//		}

	}


}


#endif // LOGIC_H
