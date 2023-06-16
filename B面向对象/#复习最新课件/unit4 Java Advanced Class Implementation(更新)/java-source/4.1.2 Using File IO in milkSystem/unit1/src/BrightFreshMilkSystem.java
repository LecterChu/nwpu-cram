/*!Begin Snippet:file*/


import java.io.*;
import java.util.Iterator;

/**
 * This class implements a milk system.
 *
 * @author ydecube
 * @version 1.1.0
 * @see Jelly
 * @see MilkDrink
 * @see Yogurt
 * @see PureMilk
 * @see Product
 * @see ProductCatalog
 * @see Order
 * @see ProductSaleList
 * @see SaleItem
 * @see StoreSales
 * @see OrdersFormatter
 * @see PlainTextOrdersFormatter
 * @see HTMLOrdersFormatter
 * @see XMLOrdersFormatter
 * @see MilkProductCatalogLoader
 * @see FileMilkProductCatalogLoader
 */
public class BrightFreshMilkSystem {

    private static BufferedReader stdIn =
            new  BufferedReader(new InputStreamReader(System.in));
    private static PrintWriter stdOut =
            new  PrintWriter(System.out, true);
    private static PrintWriter  stdErr =
            new  PrintWriter(System.err, true);

    private ProductCatalog productCatalog;

    private StoreSales storeSales;

    private OrdersFormatter ordersFormatter;

    /**
     * Loads a product catalog and store's sales from a file
     * and then starts the application.
     * <p>
     * The name of the file is specified in the command arguments
     * </p>
     *
     * @param args  String arguments.
     * @throws IOException if there are errors in the input.
     */
    public static void main(String[] args) throws IOException {

        if (args.length != 1) {
            stdErr.println("Usage: java BrightFreshMilkSystem filename");
        } else {

            ProductCatalog productCatalog = null;

            try {
                MilkProductCatalogLoader loader =
                        new FileMilkProductCatalogLoader();

                productCatalog = loader.loadCatalog(args[0]);
            } catch (FileNotFoundException fnfe) {
                stdErr.println("The file does not exist");

                System.exit(1);

            } catch (DataFormatException dfe) {
                stdErr.println("The file contains malformed data: "
                        + dfe.getMessage());

                System.exit(1);
            }

            BrightFreshMilkSystem  app = new BrightFreshMilkSystem(productCatalog);

            app.run();
        }
    }

    /*
     * Constructs a <code>BrightFreshMilkSystem</code> object.
     * Initialize the product catalog and store's sales with
     * the values specified in the parameter.
     */
    private BrightFreshMilkSystem(ProductCatalog initialProductCatalog) {

        productCatalog = initialProductCatalog;

        storeSales = load(productCatalog);
        ordersFormatter =
                PlainTextOrdersFormatter.getSingletonInstance();
    }

