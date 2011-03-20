// Nick Overdijk	3029832
// Joshua Moerman	3009408

#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <map>
#include <vector>
#include <stdexcept>

#include "tokenizor.h"
#include "grammar.h"
#include "arithmetic.h"
#include "logic.h"


/**
    De parser, was misschien mooier als groepje functies.
    Maar de iterator kan wel als state gezien worden.
 */
template <typename InputIterator>
struct parser {
	typedef std::string ID_t;
	typedef bool T;
	typedef node<ID_t, T> node_t;
	typedef sequent<ID_t, T> sequent_t;

    /** Maak de parser, met een bron (iterator) */
	parser(InputIterator is) : is(is) {}

    /** parseer je bron */
	sequent_t* parse(){
		root = parse_sequent();

		// TODO: werkt louter op istream::iterator. Life sucks.
		if(is != InputIterator()){
			throw JN::syntax_error("End of stream expected");
		}

		return root;
	}

    /**
        Zie grammar.h voor de opbouw van de volgende functies:
        de naamgeving spreekt voor zich.
     */
	sequent_t* parse_sequent(){
		std::vector<node_t*> lh;
		//NOTE: Geval van een lege links lijst
		if(is->type != token_t::sequent){
			lh = parse_list();
		}

		auto current_token = *is;
		if(current_token.type == token_t::sequent){
			++is;
			auto rh = parse_list();
			return new sequent<ID_t, T>(lh, rh);
		} else {
			throw JN::syntax_error("Expected sequent token");
		}
	}

	std::vector<node_t*> parse_list(){
		auto first = parse_form();

		auto current_token = *is;
		if(current_token.type == token_t::comma){
			++is;
			auto rest = parse_list();
			rest.push_back(first);
			return rest;
		} else {
			return std::vector<node_t*>{first};
		}
	}

	node_t* parse_form(){
		auto lh = parse_basic();

		auto current_token = *is;
		if(current_token.type == token_t::binary_operator){
			++is;
			auto output = new binary_operator_node<ID_t, T>(current_token.b_op);
			output->left = lh;
			output->right = parse_form();
			return output;
		} else {
			return lh;
		}
	}

	node_t* parse_basic(){
		auto current_token = *is++;

		switch(current_token.type){
			case token_t::basic:
				return new leaf<ID_t>(current_token.string);
			case token_t::unary_operator: {
				auto output = new unary_operator_node<ID_t, T>(current_token.u_op);
				output->child = parse_basic();
				return output;
			}
			case token_t::open: {
				auto form = parse_form();
				if(is->type == token_t::close){
					++is;
					return form;
				} else {
					throw JN::syntax_error("no matching )");
				}
			}
			default:
				throw JN::syntax_error("expected basic");
		}

	}

	sequent_t* root;
	InputIterator is;
};
#endif // PARSER_H
