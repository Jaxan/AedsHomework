#ifndef NETWERK_H
#define NETWERK_H

#include <limits>

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

    virtual int getAfstand(int van, int naar) const = 0;
protected:
private:
};

#endif // NETWERK_H
