/*!Begin Snippet:file*/

/**
 * This interface defines a method that obtains a string
 * representation of a {@link StoreSales} object.
 *
 * @author ydecube
 * @version  1.0.0
 * @see StoreSales
 */
public interface OrdersFormatter {

    /**
     * Obtains the string representation of the store's sales.
     *
     * @param storeSales  the store's sales.
     * @return  the string representation of the specified
     *          {@link StoreSales} object.
     */
    String formatOrders(StoreSales storeSales);
}
/*!End Snippet:file*/