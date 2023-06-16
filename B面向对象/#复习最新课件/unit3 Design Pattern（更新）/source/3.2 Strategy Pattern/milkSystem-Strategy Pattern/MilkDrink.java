/*!Begin Snippet:file*/

import java.util.Date;

/**
 * This class models a milk drink. It extends {@link Product} and
 * adds the following information:
 * <ol>
 * <li>the content of flavor in milk drink, a <code>String</code></li>
 * <li>the content of sugar in milk drink, a <code>String</code></li>
 * </ol>
 *
 * @author ydecube
 * @version  1.0.0
 * @see Product
 */
public class MilkDrink extends Product{

    /* Content of flavor in milk drink.*/
    private String flavor;

    /* Content of sugar in milk drink.*/
    private String sugar;

    /**
     * Constructs a <code>MilkDrink</code> object.
     *
     * @param initialCode  the code of the milk drink.
     * @param initialDescription  the description of the milk drink.
     * @param initialPrice  the price of the milk drink.
     * @param initialProductionDate  the production date of the milk drink.
     * @param initialShelfLife  the shelf life of the milk drink.
     * @param initialFlavor  the content of flavor in milk drink.
     * @param initialSugar  the content of sugar in milk drink.
     */
    public MilkDrink(String initialCode, String initialDescription, double initialPrice,
                     Date initialProductionDate, String initialShelfLife, String initialFlavor,
                     String initialSugar) {

        super(initialCode, initialDescription, initialPrice, initialProductionDate, initialShelfLife);

        this.flavor = initialFlavor;
        this.sugar = initialSugar;
    }

    /**
     * Returns the content of flavor in milk drink.
     *
     * @return  the content of flavor in milk drink.
     */
    public String getFlavor() {

        return this.flavor;
    }

    /**
     * Returns the content of sugar in milk drink.
     *
     * @return  the content of sugar in milk drink.
     */
    public String getSugar() {

        return this.sugar;
    }

    /**
     * Returns the string representation of this milk drink.
     *
     * @return  the string representation of this milk drink.
     */
    @Override
    public String toString() {

        return super.toString() + "_" + getFlavor() + "_"
                + getSugar();
    }
}
/*!End Snippet:file*/
