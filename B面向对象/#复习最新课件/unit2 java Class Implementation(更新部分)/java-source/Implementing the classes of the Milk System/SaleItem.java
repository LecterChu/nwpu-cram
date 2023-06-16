/*!Begin Snippet:file*/

/**
 * This class models a sales item. It contains the following
 * following information:
 * </p>
 * <ol>
 * <li>the quantity of the sales item, a <code>String</code></li>
 * <li>the product corresponding to the sales item, a <code>Product</code></li>
 * </ol>
 *
 * @author ydecube
 * @version  1.0.0
 * @see Product
 */
public class SaleItem {

    /* Quantity of the sales item. */
    private int quantity;

    /* Product corresponding to the sales item. */
    private Product product;

    /**
     * Constructs a <code>SaleItem</code> object.
     *
     * @param initialQuantity  the quantity of the sales item.
     * @param initialProduct  the product corresponding to the sales item.
     */
    public SaleItem(int initialQuantity, Product initialProduct) {

        this.quantity = initialQuantity;
        this.product = initialProduct;
    }

    /**
     * Returns the quantity of the sales item.
     *
     * @return  the quantity of the sales item.
     */
    public int getQuantity() {

        return this.quantity;
    }

    /**
     * Returns the product corresponding to the sales item.
     *
     * @return  the product corresponding to the sales item.
     */
    public Product getProduct() {

        return this.product;
    }

    /**
     * Sets the value of instance variable <code>quantity</code>.
     *
     * @param quantity  the new value.
     */
    public void setQuantity(int quantity) {

        this.quantity = quantity;
    }

    /**
     * Returns the total cost of the sales item.
     *
     * @return  the total cost of the sales item.
     */
    public double getValue(){

        return this.product.getPrice() * getQuantity();
    }

    /**
     * Returns the string representation of this sales item.
     *
     * @return  the string representation of this sales item.
     */
    @Override
    public String toString() {

        return this.quantity + "|" + getProduct().getCode() + "|" +
                getProduct().getDescription() + "|" + getProduct().getPrice();
    }
}
