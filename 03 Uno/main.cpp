#include <iostream>
#include <vector>

#include "include/List.h"
#include "include/Card.h"

template <typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& x) {
	std::copy(x.cbegin(), x.cend(), std::ostream_iterator<T>(out, " "));
}

int main(int argc, char* argv[]) {

	try {
		JN::List<Card> uberStack;
		for(size_t i = 0; i <= 12; ++i){	// de getallen + 3 speciale kaarten (van elke kleur 2 stuks)
		    {Card card(Card::Yellow, i);
            uberStack.push(card);
            uberStack.push(card);}
		    {Card card(Card::Green, i);
            uberStack.push(card);
            uberStack.push(card);}
		    {Card card(Card::Red, i);
            uberStack.push(card);
            uberStack.push(card);}
		    {Card card(Card::Blue, i);
            uberStack.push(card);
            uberStack.push(card);}
		}
		{
			Card choice(Card::Choice);
			for(size_t i = 0; i < 4; ++i) uberStack.push(choice);
			Card choicePick4(Card::ChoicePick4);
			for(size_t i = 0; i < 4; ++i) uberStack.push(choicePick4);
		}

        std::cout << "De random stapel: " << uberStack << std::endl;

        /*std::cout << "De nette stapel met iterator: " << std::endl;
        for (auto it = s[2].begin(); it != s[2].end(); ++it)
            std::cout << *it << "; ";
        std::cout << std::endl;

        auto it = s[2].begin();
        std::cout << "removing: " << std::endl;
        for (auto it = s[2].begin(); it != s[2].end(); ++it) {
            static size_t i = 0;
            Card card = *it;
            if (i++ % 2){
                it.remove();
                std::cout << card << "; ";
            }
         }
        std::cout << std::endl;
        std::cout << "De nette stapel bevat nu nog: " << s[2] << std::endl;
        */

		return 0;
	} catch(std::exception& e) {
		std::cerr << e.what() << std::endl;
	} catch(...) {
#define wtf {std::cerr << "WAAAAAAAAAARRRRRRRGHHHHHHHHHHHHHHHHHNOWAI" << std::endl;};;;;;;;;;;
		wtf;
	}
}
