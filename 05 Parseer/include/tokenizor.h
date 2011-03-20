// Nick Overdijk	3029832
// Joshua Moerman	3009408

#ifndef TOKENIZOR_H
#define TOKENIZOR_H

#include <iostream>
#include <cctype>
#include "syntax_error.h"
#include "grammar.h"

/**
    Een token, zodat we een fijne >> operator kunnen overloaden. Hieruit haalt de parser alle informatie
    zie ook grammar.h
 */
struct token {
	token_t type;
	std::string string;

    // Union, omdat het altijd maar 1 vd 2 is (string mag niet in een union)
	union {
		binary_operator_t b_op;
		unary_operator_t u_op;
	};

	token() : type(), string() {}
	token(token const & x) : type(x.type), string(x.string), b_op(x.b_op) {}
};

/**
    Haal een token uit een istream. (vooral handig met istream_iterator<token>, dan kan je itereren over tokens)
 */
std::istream& operator>>(std::istream& is, token& x) {
	char c;
    // negeer whitespace
	do {
		is.get(c);
		if(!is) return is;
	} while(isspace(c));

	x.string = c;

    // vreselijk grote switchcase, had makkelijk mooier gekund, maar dit werkt.
	switch(c){
		case '/':
			is.get(c);
			if(!is) throw JN::syntax_error(std::string("Expected '\\' after ") + x.string);
			if(c!='\\') throw JN::syntax_error(std::string("Character '") + c + "' not recognized after " + x.string);
			x.string += c;
			x.type = token_t::binary_operator;
			x.b_op = binary_operator_t::operator_and;
			break;
		case '\\':
			is.get(c);
			if(!is) throw JN::syntax_error(std::string("Expected '/' after ") + x.string);
			if(c!='/') throw JN::syntax_error(std::string("Character '") + c + "' not recognized after " + x.string);
			x.string += c;
			x.type = token_t::binary_operator;
			x.b_op = binary_operator_t::operator_and;
			break;
		case '-':
			is.get(c);
			if(!is) throw JN::syntax_error(std::string("Expected '>' after ") + x.string);
			if(c!='>') throw JN::syntax_error(std::string("Character '") + c + "' not recognized after " + x.string);
			x.string += c;
			x.type = token_t::binary_operator;
			x.b_op = binary_operator_t::operator_implication;
			break;
		case '~':
			x.type = token_t::unary_operator;
			x.u_op = unary_operator_t::operator_not;
			break;
		case '(':
			x.type = token_t::open;
			break;
		case ')':
			x.type = token_t::close;
			break;
		case '.':
			x.type = token_t::sequent;
			break;
		case ',':
			x.type = token_t::comma;
			break;
		default:
			if (!isalpha(c)) throw JN::syntax_error(std::string("Character not recognized: '") + c + '\'');
			while(is.get(c) && isalpha(c)) x.string += c;
			is.unget().clear();
			x.type = token_t::basic;
			break;
	}

	return is;
}

#endif // TOKENIZOR_H
