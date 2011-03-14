#ifndef SYNTAX_ERROR_H
#define SYNTAX_ERROR_H

#include <stdexcept>

namespace JN {

class syntax_error : public std::runtime_error {
public:
	syntax_error(const std::string& string) : std::runtime_error("Syntax error: " + string) {}
};

}

#endif // SYNTAX_ERROR_H
