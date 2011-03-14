#ifndef TOKENIZOR_H
#define TOKENIZOR_H

#include <cctype>
#include "syntax_error.h"

/**
	grammatica:

	UOp		:==	~											not
	BOp		:==	/\ | \/ | ->								and, or, implication, iff (all have same precendence)
	Bas		:==	[a..Z]										any string with 'normal' characters
	Form	:== Bas | Form BOp Form | UOp Form | (Form)		a basic formula or a combination of
	Seq		:==	Form . Form									a sequental
*/

enum class token_t {
	unary_operator,
	binary_operator,
	basic,
	sequent
};

struct token {
	std::string string;
	token_t type;
};

std::istream& operator>>(std::istream& is, token& x) {
	char c;
	do {
		is.get(c);
	} while(isspace(c));

	x.string = c;

	switch(c){
		case '/':
			is.get(c);
			if(c!='\\') throw JN::syntax_error("Character " + c " not recognized after " + x.string);
			x.string += c;
			x.type = token_t::binary_operator;
			break;
		case '\\':
			is.get(c);
			if(c!='/') throw JN::syntax_error("Character " + c " not recognized after " + x.string);
			x.string += c;
			x.type = token_t::binary_operator;
			break;
		case '-':
			is.get(c);
			if(c!='>') throw JN::syntax_error("Character " + c " not recognized after " + x.string);
			x.string += c;
			x.type = token_t::binary_operator;
			break;
		case '~':
			x.type = token_t::unary_operator;
			break;
		case '.':
			x.type = token_t::sequent;
			break;
		default:
			if (!isalpha(c)) throw JN::syntax_error("Character not recognized: " + c);
			is.get(c);
			while(isalpha(c)) {
				x.string += c;
				is.get(c);
			}
			is.unget();
			x.type = token_t::basic;
			break;
	}

	return is;
}

#endif // TOKENIZOR_H
