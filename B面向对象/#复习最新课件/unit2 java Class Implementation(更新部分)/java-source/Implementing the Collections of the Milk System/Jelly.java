/*!Begin Snippet:file*/

import java.util.Date;

/**
 * This class models a jelly. It extends {@link Product} and
 * adds the following information:
 * <ol>
 * <li>the content of flavor in jelly, a <code>String</code></li>
 * </ol>
 *
 * @author ydecube
 * @version  1.0.0
 * @see Product
 */
public class Jelly extends Product {

    /* Content of flavor in jelly.*/
    private String flavor;

    /**
     * Constructs a <code>Jelly</code> object.
     *
     * @param initialCode  the code of the jelly.
     * @param initialDescription  the description of the jelly.
     * @param initialPrice  the price of the jelly.
     * @param initialProductionDate  the production date of the jelly.
     * @param initialShelfLife  the shelf life of the jelly.
     * @param initialFlavor  the content of flavor in jelly.
     */
    public Jelly(String initialCode, String initialDescription, double initialPrice,
                 Date initialProductionDate, String initialShelfLife, String initialFlavor) {

        super(initialCode, initialDescription, initialPrice, initialProductionDate, initialShelfLife);

        this.flavor = initialFlavor;
    }

    /**
     * Returns the content of flavor in jelly.
     *
     * @return  the content of flavor in jelly.
     */
    public String getFlavor() {

        return this.flavor;
    }

    /**
     * Returns the string representation of this jelly.
     *
     * @return  the string representation of this jelly.
     */
    @Override
    public String toString() {

        return super.toString() + "_" + getFlavor();
    }
}
/*!End Snippet:file*/
