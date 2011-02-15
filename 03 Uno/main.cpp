#include <iostream>
#include <vector>

#include "include/List.h"

template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& x) {
	std::copy(x.cbegin(), x.cend(), std::ostream_iterator<T>(out, " "));
}

int main(int argc, char* argv[]) {
	try {
		JN::List<int> purePwn;
		std::vector<int> pureTest;

		for(size_t i = 0; i < 42; i++) {
			purePwn.push_back(i);
			pureTest.push_back(i);
		}

		std::cout << purePwn << std::endl;
		std::cout << pureTest;

		return 0;
	} catch(std::exception& e) {
		std::cerr << e.what() << std::endl;
	} catch(...) {
#define wtf {std::cerr << "WAAAAAAAAAARRRRRRRGHHHHHHHHHHHHHHHHHNOWAI" << std::endl;};;;;;;;;;;
		wtf;
	}
}
