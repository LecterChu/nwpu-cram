/*!Begin Snippet:file*/

/**
 * This class implements a method that obtains a XML
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
public class XMLOrdersFormatter implements OrdersFormatter {

    /* Line separator */
    private final static String NEW_LINE = System.getProperty("line.separator");

    /* single instance of this class */
    static private XMLOrdersFormatter singletonInstance = null;

    /**
     * Obtains the single instance of class
     * <code>XMLOrdersFormatter</code>
     *
     * @return the single instance  of class
     *         <code>XMLOrdersFormatter</code>
     */
    static public XMLOrdersFormatter getSingletonInstance() {

        if (singletonInstance == null) {
            singletonInstance = new XMLOrdersFormatter();
        }

        return singletonInstance;
    }

    /*
     * The constructor is declared private so other classes cannot
     * create an instance of this class.
     */
    private XMLOrdersFormatter() {

    }

    /**
     * Obtains a XML representation of the store's sales.
     *
     * @param storeSales  the store's sales.
     * @return  a XML representation of the specified
     *          {@link StoreSales} object.
     */
    @Override
    public String formatOrders(StoreSales storeSales) {

        String out = "<StoreSales>" + NEW_LINE;

        for (Order order : storeSales) {
            out += "  <Order total=\""
                    + order.getTotal()
                    + "\">"
                    + NEW_LINE;

                if (order.getNumberOfItems() > 0) {
                out += "    <ProductSaleList>" + NEW_LINE;

                for (SaleItem saleItem : order) {
                    out += "      <SaleItem quantity=\""
                            + saleItem.getQuantity()
                            + "\">"
                            + saleItem.getProduct().getCode()
                            + " "
                            + saleItem.getProduct().getDescription()
                            + " "
                            + saleItem.getProduct().getPrice()
                            + "</SaleItem>" + NEW_LINE;
                }
                out += "    </ProductSaleList>" + NEW_LINE;
            }
            out += "  </Order>" + NEW_LINE;
        }
        out += "</StoreSales>";

        return out;
    }
}
/*!End Snippet:file*/
