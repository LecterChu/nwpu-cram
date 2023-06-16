public class BrightFreshMilkSystemSolution {
    ...
    private StoreSales storeSales;
    ...
    public static void main(String[] args) throws IOException {

        BrightFreshMilkSystem  app = new BrightFreshMilkSystem();

        app.run();
    }

    ...

    public String formatOrders (String strFormat) {

        String out;

        if (strFormat.equals("plain text")) {

            out = "Store's Sales" + NEW_LINE;

            for (Order order : storeSales) {

                double total = order.getTotal();

                for (SaleItem saleItem : order.getProductSaleList()) {

                    Product product = saleItem.getProduct();

                    out += product.getCode() + "_" + product.getDescription() + "_"
                            + product.getPrice() + "_" + saleItem.getQuantity();

                    out += NEW_LINE;
                }
                out += "total:" + total + NEW_LINE;
            }
        } else if (strFormat.equals("HTML")) {

            out = "<html>"
                    + NEW_LINE
                    + "  <body>"
                    + NEW_LINE + ""
                    + "    <center><h2>Store's Sale</h2></center>"
                    + NEW_LINE;

            for (Order order : storeSales) {

                out += "    <hr>"
                        + NEW_LINE;

                if (order.getProductSaleList().getNumberOfItems() > 0) {
                    out += "      <blockquote>" + NEW_LINE;

                    double total = order.getTotal();

                    for (SaleItem saleItem : order.getProductSaleList()) {

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

        } else if (strFormat.equals("XML")) {

            out = "<StoreSales>" + NEW_LINE;

            for (Order order : storeSales) {

                out += "  <Order total=\""
                        + order.getTotal()
                        + "\">"
                        + NEW_LINE;

                ProductSaleList list = order.getProductSaleList();

                if (list.getNumberOfItems() > 0) {

                    out += "    <ProductSaleList>" + NEW_LINE;

                    for (SaleItem saleItem : list) {

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
        }

        return out;
    }

    private void run() throws IOException {

        int choice = getChoice();

        while (choice != 0)  {

            if (choice == 1)  {
                String out = app.formatOrders("plain text",storeSales);
                ...
            } else if (choice == 2)  {
                app.formatOrders("plain text",storeSales);
                ...
            } else if (choice == 3)  {
                app.formatOrders("plain text",storeSales);
                ...
            }
            ...

            choice = getChoice();
        }
    }

    private int  getChoice() throws IOException  {

        int input;

        do  {
            try  {
                stdErr.println();
                stdErr.print("[0]  Quit\n"
                        + "[1]  Display Plain Text\n"
                        + "[2]  Display HTML\n"
                        + "[3]  Display XML\n"
                        + "choice> ");
                stdErr.flush();

                input = Integer.parseInt(stdIn.readLine());

                stdErr.println();

                if (0 <= input && 3 >= input)  {
                    break;
                } else {
                    stdErr.println("Invalid choice:  " + input);
                }
            } catch (NumberFormatException  nfe)  {
                stdErr.println(nfe);
            }
        }  while (true);

        return  input;
    }
}
