#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <algorithm>

#include "Card.h"
#include "List.h"

class Game;

class Player {
public:
	Player() {}
	void setStacks(JN::List<Card>& uberStack_, JN::List<Card>& dumpStack_){
		uberStack = &uberStack_;
		dumpStack = &dumpStack_;
	}


	void prompt() {
		std::cout << hand << std::endl;
		std::cout << "Speel deze kaart [1.." << hand.size() << "]: ";
		std::cin >> choice;
	}

	void makeChoice () {
		auto topCard = (*dumpStack)[0];

		size_t i = 0;
		for (auto it = hand.begin(); it != hand.end(); ++it, ++i) {
			if (it->fitsOn (topCard) ) {
				choice = i;
				break;
			}
		}

		choice = 0;
	}

	void play() {
		Card cardToPlay = hand[choice-1];
		if (!cardToPlay.fitsOn ((*dumpStack)[0]) ) {	// oei kan niet spelen
			hand.push_front (uberStack->pop_front() );	// kaart pakken

			Card extra = hand[0];
			if (extra.fitsOn ((*dumpStack)[0]) ) {		// mag ik die kaart leggen, plz ?
				std::cout << "Kon meteen een kaart opleggen: " << extra << std::endl;
				dumpStack->push_front (hand.pop_front() );
			}
			return;
		}

		dumpStack->push_front(cardToPlay);
		auto it = hand.begin();
		std::advance(it, choice-1);		// iterator vinden tot element
		hand.erase(it);
	}

	void pick(unsigned int n) {
		while(n--) hand.push_front(uberStack->pop_front());
	}


	size_t choice;

	JN::List<Card> hand;

	friend std::ostream& operator<< (std::ostream& out, const Player& x);

	private:
	JN::List<Card> * uberStack;
	JN::List<Card> * dumpStack;
};

std::ostream& operator<< (std::ostream& out, const Player& x){
	return (out);// << x.hand);
}

#endif // PLAYER_H
