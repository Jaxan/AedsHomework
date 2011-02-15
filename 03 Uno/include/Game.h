#ifndef GAME_H
#define GAME_H

#include "List.h"
#include "Player.h"

class Game {
public:
	Game() {
		for(size_t i = 0; i <= 12; ++i) {	// de getallen + 3 speciale kaarten (van elke kleur 2 stuks)
			{
				Card card(Card::Yellow, i);
				uberStack.push(card);
				uberStack.push(card);
			}
			{
				Card card(Card::Green, i);
				uberStack.push(card);
				uberStack.push(card);
			}
			{
				Card card(Card::Red, i);
				uberStack.push(card);
				uberStack.push(card);
			}
			{
				Card card(Card::Blue, i);
				uberStack.push(card);
				uberStack.push(card);
			}
		}
		{
			Card choice(Card::Choice);
			for(size_t i = 0; i < 4; ++i) uberStack.push(choice);
			Card choicePick4(Card::ChoicePick4);
			for(size_t i = 0; i < 4; ++i) uberStack.push(choicePick4);
		}

        dumpStack.push_front(uberStack.pop_front());
		std::cout << "De pakstapel: " << uberStack << std::endl;
		std::cout << "De dump: " << dumpStack << std::endl;

		play();
	}

	virtual ~Game() {}

	friend std::ostream& operator<< (std::ostream& out, const Game& x);

	void play(){
	    Player * currentPlayer = &person;
	    while(!gameOver()){
	        std::cout << dumpStack[0] << std::endl;

	        if(currentPlayer == &person){
	            currentPlayer->prompt();
	        } else {
	            currentPlayer->makeChoice(uberStack);
	        }

	        currentPlayer->play();

	        togglePlayer();

            switch(dumpStack[0]->value){
                case Card::Value::Skip:
                togglePlayer();
                break;

                case Card::Value::Pick2:
                currentPlayer->pick(2);
                break;

                case Card::Value::Turn:
                default:
                break;
            }
	    }
	}

	void togglePlayer(){
        currentPlayer = (currentPlayer == &person) computer : person;
    }


	bool gameOver() {
		return (computer.hand.empty() || person.hand.empty());
	}

	Player computer;
	Player person;

    JN::List<Card> dumpStack;
	JN::List<Card> uberStack;
};

std::ostream& operator<<(std::ostream& out, const Game& x) {
	out << "NPC: " << computer << '\n';
	out << "PC: " << person << '\n';
	out << "Kaartjens: " << uberStack << '\n';
	return out;
}

#endif // GAME_H
