/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package ad11o02uit;

import java.io.File;
import java.io.FileReader;
import java.util.Scanner;

/**
 *
 * @author Pieter Koopman
 */
public class NetwerkMatrix extends Netwerk
{
    private int stations = -1;
    private int [] [] afstand;

    /**
     * constructio leest afstanden uit file
     * Eerste regel bevat het aantal stations
     * iedere volgende regel bevat een verbinding in de vorm van 3 integers:
     * van naar aftand
     * @param fileName
     * @throws java.lang.Exception gooit exception als er iets mis gaat met lezen of access
     */
    public NetwerkMatrix(String fileName) throws Exception
    {
        File file = new File(fileName);
        Scanner scanner = new Scanner(new FileReader(file));

        stations = scanner.nextInt();
        System.out.println("Dit netwerk heeft "+stations+" stations");
        scanner.nextLine();
        afstand = new int [stations] [stations];
        for (int i = 0; i < stations; i += 1)
            for (int j = 0; j < stations; j += 1)
                afstand[i][j] = i == j ? 0 :INF;

        while (scanner.hasNextLine())
        {
            int van, naar, afstand;
            van     = scanner.nextInt();
            naar    = scanner.nextInt();
            afstand = scanner.nextInt();
            System.out.println("Er is een spoor van "+van+" naar "+naar+" met lengte "+afstand);
            setAfstand(van-1, naar-1, afstand); // -1 wegens array indices
            scanner.nextLine();
        }
    }

    /**
     * Het aantal stations
     * @return aantal stations als dat gezet is
     * @throws java.lang.Exception als aantal niet gezet is
     */
    public int  grootte() throws Exception
    {
        if (stations > 0)
            return stations;
        else
            throw new Exception("Leeg netwerk");
    }

    /**
     * getter voor afstanden
     * @param van
     * @param naar
     * @return
     * @throws java.lang.Exception
     */
    public int  getAfstand(int van, int naar) throws Exception
    {
        if (van >= 0 && van < stations && naar >= 0 && naar < stations)
        {
            return afstand[van][naar];
        }
        else
            throw new Exception("Illegaal station nummer in "+(van+1)+", "+(naar+1));
    }

    /**
     * setter voor afstanden, afstanden zijn altijd symmetrisch
     * (naar,va,afsatnd wordt automatisch gezet
     * @param van
     * @param naar
     * @param afstand
     * @throws java.lang.Exception
     */
    private void setAfstand(int van, int naar, int lengte) throws Exception
    {
        if (van >= 0 && van < stations && naar >= 0 && naar < stations)
        {
            afstand[van][naar] = lengte;
            afstand[naar][van] = lengte;
        }
        else
            throw new Exception("Illegaal station nummer in "+(van+1)+", "+(naar+1));
    }
}
