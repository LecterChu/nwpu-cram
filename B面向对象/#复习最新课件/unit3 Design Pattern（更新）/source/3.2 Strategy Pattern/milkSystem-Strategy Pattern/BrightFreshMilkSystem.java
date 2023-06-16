/*!Begin Snippet:file*/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.text.ParseException;
import java.text.SimpleDateFormat;

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
 */
public class BrightFreshMilkSystem {

    private static BufferedReader stdIn =
            new  BufferedReader(new InputStreamReader(System.in));
    private static PrintWriter stdOut = new  PrintWriter(System.out, true);
    private static PrintWriter  stdErr = new  PrintWriter(System.err, true);

    private StoreSales storeSales;

    private OrdersFormatter ordersFormatter;

    /**
     * Loads a product catalog and store's sales and then
     * starts the application.
     *
     * @param args  String arguments.  Not used.
     * @throws IOException if there are errors in the input.
     */
    public static void main(String[] args) throws IOException {

        BrightFreshMilkSystem  app = new BrightFreshMilkSystem();

        app.run();
    }

    /**
     * Creates a <code>BrightFreshMilkSystem</code> object.
     */
    private BrightFreshMilkSystem() {

        try {
            storeSales = load(load());
        } catch (ParseException e) {
            e.printStackTrace();
        }
        ordersFormatter = PlainTextOrdersFormatter.getSingletonInstance();
    }

    /**
     * Loads product catalog data.
     */
    private static ProductCatalog load() throws ParseException {

        ProductCatalog productCatalog = new ProductCatalog();

        SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd");
        productCatalog.addProduct(new PureMilk("A001","skim milk,800ml",18,
                simpleDateFormat.parse("2020-8-7"),"45days","Germany","0.01%","0.051%"));
        productCatalog.addProduct(new PureMilk("A002","nutritional balance,500ml",16,
                simpleDateFormat.parse("2020-7-21"),"45days","France","0.12%","0.32%"));
        productCatalog.addProduct(new PureMilk("A003","original milk,900ml",21,
                simpleDateFormat.parse("2020-7-25"),"30days","China","0.11%","0.35%"));
        productCatalog.addProduct(new PureMilk("A004","organic milk,200ml",6,
                simpleDateFormat.parse("2020-8-14"),"30days","China","0.32%","0.67%"));
        productCatalog.addProduct(new PureMilk("A005","every benefit milk,300ml",8.9,
                simpleDateFormat.parse("2020-6-20"),"15days","China","0.23%","0.51%"));

        productCatalog.addProduct(new Jelly("B001","solid,250ml",8.5,
                simpleDateFormat.parse("2020-8-1"),"9months","0.23%"));
        productCatalog.addProduct(new Jelly("B002","coconut flavor,250ml",6.5,
                simpleDateFormat.parse("2020-7-16"),"9months","0.33%"));
        productCatalog.addProduct(new Jelly("B003","grape taste,200ml",7,
                simpleDateFormat.parse("2020-8-10"),"9months","0.56%"));
        productCatalog.addProduct(new Jelly("B004","suck jelly,230ml",8,
                simpleDateFormat.parse("2020-8-8"),"9months","1.02%"));
        productCatalog.addProduct(new Jelly("B005","real fruit,300ml",9.5,
                simpleDateFormat.parse("2020-7-2"),"12months","0.55%"));

        productCatalog.addProduct(new MilkDrink("C001","chocolate flavor,270ml",5,
                simpleDateFormat.parse("2020-8-9"),"12months","0.34%","0.52%"));
        productCatalog.addProduct(new MilkDrink("C002","vanilla flavor,300ml",6,
                simpleDateFormat.parse("2020-8-5"),"9months","0.54%","0.32%"));
        productCatalog.addProduct(new MilkDrink("C003","nectarine flavor,180ml",3.9,
                simpleDateFormat.parse("2020-8-12"),"9months","0.62%","0.92%"));
        productCatalog.addProduct(new MilkDrink("C004","soy sauce,280ml",3.5,
                simpleDateFormat.parse("2020-8-4"),"9months","0.33%","0.12%"));
        productCatalog.addProduct(new MilkDrink("C005","apple flavor,280ml",4,
                simpleDateFormat.parse("2020-7-5"),"6months","0.34%","1.2%"));

        productCatalog.addProduct(new Yogurt("D001","taro flavor,250ml",13.1,
                simpleDateFormat.parse("2020-8-2"),"7days","A1","2.2%"));
        productCatalog.addProduct(new Yogurt("D002","mango flavor,280ml",12.6,
                simpleDateFormat.parse("2020-8-2"),"7days","A2","1.32%"));
        productCatalog.addProduct(new Yogurt("D003","with fruit,250ml",9.1,
                simpleDateFormat.parse("2020-8-11"),"7days","A3","1.2%"));
        productCatalog.addProduct(new Yogurt("D004","peach flavor,220ml",7,
                simpleDateFormat.parse("2020-8-9"),"7days","A4","2.06%"));
        productCatalog.addProduct(new Yogurt("D005","grape flavor,310ml",3.5,
                simpleDateFormat.parse("2020-7-23"),"7days","A5","1.8%"));

        return productCatalog;
    }

