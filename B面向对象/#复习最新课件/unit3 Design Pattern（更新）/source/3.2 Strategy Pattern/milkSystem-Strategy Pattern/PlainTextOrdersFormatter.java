/*!Begin Snippet:file*/



/**
 * This class implements a method that obtains a plain text
 * representation of a {@link StoreSales} object.
 *
 * @author ydecube
 * @version  1.0.0
 * @see OrdersFormatter
 * @see StoreSales
 * @see Order
 * @see ProductSaleList
 * @see SaleItem
 */
public class PlainTextOrdersFormatter implements OrdersFormatter{

    /* Line separator */
    private final static String NEW_LINE = System.getProperty("line.separator");

    /* single instance of this class */
    static private PlainTextOrdersFormatter singletonInstance = null;

    /**
     * Obtains the single instance of class
     * <code>PlainTextOrdersFormatter</code>
     *
     * @return the single instance  of class
     *         <code>PlainTextOrdersFormatter</code>
     */
    static public PlainTextOrdersFormatter getSingletonInstance() {

        if (singletonInstance == null) {
            singletonInstance = new PlainTextOrdersFormatter();
        }

        return singletonInstance;
    }

    /*
     * The constructor is declared private so other classes cannot
     * create an instance of this class.
     */
    private PlainTextOrdersFormatter() {

    }

    /**
     * Obtains a plain text representation of the store's sales.
     *
     * @param storeSales  the store's sales.
     * @return  a plain text representation of the specified
     *          {@link StoreSales} object.
     */
    @Override
    public String formatOrders(StoreSales storeSales) {

        String out = "Store's Sales" + NEW_LINE;

        for (Order order : storeSales) {

            double total = order.getTotal();

            for (SaleItem saleItem : order) {
                Product product = saleItem.getProduct();

                out += product.getCode() + "_" + product.getDescription() + "_"
                            + product.getPrice() + "_" + saleItem.getQuantity();
                out += NEW_LINE;
            }
            out += "total:" + total + NEW_LINE;
        }

        return out;
    }
}
/*!End Snippet:file*/
