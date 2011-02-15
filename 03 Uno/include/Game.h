#ifndef GAME_H
#define GAME_H

#include "include/List.h"
#include "include/Player.h"

class Game
{
    public:
        Game() {}
        virtual ~Game() {}

        friend std::ostream& operator<< (std::ostream& out, const Game& x);

        bool gameOver(){
            return (computer.hand.empty() || person.hand.empty());
        }

        Player computer;
        Player person;

        JN::List<Card> uberStack;
};

std::ostream& operator<< (std::ostream& out, const Game &x){
    out << "NPC: " << computer << '\n';
    out << "PC: " << person << '\n';
    out << "Kaartjens: " << uberStack << '\n';
}

#endif // GAME_H
