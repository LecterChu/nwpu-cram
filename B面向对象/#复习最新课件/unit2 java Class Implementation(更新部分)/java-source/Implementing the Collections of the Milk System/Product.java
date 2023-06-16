/*!Begin Snippet:file*/

import java.util.Date;

/**
 * This class models a product sold in a milk store. It contains the following
 * following information:
 * </p>
 * <ol>
 * <li>the code of the product, a <code>String</code></li>
 * <li>the description of the product, a <code>String</code></li>
 * <li>the price of the product, a <code>double</code></li>
 * <li>the production date of the product, a <code>String</code></li>
 * <li>the shelf life of the product, an <code>int</code></li>
 * </ol>
 *
 * @author ydecube
 * @version  1.0.0
 */
public class Product {

    /* Identification number of the product.*/
    private String code;

    /* Description of the product.*/
    private String description;

    /* Price of the product.*/
    private double price;

    /* Production date of the product.*/
    private Date productionDate;

    /* Shelf life of the product.*/
    private String shelfLife;

    /**
     * Constructs a <code>Product</code> object.
     *
     * @param initialCode  the code of the product.
     * @param initialDescription  the description of the product.
     * @param initialPrice  the price of the product.
     * @param initialProductionDate  the production date of the product.
     * @param initialShelfLife  the shelf life of the product.
     */
    public Product(String initialCode, String initialDescription, double initialPrice,
                   Date initialProductionDate, String initialShelfLife) {

        this.code = initialCode;
        this.description = initialDescription;
        this.price = initialPrice;
        this.productionDate = initialProductionDate;
        this.shelfLife = initialShelfLife;
    }

    /**
     * Returns the code of this product.
     *
     * @return  the code of this product.
     */
    public String getCode() {

        return this.code;
    }

    /**
     * Returns the description of this product.
     *
     * @return  the description of this product.
     */
    public String getDescription() {

        return this.description;
    }

    /**
     * Returns the price of this product.
     *
     * @return  the price of this product.
     */
    public double getPrice() {
        return this.price;
    }

    /**
     * Returns the production date of this product.
     *
     * @return  the production date of this product.
     */
    public Date getProductionDate() {

        return this.productionDate;
    }

    /**
     * Returns the shelf life of this product.
     *
     * @return  the shelf life of this product.
     */
    public String getShelfLife() {

        return this.shelfLife;
    }

    /**
     * Returns <code>true</code> if the code of this product is
     * equal to the code of the argument
     *
     * @param object  object with which this product is compared.
     * @return  <code>true</code> if the code of this product is
     *          equal to the code of the argument; <code>false</code>
     *          otherwise.
     */
    public boolean  equals(Object  object)  {

        return object instanceof Product
                && getCode().equals(((Product) object).getCode());
    }

    /**
     * Returns the string representation of this product.
     *
     * @return  the string representation of this product.
     */
    @Override
    public String toString() {

        return getCode() + "_" + getDescription() + "_" + getPrice()
                + "_" + getProductionDate() + "_" + getShelfLife();
    }
}
/*!End Snippet:file*/
