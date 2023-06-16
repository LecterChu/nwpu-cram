/*!Begin Snippet:file*/

/**
 * This class implements a method that obtains a HTML
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
public class HTMLOrdersFormatter implements OrdersFormatter {

    /* Line separator */
    private final static String NEW_LINE = System.getProperty("line.separator");

    /* single instance of this class */
    static private HTMLOrdersFormatter singletonInstance = null;

    /**
     * Obtains the single instance of class
     * <code>HTMLOrdersFormatter</code>
     *
     * @return the single instance  of class
     *         <code>HTMLOrdersFormatter</code>
     */
    static public HTMLOrdersFormatter getSingletonInstance() {

        if (singletonInstance == null) {
            singletonInstance = new HTMLOrdersFormatter();
        }

        return singletonInstance;
    }

    /*
     * The constructor is declared private so other classes cannot
     * create an instance of this class.
     */
    private HTMLOrdersFormatter() {

    }

    /**
     * Obtains a HTML representation of the store's sales.
     *
     * @param storeSales  the store's sales.
     * @return  a HTML representation of the specified
     *          {@link StoreSales} object.
     */
    @Override
    public String formatOrders(StoreSales storeSales) {

        String out = "<html>"
                + NEW_LINE
                + "  <body>"
                + NEW_LINE + ""
                + "    <center><h2>Store's Sale</h2></center>"
                + NEW_LINE;
        for (Order order : storeSales) {
            out += "    <hr>"
                    + NEW_LINE;
            if (order.getNumberOfItems() > 0) {
                out += "      <blockquote>" + NEW_LINE;

                double total = order.getTotal();
                for (SaleItem saleItem : order) {

                    Product product = saleItem.getProduct();
                    out += "         "
                            + product.getCode()
                            + " "
                            + product.getDescription()
                            + " "
                            + product.getPrice()
                            + " "
                            + saleItem.getQuantity()
                            + "<br>"
                            + NEW_LINE;
                }
                out += "         total:" + total + NEW_LINE + "      </blockquote>" + NEW_LINE;
            }
        }
        out += "  </body>" + NEW_LINE + "</html>";

        return out;
    }
}
/*!End Snippet:file*/
