/*!Begin Snippet:file*/

import java.util.Date;

/**
 * This class models a pure milk. It extends {@link Product} and
 * adds the following information:
 * <ol>
 * <li>the country of origin of the pure milk, a <code>String</code></li>
 * <li>the content of butterfat in pure milk, a <code>String</code></li>
 * <li>the content of protein in pure milk, a <code>String</code></li>
 * </ol>
 *
 * @author ydecube
 * @version  1.0.0
 * @see Product
 */
public class PureMilk extends Product {

    /* Country of origin of the pure milk.*/
    private String countryOfOrigin;

    /* Content of butterfat in pure milk.*/
    private String butterfat;

    /* Content of protein in pure milk.*/
    private String protein;

    /**
     * Constructs a <code>PureMilk</code> object.
     *
     * @param initialCode  the code of the pure milk.
     * @param initialDescription  the description of the pure milk.
     * @param initialPrice  the price of the pure milk.
     * @param initialProductionDate  the production date of the pure milk.
     * @param initialShelfLife  the shelf life of the pure milk.
     * @param initialCountryOfOrigin  the country of origin of the pure milk.
     * @param initialButterfat  the content of butterfat in pure milk.
     * @param initialProtein  the content of protein in pure milk.
     */
    public PureMilk(String initialCode, String initialDescription, double initialPrice,
                    Date initialProductionDate, String initialShelfLife, String initialCountryOfOrigin,
                    String initialButterfat, String initialProtein) {

        super(initialCode, initialDescription, initialPrice, initialProductionDate, initialShelfLife);

        this.countryOfOrigin = initialCountryOfOrigin;
        this.butterfat = initialButterfat;
        this.protein = initialProtein;
    }

    /**
     * Returns the country of origin of the pure milk.
     *
     * @return  the country of origin of the pure milk.
     */
    public String getCountryOfOrigin() {

        return this.countryOfOrigin;
    }

    /**
     * Returns the content of butterfat in pure milk.
     *
     * @return  the content of butterfat in pure milk.
     */
    public String getButterfat() {

        return this.butterfat;
    }

    /**
     * Returns the content of protein in pure milk.
     *
     * @return  the content of protein in pure milk.
     */
    public String getProtein() {

        return this.protein;
    }

    /**
     * Returns the string representation of this pure milk.
     *
     * @return  the string representation of this pure milk.
     */
    @Override
    public String toString() {

        return super.toString() + "_" + getCountryOfOrigin() + "_"
                + getButterfat() + "_" + getProtein();
    }
}
/*!End Snippet:file*/
