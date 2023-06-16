/*!Begin Snippet:file*/

import java.util.ArrayList;
import java.util.Iterator;

/**
 * Maintains a collection of {@link SaleItem} assigned to a order.
 *
 * @author ydecube
 * @version  1.0.0
 * @see SaleItem
 */
public class ProductSaleList implements Iterable<SaleItem> {

    /* SaleItems assigned to a order.*/
    private ArrayList<SaleItem> saleItems;

    /**
     * Sets the collection of {@link SaleItem} to empty.
     */
    public ProductSaleList() {

        this.saleItems = new ArrayList<SaleItem>();
    }

    /**
     * Adds a {@link SaleItem} object to this collection.
     *
     * @param saleItem  the {@link SaleItem} object.
     */
    public void addSaleItem(SaleItem saleItem) {

        this.saleItems.add(saleItem);
    }

    /**
     * Removes a {@link SaleItem} object from this collection.
     *
     * @param saleItem  the {@link SaleItem} object.
     */
    public void removeSaleItem(SaleItem saleItem) {

        this.saleItems.remove(saleItem);
    }

    /**
     * Returns an iterator over the sale items in this collection.
     *
     * return  an {@link Iterator} of {@link SaleItem}
     */
    @Override
    public Iterator<SaleItem> iterator() {

        return this.saleItems.iterator();
    }

    /**
     * Returns the {@link SaleItem} object with the specified
     * <code>code</code>.
     *
     * @param code  the code of an item.
     * @return  The {@link SaleItem} object with the specified
     *          code. Returns <code>null</code> if the object with
     *          the code is not found.
     */
    public SaleItem getSaleItem(String code) {

        for (SaleItem saleItem : saleItems) {
            if (saleItem.getProduct().getCode().equals(code)) {

                return saleItem;
            }
        }
        return null;
    }

    /**
     * Returns the number of sale items.
     *
     * @return  the number of sale items.
     */
    public int getNumberOfItems() {

        return this.saleItems.size();
    }

    /**
     * Returns the total cost of sale items.
     *
     * @return the total cost of sale items.
     */
    public double getTotalCost() {

        double total = 0;
        for (SaleItem saleItem : saleItems){
            total += saleItem.getValue();
        }
        return total;
    }

    /**
     * Clear all sales items in this collection.
     */
    public void clearSaleItem() {

        this.saleItems.clear();
    }
}
/*!End Snippet:file*/
