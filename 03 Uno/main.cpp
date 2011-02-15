#include <iostream>
#include <vector>

#include "include/List.h"

template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& x) {
	std::copy(x.cbegin(), x.cend(), std::ostream_iterator<T>(out, " "));
}

int main(int argc, char* argv[]) {
	try {
		JN::List<Card> s[3];
		for(size_t i = 0; i < 10; ++i){
		    Card card(Card::Yellow, i);
            s[0].push(card);
            s[1].push_front(card);
            s[2].push_back(card);
		}

		Card card(Card::Choice);

        s[0].push(card);
        s[1].push_front(card);
        s[2].push_back(card);

        std::cout << "De random stapel: " << s[0] << std::endl;
        std::cout << "De omgekeerde stapel: " << s[1] << std::endl;
        std::cout << "De nette stapel: " << s[2] << std::endl;

        std::cout << "De nette stapel met iterator: " << std::endl;
        for (auto it = s[2].begin(); it != s[2].end(); ++it)
            std::cout << *it << "; ";
        std::cout << std::endl;

        auto it = stapel3.iterator();
        std::cout << "removing: " << std::endl;
        for (auto it = s[2].begin(); it != s[2].end(); ++it) {
            static size_t i = 0;
            Card card = *it;
            if (i++ % 2){
                it.remove();
                std::cout << k2 << "; ";
            }
         }
        std::cout << std::endl;
        std::cout << "De nette stapel bevat nu nog: " << stapel3 << std::endl;

		return 0;
	} catch(std::exception& e) {
		std::cerr << e.what() << std::endl;
	} catch(...) {
#define wtf {std::cerr << "WAAAAAAAAAARRRRRRRGHHHHHHHHHHHHHHHHHNOWAI" << std::endl;};;;;;;;;;;
		wtf;
	}
}
