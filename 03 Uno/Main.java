/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package uno;

import java.util.Iterator;

/**
 *
 * @author Pieter Koopman
 */
public class Main
{

    /**
     * @param args the command line arguments
     */
    public static void main( String[] args )
    {
        new Main();
    }

    /**
     * Main klasse doet wat tests met de klasse Kaart en Lijst
     */
    public Main()
    {
        Lijst<Kaart> stapel1 = new Lijst<Kaart> (), stapel2 = new Lijst<Kaart> (), stapel3 = new Lijst<Kaart> ();
        for (int w=1; w<=10; w += 1)
        {
            Kaart k = new Kaart (Kaart.Soort.Geel,w);
            stapel1.voegErgensToe(k);
            stapel2.voegVooraanToe(k);
            stapel3.voegAchteraanToe(k);
        }
        Kaart k = new Kaart (Kaart.Soort.Keuze);
        stapel1.voegErgensToe(k);
        stapel2.voegVooraanToe(k);
        stapel3.voegAchteraanToe(k);

        System.out.println( "De random stapel bevat:       " + stapel1 );
        System.out.println( "De omgekeerde stapel bevat:   " + stapel2 );
        System.out.println( "De nette stapel bevat:        " + stapel3 );

        System.out.print  ( "De nette stapel met iterator: " );
        for (Iterator iter = stapel3.iterator(); iter.hasNext(); )
            System.out.print( iter.next() + "; " );
        System.out.println();

        Iterator<Kaart> iter = stapel3.iterator();
        System.out.print( "removing: " );
        for ( int i = 0; iter.hasNext(); i += 1 )
        {
            Kaart k2 = iter.next();
            if ( i % 2 == 1 ) // probeer ook de andere mogelijkheid!
            {
                iter.remove();
                System.out.print( k2 + "; " );
            }
         }
        System.out.println();
        System.out.println( "De nette stapel bevat nu nog: " + stapel3 );
    }
}
