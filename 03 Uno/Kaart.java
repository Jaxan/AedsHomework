
package uno;

/**
 * De kaarten voor het spelletje Uno
 * @author Pieter Koopman
 */
public class Kaart
{
    /**
     * het soort van de kaarten
     */
    public enum Soort
    {Geel, Groen, Rood, Blauw, Keuze, KeuzeNeem4;
    
        public String toString()
         {
             switch (this)
             {
                 case Geel: return "Geel";
                 case Groen: return "Groen";
                 case Blauw: return "Blauw";
                 case Rood: return "Rood";
                 case Keuze: return "Keuze";
                 case KeuzeNeem4: return "KeuzeNeem4";
                 default: return "Onbekend soort!";
             }
         }
    };

    /**
     * de speciale waarden van de kaarten
     */
    public final int Pak2 = 10, KeerOm=11, SlaOver=12;

    /**
     * Kaart wordt gekenmerkt door zijn soort en waarde
     */
    private Soort soort;
    private int waarde;

    /**
     * standaard constructor
     * @param s soort
     * @param w waarde van de kaart
     */
    public Kaart (Soort s, int w)
    {
        soort = s;
        waarde = w;
    }

    /**
     * constructor voor kaarten zonder speciale waarde (b.v. KeerOm)
     * @param s de soort
     */
    public Kaart (Soort s)
    {
        soort = s;
        waarde = -1;
    }

    /**
     * getter voor soort, geen setter want kaarten worden nooit veranderd
     * @return het soort van deze kaart
     */
    public Soort getSoort()
    {
        return soort;
    }

    /**
     * getter voor waarde
     * @return de waarde indien deze bestaat, anders -1
     */
    public int getWaarde()
    {
        return waarde;
    }

    /**
     * gaat na of deze kaart op de gegeven kaart past
     * @param k de kaart waar deze bovenop zou moeten
     * @return of het past
     * PAS OP: deze test is iets te simpel
     */
    public boolean pastOp (Kaart k)
    {
        return soort == k.soort || waarde == k.waarde;
    }

    /**
     * maakt een nette string die deze kaart beschrijft
     * @return de beschrijving van deze kaart
     */
    public String toString()
    {
        switch (soort)
        {
            case Keuze:
            case KeuzeNeem4: return soort.toString();
            default:
                switch (waarde)
                {
                    case Pak2:      return soort + " 2 pakken";
                    case KeerOm:    return soort + " keer om";
                    case SlaOver:   return soort + " beurt overslaan";
                    default:        return soort + " " + waarde;
                }
        }
    }
}
