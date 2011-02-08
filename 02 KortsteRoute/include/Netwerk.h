#ifndef NETWERK_H
#define NETWERK_H


class Netwerk {
public:
    Netwerk() {}
    virtual ~Netwerk() {}

    virtual int getAfstand(int van, int naar) const = 0;
protected:
private:
};

#endif // NETWERK_H
