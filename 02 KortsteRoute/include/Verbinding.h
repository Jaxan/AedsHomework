#ifndef VERBINDING_H
#define VERBINDING_H

#include "Netwerk.h"

#include <limits>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>


class Verbinding : public Netwerk {
public:
    Verbinding(std::string fileName) {
        std::ifstream file(fileName);
        if (!file) throw std::runtime_error("Ik kon het bestand "+fileName+" niet lezen");

        file >> stations;

        std::cout << "Dit netwerk heeft " << stations << " stations" << std::endl;

        while (true) {
            int van, naar, afstand;
            file >> van >> naar >> afstand;

            if (!file) break;

            std::cout << "Er is een spoor van " << van << " naar " << naar << " met lengte " << afstand << std::endl;
            setAfstand(van, naar, afstand); //Geen -1 vanwege map indices
        }

    }

    virtual ~Verbinding() {}

    int getGrootte() const {
        if (stations > 0) {
            return stations;
        } else {
            throw std::logic_error("Leeg netwerk");
        }
    }

    int getAfstand(int van, int naar) const {
        if (afstand.find(van) != afstand.end() && afstand[van].find(naar) != afstand.end() {
            return afstand[van][naar];
        } else {
            return std::numeric_limits<int>::max();
        }
    }

private:
    int stations;
    std::map<int <std::map<int, int> > afstand;

    void setAfstand(int van, int naar, int lengte) {
        if (van >= 1 && van < stations && naar >= 1 && naar < stations) {
            afstand[van][naar] = lengte;
            afstand[naar][van] = lengte;
        } else {
            std::stringstream stream("Illegaal station nummer in ");
            stream << van << ", " << naar;
            throw std::out_of_range(stream.str());
        }
    }
};

#endif // VERBINDING_H
