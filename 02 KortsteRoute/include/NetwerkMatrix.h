#ifndef NETWERKMATRIX_H
#define NETWERKMATRIX_H

#include <limits>
#include <iostream>


class NetwerkMatrix {
public:
    NetwerkMatrix(std::string fileName) : stations(-1) {

        std::ifstream file(fileName);

        Scanner scanner = new Scanner(new FileReader(file));

        stations = scanner.nextInt();
        System.out.println("Dit netwerk heeft "+stations+" stations");
        scanner.nextLine();
        afstand = new int [stations] [stations];
        for (int i = 0; i < stations; i += 1)
            for (int j = 0; j < stations; j += 1)
                afstand[i][j] = i == j ? 0 : std::numeric_limits<int>::max();

        while (scanner.hasNextLine()) {
            int van, naar, afstand;
            van     = scanner.nextInt();
            naar    = scanner.nextInt();
            afstand = scanner.nextInt();
            System.out.println("Er is een spoor van "+van+" naar "+naar+" met lengte "+afstand);
            setAfstand(van-1, naar-1, afstand); // -1 wegens array indices
            scanner.nextLine();
        }

    }

    virtual ~NetwerkMatrix() {

    }


    int  grootte() {
        if (stations > 0)
            return stations;
        else
            throw new Exception("Leeg netwerk");
    }

    int  getAfstand(int van, int naar) throws Exception {
        if (van >= 0 && van < stations && naar >= 0 && naar < stations) {
            return afstand[van][naar];
        } else
            throw new Exception("Illegaal station nummer in "+(van+1)+", "+(naar+1));
    }




private:

    int stations;
    int * afstand;

    void setAfstand(int van, int naar, int lengte) {
        if (van >= 0 && van < stations && naar >= 0 && naar < stations) {
            afstand[van][naar] = lengte;
            afstand[naar][van] = lengte;
        } else
            throw new Exception("Illegaal station nummer in "+(van+1)+", "+(naar+1));
    }
};

#endif // NETWERKMATRIX_H
