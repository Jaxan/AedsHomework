// Nick Overdijk 3029832
// Joshua Moerman 3009408

#ifndef NETWERKMATRIX_H
#define NETWERKMATRIX_H

#include "Netwerk.h"

/*
ruimte complexiteit is O(n^2)
tijd complexiteit is O(n^2) (de lookup in de matrix is constant, en per node, moet je (bijna) alle nodes langsgaan, dus dat is van de orde n^2)
*/


class NetwerkMatrix : public Netwerk {
public:
	NetwerkMatrix(std::string fileName) : stations(-1) {
		std::ifstream file(fileName);
		if(!file) throw std::runtime_error(std::string(__FILE__) + "::" + std::string(__func__) + ": Ik kon het bestand "+fileName+" niet lezen");

		file >> stations;

		//std::cout << "Dit netwerk heeft " << stations << " stations" << std::endl;

		afstand = new int [stations*stations];
		std::fill_n(afstand, stations*stations, INF);

		for(int i = 0; i < stations; i += 1)
			afstand[i + stations* i] = 0;

		while(true) {
			int van, naar, afstand;
			file >> van >> naar >> afstand;

			if(!file) break;

			//std::cout << "Er is een spoor van " << van << " naar " << naar << " met lengte " << afstand << std::endl;
			setAfstand(van-1, naar-1, afstand); // -1 wegens array indices
		}

	}

	virtual ~NetwerkMatrix() {
		delete[] afstand;
	}


	int getGrootte() const {
		if(stations > 0)
			return stations;
		else
			throw std::logic_error(std::string(__FILE__) + "::" + std::string(__func__) + ": Leeg netwerk");
	}

	int getAfstand(int van, int naar) {
		van--;
		naar--;
		if(van >= 0 && van < stations && naar >= 0 && naar < stations)
			return afstand[van + stations*naar];
		else {
			std::stringstream stream;
			stream << __FILE__ << "::" << __func__ << ": Illegaal station nummer in " << van+1 << ", " << naar+1;
			throw std::out_of_range(stream.str());
		}
	}


private:

	int stations;
	int* afstand;

	void setAfstand(int van, int naar, int lengte) {
		if(van >= 0 && van < stations && naar >= 0 && naar < stations) {
			afstand[van + stations* naar] = lengte;
			afstand[naar + stations* van] = lengte;
		} else {
			std::stringstream stream;
			stream << __FILE__ << "::" << __func__ << ": Illegaal station nummer in " << van+1 << ", " << naar+1;
			throw std::out_of_range(stream.str());
		}
	}
};

#endif // NETWERKMATRIX_H
