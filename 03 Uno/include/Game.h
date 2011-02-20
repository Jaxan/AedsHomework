// Nick Overdijk	3029832
// Joshua Moerman	3009408

#ifndef GAME_H
#define GAME_H

#include "List.h"
#include "Player.h"

class Game {
public:
	Game() : person("Jij"), computer("Een Turing Machine") {
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

		person.setStacks(uberStack, dumpStack);
		computer.setStacks(uberStack, dumpStack);

		for (unsigned int i = 0; i<7; ++i){
			person.hand.push_front(uberStack.pop_front());
			computer.hand.push_front(uberStack.pop_front());
		}

		std::cout << "Welkom bij UNO deluxe 2000++" << std::endl << std::endl << "Jij mag beginnen :D (met je hoofd)" << std::endl;

		play();
	}

	virtual ~Game() {}

	void play(){
	    currentPlayer = &person;
	    while(!gameOver()){
	        std::cout << "Er lig nu: " << dumpStack[0] << std::endl;

	        if(currentPlayer == &person){
	            currentPlayer->prompt();
	        } else {
	            currentPlayer->makeChoice();
	        }

	        currentPlayer->play();

	        togglePlayer();

            switch(dumpStack[0].getValue()){
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
        currentPlayer = (currentPlayer == &person)? &computer : &person;
        std::cout << std::endl << currentPlayer->name << " gaat doen" << std::endl;
    }


	bool gameOver() {
		return (computer.hand.empty() || person.hand.empty());
	}

	Player computer;
	Player person;

	Player * currentPlayer;

    JN::List<Card> dumpStack;
	JN::List<Card> uberStack;
};

#endif // GAME_H
