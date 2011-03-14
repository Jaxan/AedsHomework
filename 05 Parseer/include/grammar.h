#ifndef GRAMMAR_H
#define GRAMMAR_H

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

enum class binary_operator_t {
	operator_and,
	operator_or,
	operator_implication
};

enum class unary_operator_t {
	operator_not
};

std::ostream& operator<<(std::ostream& os, const token_t& x){
	switch(x){
		case token_t::unary_operator : os << "unary_operator"; break;
		case token_t::binary_operator : os << "binary_operator"; break;
		case token_t::basic : os << "basic"; break;
		case token_t::sequent : os << "sequent"; break;
		default: throw std::logic_error("The world cannot be like this. RAEG!");
	}

	return os;
}

#endif // GRAMMAR_H
