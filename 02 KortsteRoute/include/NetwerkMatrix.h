#ifndef NETWERKMATRIX_H
#define NETWERKMATRIX_H

#include "Netwerk.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <deque>
#include <algorithm>


class NetwerkMatrix : public Netwerk {
public:
    NetwerkMatrix(std::string fileName) : stations(-1) {
        std::ifstream file(fileName);
        if (!file) throw std::runtime_error("Ik kon het bestand "+fileName+" niet lezen");

        file >> stations;

        std::cout << "Dit netwerk heeft " << stations << " stations" << std::endl;

        afstand = new int [stations*stations];
        std::fill_n(afstand, stations*stations, INF);

        for (int i = 0; i < stations; i += 1)
            afstand[i + stations*i] = 0;

        while (true) {
            int van, naar, afstand;
            file >> van >> naar >> afstand;

            if (!file) break;

            std::cout << "Er is een spoor van " << van << " naar " << naar << " met lengte " << afstand << std::endl;
            setAfstand(van-1, naar-1, afstand); // -1 wegens array indices
        }

    }

    virtual ~NetwerkMatrix() {
        delete[] afstand;
    }


    int getGrootte() const {
        if (stations > 0)
            return stations;
        else
            throw std::logic_error("Leeg netwerk");
    }

    int getAfstand(int van, int naar) const {
        if (van >= 0 && van < stations && naar >= 0 && naar < stations)
            return afstand[van + stations*naar];
        else {
            std::stringstream stream("Illegaal station nummer in ");
            stream << van+1 << ", " << naar+1;
            throw std::out_of_range(stream.str());
        }
    }


    void kortsteRoute(int van, int naar) const {
        std::vector<Station> afstandenTotStations(getGrootte());
        van--; naar--;
        afstandenTotStations[van].bezocht = true;
        afstandenTotStations[van].afstand = 0;

        int huidigStation = van;

        while (huidigStation != naar) {

            int minAfstand = INF;
            int minStation = -1;

            for ( int i = 0; i < getGrootte(); ++i){
                //if ( i == huidigStation ) continue;
                int afstand = afstandenTotStations[huidigStation].afstand + getAfstand(huidigStation, i);

                if ( afstand < INF ) std::cout << huidigStation+1 << "->" << i+1 << ": " << afstand << std::endl;

                if ( afstand < afstandenTotStations[i].afstand ) {
                    afstandenTotStations[i].afstand = afstand;
                    afstandenTotStations[i].vorige = huidigStation;
                }

                afstand = afstandenTotStations[i].afstand;

                if ( !afstandenTotStations[i].bezocht && afstand < minAfstand ) {
                    std::cout << '\t' << i+1 << " met " << afstand << " is betrer dan " << minAfstand << std::endl;
                    minAfstand = afstand;
                    minStation = i;
                }
            }

            if ( minStation == -1 ) throw std::logic_error("Er is geen goed station gevonden, dat is vreemd...");

            afstandenTotStations[minStation].bezocht = true;
            huidigStation = minStation;

        }

        std::cout << "kortste pad is " << afstandenTotStations[huidigStation].afstand << "km :D" << std::endl;

        std::deque<int> reversedArrayList;
        while ( huidigStation != -1 ) {
            reversedArrayList.push_front(huidigStation);
            huidigStation = afstandenTotStations[huidigStation].vorige;
        }
        std::for_each(reversedArrayList.begin(), reversedArrayList.end(), [] (int x) { std::cout << x+1 << ", "; } );

    }


private:

    int stations;
    int * afstand;

    void setAfstand(int van, int naar, int lengte) {
        if (van >= 0 && van < stations && naar >= 0 && naar < stations) {
            afstand[van + stations*naar] = lengte;
            afstand[naar + stations*van] = lengte;
        } else {
            std::stringstream stream("Illegaal station nummer in ");
            stream << van+1 << ", " << naar+1;
            throw std::out_of_range(stream.str());
        }
    }
};

#endif // NETWERKMATRIX_H
