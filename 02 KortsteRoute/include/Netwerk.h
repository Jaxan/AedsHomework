#ifndef NETWERK_H
#define NETWERK_H

#include <limits>


struct Station {

    bool bezocht;
    int afstand;

    Station() : bezocht(false), afstand(std::numeric_limits<int>::max()) {}

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
