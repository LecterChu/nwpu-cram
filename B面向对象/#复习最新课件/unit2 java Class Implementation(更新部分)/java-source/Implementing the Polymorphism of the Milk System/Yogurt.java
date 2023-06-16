/*!Begin Snippet:file*/

import java.util.Date;

/**
 * This class models a yogurt. It extends {@link Product} and
 * adds the following information:
 * <ol>
 * <li>the type of the yogurt, a <code>String</code></li>
 * <li>the dilute concentration of the yogurt, a <code>String</code></li>
 * </ol>
 *
 * @author ydecube
 * @version  1.0.0
 * @see Product
 */
public class Yogurt extends Product{

    /* Type of the yogurt.*/
    private String type;

    /* Dilute concentration of the yogurt.*/
    private String diluteConcentration;

    /**
     * Constructs a <code>Yogurt</code> object.
     *
     * @param initialCode  the code of the yogurt.
     * @param initialDescription  the description of the yogurt.
     * @param initialPrice  the price of the yogurt.
     * @param initialProductionDate  the production date of the yogurt.
     * @param initialShelfLife  the shelf life of the yogurt.
     * @param initialType  the type of the yogurt.
     * @param initialDiluteConcentration  the dilute concentration of the yogurt.
     */
    public Yogurt(String initialCode, String initialDescription, double initialPrice,
                  Date initialProductionDate, String initialShelfLife, String initialType,
                  String initialDiluteConcentration) {

        super(initialCode, initialDescription, initialPrice, initialProductionDate, initialShelfLife);

        this.type = initialType;
        this.diluteConcentration = initialDiluteConcentration;
    }

    /**
     * Returns the type of the yogurt.
     *
     * @return  the type of the yogurt.
     */
    public String getType() {

        return this.type;
    }

    /**
     * Returns the dilute concentration of the yogurt.
     *
     * @return  the dilute concentration of the yogurt.
     */
    public String getDiluteConcentration() {

        return this.diluteConcentration;
    }

    /**
     * Returns the string representation of this yogurt.
     *
     * @return  the string representation of this yogurt.
     */
    @Override
    public String toString() {

        return super.toString() + "_" + getType() + "_"
                + getDiluteConcentration();
    }
}
/*!End Snippet:file*/
