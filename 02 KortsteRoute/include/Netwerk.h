#ifndef NETWERK_H
#define NETWERK_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <deque>
// Nick Overdijk 3029832
// Joshua Moerman 3009408

#include <algorithm>

#define INF (1000000)


struct Station {

	bool bezocht;
	int afstand;
	int vorige;

	Station() : bezocht(false), afstand(INF), vorige(-1) {}

};



class Netwerk {
public:
	Netwerk() {}
	virtual ~Netwerk() {}

	virtual int getAfstand(int van, int naar) = 0;
	virtual int getGrootte() const = 0;

	void kortsteRoute(int van, int naar) {
		std::vector<Station> afstandenTotStations(getGrootte()+1);
		afstandenTotStations[van].bezocht = true;
		afstandenTotStations[van].afstand = 0;

		int huidigStation = van;

		// zolang we er nog niet zijn
		while(huidigStation != naar) {

			int minAfstand = INF;
			int minStation = -1;

			// alle afstanden controleren
			for(auto i = 1; i <= getGrootte(); ++i) {
				//if ( i == huidigStation ) continue;
				int afstand = afstandenTotStations[huidigStation].afstand + getAfstand(huidigStation, i);

				// nieuw kortste pad -> onthouden!
				if(afstand < afstandenTotStations[i].afstand) {
					afstandenTotStations[i].afstand = afstand;
					afstandenTotStations[i].vorige = huidigStation;
				}

				afstand = afstandenTotStations[i].afstand;

				// nog niet bezocht, dus hier mogelijk mee verder gaan
				if(!afstandenTotStations[i].bezocht && afstand < minAfstand) {
					minAfstand = afstand;
					minStation = i;
				}
			}

			if(minStation == -1) throw std::logic_error(std::string(__FILE__) + "::" + std::string(__func__) + "Er is geen goed station gevonden, dat is vreemd...");

			afstandenTotStations[minStation].bezocht = true;
			huidigStation = minStation;

		}

		std::cout << "kortste pad is " << afstandenTotStations[huidigStation].afstand << "km :D" << std::endl;

		std::deque<int> reversedArrayList;
		while(huidigStation != -1) {
			reversedArrayList.push_front(huidigStation);
			huidigStation = afstandenTotStations[huidigStation].vorige;
		}
		std::cout << "Volg het pad: ";
		std::for_each(reversedArrayList.begin(), reversedArrayList.end(), [](int x) -> void { std::cout << x << ", ";});    //NB: zie note hier beneden
		std::cout << "\b\b klaar!" << std::endl;

		/*
		    We hebben hierboven een lambda-functie gebruikt :)

		    als het niet werkt, update je compiler en zet de c++0x flag aan :)
		    NB: JA DIT IS GELDIGE C++ CODE!!!!!!!!!!!!111111111111`eins
		*/

	}

};

#endif // NETWERK_H
