// Nick Overdijk	3029832
// Joshua Moerman	3009408

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <limits>
#include <algorithm>

#include "Card.h"
#include "List.h"

class Game;

class Player {
public:
	Player(std::string name) : name(name) {}
	void setStacks(JN::List<Card>& uberStack_, JN::List<Card>& dumpStack_){
		uberStack = &uberStack_;
		dumpStack = &dumpStack_;
	}


	void prompt() {
		std::cout << hand << std::endl;
		std::cout << "Speel deze kaart [1.." << hand.size() << "]: ";
		while (!(std::cin >> choice)){
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "doe ff normaal" << std::endl;
		}
		--choice;
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
		if ( choice >= hand.size() ) {					// dit is niet mijn keuze, vriend
			choice = 0;
		}

		Card cardToPlay = hand[choice];
		if (!cardToPlay.fitsOn ((*dumpStack)[0]) ) {	// oei kan niet spelen
			hand.push_front (uberStack->pop_front() );	// kaart pakken

			std::cout << name << " moest een kaart pakken: " << hand[0] << std::endl;

			Card extra = hand[0];
			if (extra.fitsOn ((*dumpStack)[0]) ) {		// mag ik die kaart leggen, plz ?
				std::cout << name << " kon meteen die kaart opleggen!" << std::endl;
				dumpStack->push_front (hand.pop_front() );
			}
			return;
		}

		dumpStack->push_front(cardToPlay);
		auto it = hand.begin();
		std::advance(it, choice);		// iterator vinden tot element
		hand.erase(it);
	}

	void pick(unsigned int n) {
		while(n--) hand.push_front(uberStack->pop_front());
	}

	std::string name;
	size_t choice;
	JN::List<Card> hand;

	private:
	JN::List<Card> * uberStack;
	JN::List<Card> * dumpStack;
};


#endif // PLAYER_H
