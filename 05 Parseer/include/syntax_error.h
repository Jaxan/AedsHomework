// Nick Overdijk	3029832
// Joshua Moerman	3009408

#ifndef SYNTAX_ERROR_H
#define SYNTAX_ERROR_H

#include <stdexcept>

namespace JN {

/**
    Mooie exception
 */
class syntax_error : public std::runtime_error {
public:
	syntax_error(const std::string& string) : std::runtime_error("Syntax error: " + string) {}
};

}

#endif // SYNTAX_ERROR_H
