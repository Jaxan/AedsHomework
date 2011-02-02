#include <iostream>
#include <fstream>
#include <string>
#include <limits>

/*
    Algoritmen & Datastrucuren 2011
    Begin van opgave 1

    Pieter koopman, pieter@cs.ru.nl
*/

using namespace std;

class Uitgang
{
    // de variabelen en methoden van deze klasse
};

class Kamer
{
private:
    // de variabelen van deze klasse

public:
    Kamer (char _naam [], char _beschrijving [], bool _eind){}

    void nieuweUitgang (char _sleutel [], Kamer* _naar){}
};


void leesKamers (ifstream& file)
{
     int aantal;
     file >> aantal;

     for (int i=0; i<aantal; i++)
     {   int nr;
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

void leesUitgangen (ifstream& file)
{
     while (true)
     {   int van;
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

int main ()
{
    // Simpel voorbeeld van directe definities
    Kamer  k1  =  Kamer ("Startkamer", "Dit is het begin van de reis.", false ) ;
    Kamer  k2  =  Kamer ("Eindstation", "Dit is de laatste kamer.", true ) ;

    k1.nieuweUitgang ("blijf hier", &k1 ) ;
    k1.nieuweUitgang ("ga verder", &k2 ) ;
    k2.nieuweUitgang ("opnieuw", &k1 ) ;

    // Kamers en uitgangangen uit files lezen
	char in_naam1 [] = "kamers.txt";
	char in_naam2 [] = "deuren.txt";
	ifstream kamer_file(in_naam1);
	ifstream uitg_file (in_naam2);

	if (! kamer_file)
	{
		cout << "Het kamerbestand " << in_naam1 << " kon niet geopend worden.\n";
		return 1;
	}
	if (! uitg_file)
	{
		cout << "Het uitgangenbestand " << in_naam2 << " kon niet geopend worden.\n";
		return 1;
	}

	leesKamers (kamer_file);
	leesUitgangen (uitg_file);

	kamer_file.close ();
	uitg_file.close	();

	return 0;
}

