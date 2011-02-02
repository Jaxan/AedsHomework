#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <limits>
#include <stdexcept>
#include <map>

/*
Nick Overdijk   3029832
Joshua Moerman  3009408
*/


/*
	Algoritmen & Datastrucuren 2011
	Begin van opgave 1

	Pieter koopman, pieter@cs.ru.nl
*/

using namespace std;	// slechte stijl...

class Kamer; 			// forward decleration
typedef map<unsigned int, Kamer*> Map;


class Uitgang {
public:
	Kamer const * nextKamer;
	Uitgang * next;
	std::string sleutel;

	// wij prefereren const als een postfix (zoals c ooit ontworpen is)
	Uitgang (char const * sleutel, Kamer const * nextKamer ) : nextKamer(nextKamer), next(NULL), sleutel(sleutel) {
	}

	void push_back (Uitgang * element) {
		// haha recursief :D
		if ( next == NULL ) {
			next = element;
		} else {
			next->push_back(element);
		}
	}

	Uitgang const * operator[](const unsigned int index) {
		Uitgang const * iterator = this;
		for ( unsigned int i = 0; i < index && iterator != NULL; ++i ) {
			if (iterator->next != NULL) {
				iterator = iterator->next;
			} else {
				throw out_of_range("Ongeldige index");
			}
		}
		return iterator;
	}

};


class Kamer {
public:
	Uitgang * firstUitgang;
	std::string naam;
	std::string beschrijving;
	bool eind;

	// AUW dit (de orginele code) doet pijn, want:
	// 1. c++ 2003 standaard: "Each name that begins with an underscore is reserved to the implementation for use as a name in the global namespace."
	//    Dus ik heb de "_naam" veranderd in "naam" enzo (ja dat werkt)
	// 2. gebruik van "char *" is deprecated ("char const *" of "const char *" moet gebruikt worden)
	//    Dus ik heb op veel plekken const toegevoegd, ook al is std::string eigenlijk mooier...
	// FOEI!
	Kamer (char const * naam, char const * beschrijving, bool eind) : firstUitgang(NULL), naam(naam), beschrijving(beschrijving), eind(eind) {
	}

	void nieuweUitgang (char const _sleutel [], Kamer const * _naar) {
		Uitgang * newUitgang = new Uitgang(_sleutel, _naar);

		if ( firstUitgang == NULL ) {
			firstUitgang = newUitgang;
		} else {
			firstUitgang->push_back(newUitgang);
		}
	}

};


void leesKamers (ifstream& file, Map& kamers) {
	int aantal;
	file >> aantal;

	for (int i=0; i<aantal; i++) {
		int nr;
		file >> nr;

		char is_eind;
		file >> is_eind;

		char newl;
		file.get (newl);

		string naam;
		getline(file, naam);

		string beschr;
		getline(file, beschr);

		cout << nr << " " << is_eind << " " << naam << " " << beschr << endl;

		kamers[nr] = new Kamer(naam.c_str(), beschr.c_str(), is_eind == 'T');
	}
}


void leesUitgangen (ifstream& file, Map kamers) {
	while (true) {
		int van;
		file >> van;

		if (van == -1)
			return;

		int naar;
		file >> naar;

		char sch;
		file.get (sch);

		string beschr;
		getline(file, beschr);

		cout << van << ' ' << naar << ' ' << beschr << endl;
		kamers[van]->nieuweUitgang(beschr.c_str(), kamers[naar]);
	}
}


void interaction(Kamer const & startKamer){
	Kamer const * nextKamer = &startKamer;

	while(true){
		Kamer const & kamer = *nextKamer;

		// geef uitleg
		#ifndef _WIN32
		system("clear");	// werkt niet onder windows?
		#else
		system("cls");
		#endif
		cout << "U bent nu hier: " << kamer.naam << endl;
		cout << kamer.beschrijving << endl << endl;
		if ( kamer.eind ) cout << "HOERA, dit is het einde, uw leven is nu compleet" << endl;

		// geef mogelijkheden
		Uitgang * iterator = kamer.firstUitgang;
		cout << "Waar wilt u heen?" << endl;
		for ( unsigned int i = 1; iterator != NULL; ++i ) {
			cout << i << ". " << iterator->sleutel << endl;
			iterator = iterator->next;
		}

		// vraag om keuze (in de vorm van een int);
		cout << "Maak uw keuze door het getal in te tikken: " << endl;
		int choice;
		while (!(cin >> choice)){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "doe ff normaal" << endl;
		}

		// ga naar die keuze
		Uitgang const * chosenUitgang = (*kamer.firstUitgang)[choice-1];
		nextKamer = chosenUitgang->nextKamer;
	}

}


int main () {
    try {
        Map kamers;

        // Kamers en uitgangangen uit files lezen
        char in_naam1 [] = "kamers.txt";
        char in_naam2 [] = "deuren.txt";
        ifstream kamer_file(in_naam1);
        ifstream uitg_file (in_naam2);

        if (! kamer_file) {
            cout << "Het kamerbestand " << in_naam1 << " kon niet geopend worden.\n";
            return 1;
        }
        if (! uitg_file) {
            cout << "Het uitgangenbestand " << in_naam2 << " kon niet geopend worden.\n";
            return 1;
        }

        leesKamers (kamer_file, kamers);
        leesUitgangen (uitg_file, kamers);

        kamer_file.close ();
        uitg_file.close	();

        // doe iets met kamers

        interaction(*kamers[0]);

    } catch (exception &e) {
        std::cout << "Aiiii:" << e.what() << std::endl;
    }

	return 0;
}

