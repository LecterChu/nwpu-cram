/*!Begin Snippet:file*/

import java.util.ArrayList;
import java.util.Iterator;

/**
 * Maintains the sales information for a milk store. Contains a
 * collection of {@link Order} objects.
 *
 * @author ydecube
 * @version  1.0.0
 * @see Order
 */
public class StoreSales implements Iterable<Order>{

    /* Collection of <code>Order</code> objects.*/
    private ArrayList<Order> orders;

    /**
     * Constructs an empty collection of {@link Order}
     * objects.
     */
    public StoreSales() {

        this.orders = new ArrayList<Order>();
    }

    /**
     * Adds a {@link Order} object to this store's sales.
     *
     * @param order  the {@link Order} object.
     */
    public void addOrder(Order order) {

        this.orders.add(order);
    }

    /**
     * Removes a {@link Order} object from this collection
     *
     * @param order  the {@link Order} object.
     */
    public void removeOrder(Order order) {

        this.orders.remove(order);
    }

    /**
     * Returns an iterator over the order in this store's sales.
     *
     * return  an {@link Iterator} of {@link Order}
     */
    @Override
    public Iterator<Order> iterator() {

        return this.orders.iterator();
    }

    /**
     * Returns the number of {@link Order} objects in this collection.
     *
     * @return  the number of {@link Order} objects in this collection.
     */
    public int getNumberOfOrders() {

        return orders.size();
    }

    /**
     * Returns the string representation of this collection.
     *
     * @return  the string representation of this collection.
     */
    @Override
    public String toString() {

        String result = "";
        for (Order order : this.orders) {
            result += order.toString();
        }
        return result;
     }
}
/*!End Snippet:file*/