    /**
     * Loads a storeSales object.
     */
    private static StoreSales load(ProductCatalog productCatalog) {

        StoreSales storeSales = new StoreSales();

        Order currentOrder = new Order();

        currentOrder.addSaleItem(new SaleItem(2,productCatalog.getProduct("A002")));
        currentOrder.addSaleItem(new SaleItem(3,productCatalog.getProduct("C001")));
        currentOrder.addSaleItem(new SaleItem(1,productCatalog.getProduct("D001")));
        currentOrder.addSaleItem(new SaleItem(3,productCatalog.getProduct("B001")));
        storeSales.addOrder(currentOrder);

        currentOrder = new Order();
        currentOrder.addSaleItem(new SaleItem(1,productCatalog.getProduct("A005")));
        currentOrder.addSaleItem(new SaleItem(2,productCatalog.getProduct("C002")));
        currentOrder.addSaleItem(new SaleItem(3,productCatalog.getProduct("D004")));
        currentOrder.addSaleItem(new SaleItem(3,productCatalog.getProduct("B003")));
        storeSales.addOrder(currentOrder);

        currentOrder = new Order();
        currentOrder.addSaleItem(new SaleItem(1,productCatalog.getProduct("A001")));
        currentOrder.addSaleItem(new SaleItem(2,productCatalog.getProduct("C001")));
        currentOrder.addSaleItem(new SaleItem(3,productCatalog.getProduct("D003")));
        currentOrder.addSaleItem(new SaleItem(3,productCatalog.getProduct("B005")));
        storeSales.addOrder(currentOrder);

        currentOrder = new Order();
        currentOrder.addSaleItem(new SaleItem(1,productCatalog.getProduct("A004")));
        currentOrder.addSaleItem(new SaleItem(2,productCatalog.getProduct("C005")));
        currentOrder.addSaleItem(new SaleItem(3,productCatalog.getProduct("D002")));
        currentOrder.addSaleItem(new SaleItem(3,productCatalog.getProduct("B002")));
        storeSales.addOrder(currentOrder);

        return storeSales;
    }

    /**
     * Presents the user with a menu of options and executes the
     * selected task.
     */
    private void run() throws IOException {

        int choice = getChoice();

        while (choice != 0)  {

            if (choice == 1)  {
                setOrdersFormatter(
                        PlainTextOrdersFormatter.getSingletonInstance());
            } else if (choice == 2)  {
                setOrdersFormatter(
                        HTMLOrdersFormatter.getSingletonInstance());
            } else if (choice == 3)  {
                setOrdersFormatter(
                        XMLOrdersFormatter.getSingletonInstance());
            }
            displayOrders();

            choice = getChoice();
        }
    }

    /**
     * Displays a menu of options and verifies the user's choice.
     *
     * @return an integer in the range [0,3]
     */
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

    /**
     * Changes the format in which the store's sales will be
     * displayed.
     *
     * @param newFormatter format in which the store's sales will
     *                     be displayed.
     */
    private void setOrdersFormatter(
            OrdersFormatter newFormatter){

        ordersFormatter = newFormatter;
    }

    /**
     * Displays the orders in the current format.
     */
    private void displayOrders() {

        stdOut.println(
                ordersFormatter.formatOrders(storeSales));
    }
}
/*!End Snippet:file*/
