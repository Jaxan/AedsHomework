#ifndef TOKENIZOR_H
#define TOKENIZOR_H

#include <cctype>
#include "syntax_error.h"
#include "grammar.h"

struct token {
	token_t type;
	std::string string;

	union {
		binary_operator_t b_op;
		unary_operator_t u_op;
	};

	token() : type(), string() {}
};

std::istream& operator>>(std::istream& is, token& x) {
	char c;
	do {
		is.get(c);
		if(!is) return is;
	} while(isspace(c));

	x.string = c;

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
		case '.':
			x.type = token_t::sequent;
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
