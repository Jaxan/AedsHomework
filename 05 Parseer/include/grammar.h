// Nick Overdijk	3029832
// Joshua Moerman	3009408

#ifndef GRAMMAR_H
#define GRAMMAR_H

/**
	grammatica:

	UOp		:==	~											unaire voegtekens
	BOp		:==	/\ | \/ | ->								voegtekens (connectieven)
	Bas		:==	[a..Z] | (Form)								een mooie naam. Net zoals in het voorbeeld, ook iets met haakjes
	Form	:== Bas | Form BOp Form | UOp Form		 		inductieve opbouw naar formules
	List	:== Form , List | Form                          lijstje formules (nooit leeg)
	Seq		:==	List . List	| e . List						een sequent (rechts niks hebben staan slaat nergens op)


	Om links recursie te vermijden, omgeschreven tot:

	UOP		:==	~
	BOp		:==	/\ | \/ | ->
	Form	:==	Bas Rest
	Rest	:==	BOp Form | e
	Bas		:==	[a..Z] | UOp Bas | (Form)
	List	:== Form , List | Form
	Seq		:==	List . List | e . List
*/

/**
    Types:
 */
enum class token_t {
	unary_operator,
	binary_operator,
	basic,
	sequent,
	comma,
	open,
	close
};

enum class binary_operator_t {
	operator_and,
	operator_or,
	operator_implication
};

enum class unary_operator_t {
	operator_not
};

/**
    Output functies:
 */
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

std::ostream& operator<<(std::ostream& os, const binary_operator_t& x){
	switch(x){
		case binary_operator_t::operator_and: os << "/\\"; break;
		case binary_operator_t::operator_or: os << "\\/"; break;
		case binary_operator_t::operator_implication: os << "->"; break;
		default: throw std::logic_error("Corrupted binary operator");
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, const unary_operator_t& x){
	switch(x){
		case unary_operator_t::operator_not: os << "~"; break;
		default: throw std::logic_error("Corrupted unary operator");
	}
	return os;
}

#endif // GRAMMAR_H