    /*
     * Loads a storeSales object.
     */
    private static StoreSales load(ProductCatalog productCatalog) {

        StoreSales storeSales = new StoreSales();

        Order currentOrder = new Order(0);

        currentOrder.getProductSaleList().addSaleItem(new SaleItem(2,productCatalog.getProduct("A002")));
        currentOrder.getProductSaleList().addSaleItem(new SaleItem(3,productCatalog.getProduct("C001")));
        currentOrder.getProductSaleList().addSaleItem(new SaleItem(1,productCatalog.getProduct("D001")));
        currentOrder.getProductSaleList().addSaleItem(new SaleItem(3,productCatalog.getProduct("B001")));
        storeSales.addOrder(currentOrder);

        currentOrder = new Order(0);
        currentOrder.getProductSaleList().addSaleItem(new SaleItem(2,productCatalog.getProduct("A005")));
        currentOrder.getProductSaleList().addSaleItem(new SaleItem(2,productCatalog.getProduct("C002")));
        currentOrder.getProductSaleList().addSaleItem(new SaleItem(4,productCatalog.getProduct("D004")));
        currentOrder.getProductSaleList().addSaleItem(new SaleItem(1,productCatalog.getProduct("B003")));
        storeSales.addOrder(currentOrder);

        currentOrder = new Order(0);
        currentOrder.getProductSaleList().addSaleItem(new SaleItem(1,productCatalog.getProduct("A001")));
        currentOrder.getProductSaleList().addSaleItem(new SaleItem(5,productCatalog.getProduct("C001")));
        currentOrder.getProductSaleList().addSaleItem(new SaleItem(1,productCatalog.getProduct("D003")));
        currentOrder.getProductSaleList().addSaleItem(new SaleItem(2,productCatalog.getProduct("B005")));
        storeSales.addOrder(currentOrder);

        currentOrder = new Order(0);
        currentOrder.getProductSaleList().addSaleItem(new SaleItem(1,productCatalog.getProduct("A004")));
        currentOrder.getProductSaleList().addSaleItem(new SaleItem(1,productCatalog.getProduct("C005")));
        currentOrder.getProductSaleList().addSaleItem(new SaleItem(1,productCatalog.getProduct("D002")));
        currentOrder.getProductSaleList().addSaleItem(new SaleItem(3,productCatalog.getProduct("B002")));
        storeSales.addOrder(currentOrder);

        currentOrder = new Order(0);
        currentOrder.getProductSaleList().addSaleItem(new SaleItem(3,productCatalog.getProduct("A002")));
        currentOrder.getProductSaleList().addSaleItem(new SaleItem(2,productCatalog.getProduct("C004")));
        currentOrder.getProductSaleList().addSaleItem(new SaleItem(1,productCatalog.getProduct("D001")));
        currentOrder.getProductSaleList().addSaleItem(new SaleItem(1,productCatalog.getProduct("B002")));
        storeSales.addOrder(currentOrder);

        return storeSales;
    }

    /*
     * Presents user with menu of options and executes selected task.
     */
    private void run() throws IOException  {

        int  choice = getChoice();

        while (choice != 0)  {
            if (choice == 1)  {
                displayCatalog();
            } else if (choice == 2)  {
                this.ordersFormatter =
                        PlainTextOrdersFormatter.getSingletonInstance();
                writeFile(readFileName(),
                        this.ordersFormatter.formatOrders(this.storeSales));
            } else if (choice == 3)  {
                this.ordersFormatter =
                        HTMLOrdersFormatter.getSingletonInstance();
                writeFile(readFileName(),
                        this.ordersFormatter.formatOrders(this.storeSales));
            } else if (choice == 4)  {
                this.ordersFormatter =
                        XMLOrdersFormatter.getSingletonInstance();
                writeFile(readFileName(),
                        this.ordersFormatter.formatOrders(this.storeSales));
            }

            choice = getChoice();
        }
    }

    /*
     * Displays a menu of options and verifies the user's choice.
     */
    private int  getChoice() throws IOException  {

        int  input;

        do  {
            try  {
                stdErr.println();
                stdErr.print("[0]  Quit\n"
                        + "[1]  Display product catalog\n"
                        + "[2]  Save store's sales (plain text)\n"
                        + "[3]  Save store's sales (HTML)\n"
                        + "[4]  Save store's sales (XML)\n"
                        + "choice> ");
                stdErr.flush();

                input = Integer.parseInt(stdIn.readLine());

                stdErr.println();

                if (0 <= input && 4 >= input)  {
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

    /*
     * Displays the catalog.
     */
    private void displayCatalog() {

        if (this.productCatalog.getNumberOfProducts() == 0) {
            stdErr.println("The catalog is empty");
        } else {
            Iterator<Product> iterator = this.productCatalog.iterator();
            for (; iterator.hasNext();) {
                Product product =  iterator.next();
                stdOut.println(product.getCode() + " " + product.getDescription() + " "
                        + product.getProductionDate());
            }
        }
    }

    /*
     * Prompts the user for a file name (the name of the file that
     * will store the store's sales) and returns the user's
     * response.
     */
    public String readFileName() throws IOException  {

        stdErr.print("File name> ");
        stdErr.flush();

        return stdIn.readLine();
    }

    /*
     * Creates a new file (which has the specified name) and writes
     * the specified string to the new file
     */
    public void writeFile(String fileName, String content)
            throws IOException {

        PrintWriter fileOut =
                new PrintWriter(new FileWriter(fileName));

        fileOut.println(content);

        fileOut.close();
    }
}
/*!End Snippet:file*/