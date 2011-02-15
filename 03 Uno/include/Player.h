#ifndef PLAYER_H
#define PLAYER_H

#include "include/List.h"

class Player
{
    public:
        Player() {}
        virtual ~Player() {}

        void prompt(){
            std::cout << "Speel deze kaart [1.." << hand.size() << "]: ";
            std::cin >> choice;
        }

        void makeChoice(const JN::List<Card> &currentStack){
            for(auto it = hand.begin(); it != hand.end(); ++it){
                if(it->
            }
        }

        void play(){
			Card cardToPlay = hand[choice-1];
			if (!cardToPlay.fitsOn(game->dumpStack[0])) {
				hand.push_front(game->uberStack.pop_front());

				Card extra = hand[0];
				if(extra.fitsOn(game->dumpStack[0])) {
					game->dumpStack.push_front(hand.pop_front());
				}
			}
        }


        size_t choice;

        JN::List<Card> hand;
};

#endif // PLAYER_H
