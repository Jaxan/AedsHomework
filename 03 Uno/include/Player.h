#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include "Card.h"
#include "List.h"

class Player {
public:
	Player() {}
	virtual ~Player() {}

	void prompt() {
		std::cout << hand << std::endl;
		std::cout << "Speel deze kaart [1.." << hand.size() << "]: ";
		std::cin >> choice;
	}

	void makeChoice (const JN::List<Card> &currentStack) {
		auto topCard = *currentStack.begin();

		for (size_t i = 0, auto it = hand.begin(); it != hand.end(); ++it, ++i) {
			if (it->fitsOn (top) ) {
				choice = i;
				break;
			}
		}

		choice = 0;
	}

	void play() {
		Card cardToPlay = hand[choice-1];
		if (!cardToPlay.fitsOn (game->dumpStack[0]) ) {
			hand.push_front (game->uberStack.pop_front() );

			Card extra = hand[0];
			if (extra.fitsOn (game->dumpStack[0]) ) {
				game->dumpStack.push_front (hand.pop_front() );
			}
		}
	}


	size_t choice;

	JN::List<Card> hand;
};

#endif // PLAYER_H
