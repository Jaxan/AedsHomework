#ifndef PLAYER_H
#define PLAYER_H

#include "include/List.h"

class Player
{
    public:
        Player() {}
        virtual ~Player() {}

        void prompt(){
            std::cout << "Speel deze kaart: ";
            std::cin >> choice;
        }

        void makeChoice(const JN::List<Card> &currentStack){
            for(auto it = hand.begin(); it != hand.end(); ++it){
                if(it->
            }
        }

        void play(){


        size_t choice;

        JN::List<Card> hand;
};

#endif // PLAYER_H
