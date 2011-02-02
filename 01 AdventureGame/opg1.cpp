#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <limits>


/*
	Algoritmen & Datastrucuren 2011
	Begin van opgave 1

	Pieter koopman, pieter@cs.ru.nl
*/

using namespace std;	// slechte stijl...

class Kamer; 			// forward decleration

class Uitgang {
public:
	std::string sleutel;
	Kamer * nextKamer;
	Uitgang * next;

	
	// wij prefereren const als een postfix (zoals c ooit ontworpen is)
	Uitgang (char const * sleutel, Kamer * nextKamer ) : sleutel(sleutel), nextKamer(nextKamer), next(NULL) {
	}

	void push_back (Uitgang * element) {
		// haha recursief :D
		if ( next == NULL ) {
			next = element;
		} else {
			next->push_back(element);
		}
	}

};

class Kamer {
public:
	// als we de standaard library van c++ mochten gebruiken, waren we veel sneller (en veiliger, en minder c-ish) klaar...
	std::string naam;
	std::string beschrijving;
	bool eind;
	Uitgang * firstUitgang;


	// AUW dit (de orginele code) doet pijn, want:
	// 1. c++ 2003 standaard: "Each name that begins with an underscore is reserved to the implementation for use as a name in the global namespace."
	// 2. gebruik van "char *" is deprecated ("char const *" of "const char *" moet gebruikt worden)
	// FOEI!
	Kamer (char _naam [], char _beschrijving [], bool _eind) : naam(_naam), beschrijving(_beschrijving), eind(_eind), firstUitgang(NULL) {

	}

	void nieuweUitgang (char _sleutel [], Kamer* _naar) {
		Uitgang * newUitgang = new Uitgang(_sleutel, _naar);

		if ( firstUitgang == NULL ) {
			firstUitgang = newUitgang;
		} else {
			firstUitgang->push_back(newUitgang);
		}
	}

};


void leesKamers (ifstream& file) {
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

// Conversie van `string' naar `char []' doe je met `naam.c_str()'.

		string beschr;
		getline(file, beschr);

		cout << nr << " " << is_eind << " " << naam << " " << beschr << endl;
	}
}

void leesUitgangen (ifstream& file) {
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
	}
}

void interaction(Kamer& startKamer){
	Kamer * nextKamer = &startKamer;

	while(true){
		Kamer& kamer = *nextKamer;

		system("clear");	// werkt niet onder windows?
		cout << "U bent nu hier: " << kamer.naam << endl;
		cout << kamer.beschrijving << endl << endl;
		if ( kamer.eind ) cout << "HOERA, dit is het einde, uw leven is nu compleet" << endl;
	
		Uitgang * iterator = kamer.firstUitgang;
		cout << "Waar wilt u heen?" << endl;
		for ( unsigned int i = 1; iterator != NULL; ++i ) {
			cout << i << ". " << iterator->sleutel << endl;
			iterator = iterator->next;
		}
		cout << "Maak uw keuze door het getal in te tikken: " << endl;
		int choice;
		while (!(cin >> choice)){
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "doe ff normaal" << endl;
		}

		iterator = kamer.firstUitgang;
		for ( unsigned int i = 1; i < choice && iterator != NULL; ++i ) {
			cout << i << ". " << iterator->sleutel << endl;
			iterator = (iterator->next != NULL) ? iterator->next : iterator;
		}

		nextKamer = iterator->nextKamer;
	}

}

int main () {
	// Simpel voorbeeld van directe definities
	Kamer  k1  =  Kamer ("Startkamer", "Dit is het begin van de reis.", false ) ;
	Kamer  k2  =  Kamer ("Eindstation", "Dit is de laatste kamer.", true ) ;

	k1.nieuweUitgang ("blijf hier", &k1 ) ;
	k1.nieuweUitgang ("ga verder", &k2 ) ;
	k2.nieuweUitgang ("opnieuw", &k1 ) ;

	interaction(k1);

	// Kamers en uitgangangen uit files lezen
	/*
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

	leesKamers (kamer_file);
	leesUitgangen (uitg_file);

	kamer_file.close ();
	uitg_file.close	();
	*/

	return 0;
}

