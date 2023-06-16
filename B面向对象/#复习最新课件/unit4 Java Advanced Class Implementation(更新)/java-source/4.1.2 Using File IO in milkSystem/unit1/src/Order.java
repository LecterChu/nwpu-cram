/*!Begin Snippet:file*/

/**
 * This class models an order. It contains the following
 * information:
 * <ol>
 * <li>the total of the order, a <code>double</code></li>
 * <li>the list of sale items for an order
 *     a <code>ProductSaleList</code> object</li>
 * </ol>
 *
 * @author ydecube
 * @version  1.0.0
 * @see ProductSaleList
 * @see SaleItem
 */
public class Order {

    /* Total cost of the order.*/
    private double total;

    /* List of sale items for an order.*/
    private ProductSaleList productSaleList;

    /**
     * Constructs an <code>Order</code> object.
     * <p>
     * The collection of the sale items is initially empty.
     * </p>
     *
     * @param initialTotal  the total of the order.
     */
    public Order(int initialTotal) {
        this.total = initialTotal;
        this.productSaleList = new ProductSaleList();
    }

    /**
     * Returns the total of this order.
     *
     * @return  the total of this order.
     */
    public double getTotal() {

        return this.productSaleList.getTotalCost();
    }

    /**
     * Returns the sale items collection.
     *
     * @return  a {@link ProductSaleList} object.
     */
    public ProductSaleList getProductSaleList() {

        return this.productSaleList;
    }
}
/*!End Snippet:file*/
