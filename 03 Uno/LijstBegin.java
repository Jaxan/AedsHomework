package uno;

import java.util.Iterator;
import java.util.Random;

/**
 * Een eigen Lijst klasse voor Uno
 *
 * HERNOEM DEZE KLASSE NAAR Lijst
 *
 * @author Pieter Koopman
 */
public class LijstBegin <T>
{

    /**
     * de iteraror voor Lijst
     */
    private class LijstIterator implements Iterator
    {
        /**
         * De vorige knoop en de knoop die het laatst is gezien bij next();
         */
        private Knoop <T> vorige, huidige;

        /**
         * De constructor van de LijstIterator
         * Alle info van lijst is bekend omdat de LijstItertor lokaal is
         * De aanname is dat er altijd hoogestens een iterator actief is
         */
        public LijstIterator( )
        {
            huidige = vorige = null;
        }

        /**
         * is er nog een volgend element in de lijst
         * @return True als er nog een element is
         */
        public boolean hasNext()
        {
            return false;
        }

        /**
         * lever het volgende elemnt op
         * huidige en vorige worden aangepast.
         * huidige wordt de Knoop van het op geleverde element
         * @return de inhoud van de Knoop
         */
        public T next()
        {
            return null;
        }

        /**
         * verwijder het laatst opgeleverde element (huidige)
         * Mag alleen gebruikt worden na een next
         * speciale aandacht nodig voor eerste en laatste element
         */
        public void remove()
        {
        }
    }

    /**
     * Lijst bevat referentie naar eerste en laatste knoop en de lengte.
     * De random generator wordt gebruikt in voegErgensToe.
     */
    private Knoop <T> kop = null, staart = null;
    private int lengte = 0;
    Random randomgen;

    /**
     * de constructor, maakt een lege lijst
     */
    public LijstBegin ()
    {
        randomgen = new Random();
    }

    /**
     * predicaat om te controleren of de lijst leeg is
     * @return true als de lijst leeg is
     */
    public boolean isLeeg ()
    {
        return true;
    }

    /**
     * getter van het lengte attribuut
     * @return de huidige lengte van de lijst
     */
    public int getLengte ()
    {
        return 0;
    }

    /**
     * Voeg een element vooraan in de lijst toe
     * @param t het nieuw element
     */
    public void voegVooraanToe (T t)
    {
    }

    /**
     * voeg een element achteraan in de lijst toe
     * @param t het nieuwe element
     */
    public void voegAchteraanToe (T t)
    {
    }

    /**
     * Voeg een element op een pseudo random plek toe
     * @param t het nieuwe element
     */
    public void voegErgensToe (T t)
    {
    }

    /**
     * pak het eerste element van de lijst en verwijder dat
     * @return het eerste element
     * @throws java.lang.Exception als de lijst leeg is
     */
    public T pakEerste () throws Exception
    {
        throw new Exception ("eerste element van lege lijst!");
    }

    /**
     * maak een string die de inhoud van de lijst beschrijft
     * elementen worden gescheiden door spaties
     * @return de opgebouwd string
     */
    @Override
    public String toString ()
    {
        StringBuilder output = new StringBuilder();
        return output.toString();
    }

    /**
     * maak een iterator voor deze lijst, deze begint voor aan de lijst
     * @return  de LijstIterator
     */
    public Iterator iterator()
    {
        return new LijstIterator();
    }
}
