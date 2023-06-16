/*!Begin Snippet:file*/

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Iterator;

/**
 * This class implements a milk system.
 *
 * @author ydecube
 * @version 1.1.0
 * @see Jelly
 * @see MilkDrink
 * @see Order
 * @see Product
 * @see ProductCatalog
 * @see ProductSaleList
 * @see PureMilk
 * @see SaleItem
 * @see StoreSales
 * @see Yogurt
 */
public class BrightFreshMilkSystem {

    private static BufferedReader stdIn =
            new  BufferedReader(new InputStreamReader(System.in));
    private static PrintWriter stdOut = new  PrintWriter(System.out, true);
    private static PrintWriter  stdErr = new  PrintWriter(System.err, true);

    private ProductCatalog productCatalog;
    private Order currentOrder;
    private StoreSales storeSales = new StoreSales();

    /**
     * Loads the information of the product catalog,current order and
     * store's sales and starts the application.
     *
     * @param args  String arguments.  Not used.
     * @throws IOException if there are errors in the input.
     */
    public static void main(String[] args) throws IOException, ParseException {

        ProductCatalog productCatalog  = load();

        Order order = load(productCatalog);

        BrightFreshMilkSystem  app = new BrightFreshMilkSystem(productCatalog,order);

        app.run();
    }

    /*
     * Constructs a <code>BrightFreshMilkSystem</code> object.
     * Initialize the product catalog, order and the store's sales with
     * the values specified in the parameters.
     */
    public BrightFreshMilkSystem(ProductCatalog initialProductCatalog, Order initialOrder) {

        this.productCatalog = initialProductCatalog;
        this.currentOrder = initialOrder;
    }

    /*
     * Loads the information of a product catalog object.
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

    /*
     * Loads an order object.
     */
    private static Order load(ProductCatalog productCatalog) {

        Order currentOrder = new Order();

        currentOrder.addSaleItem(new SaleItem(2,productCatalog.getProduct("A002")));
        currentOrder.addSaleItem(new SaleItem(3,productCatalog.getProduct("C001")));
        currentOrder.addSaleItem(new SaleItem(1,productCatalog.getProduct("D001")));
        currentOrder.addSaleItem(new SaleItem(3,productCatalog.getProduct("B001")));

        return currentOrder;
    }

    /*
     * Presents the user with a menu of options and processes the selection.
     */
    private void run() throws IOException {

        int choice = getChoice();

        while (choice != 0)  {

            if (choice == 1)  {
                displayCatalog();
            } else if (choice == 2)  {
                displayProduct();
            } else if (choice == 3)  {
                displayOrder();
            } else if (choice == 4)  {
                addProduct();
            } else if (choice == 5)  {
                removeProduct();
            } else if (choice == 6)  {
                addOrder();
            } else if (choice == 7)  {
                displaySales();
            }

            choice = getChoice();
        }
    }

    /* Validates the user's choice. */
    private int  getChoice() throws IOException  {

        int  input;

        do  {
            try  {
                stdErr.println();
                stdErr.print("[0]  Quit\n"
                        + "[1]  Display catalog\n"
                        + "[2]  Display product\n"
                        + "[3]  Display order\n"
                        + "[4]  Add product\n"
                        + "[5]  Remove product\n"
                        + "[6]  Add order\n"
                        + "[7]  Display sales\n"
                        + "choice> ");
                stdErr.flush();

                input = Integer.parseInt(stdIn.readLine());

                stdErr.println();

                if (0 <= input && 7 >= input)  {
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
     * Display all the orders that have been sold.
     */
    private void displaySales() {

        if (storeSales == null || this.storeSales.getNumberOfOrders() == 0) {
            stdErr.println("There is no sales in the store for the time being");
        } else {
            Iterator<Order> iterator = this.storeSales.iterator();
            for (;iterator.hasNext();) {
                Order order = iterator.next();
                double total = order.getTotal();
                String title = "Quantity" + "|" + "Code" + "|" + "Description" + "|" + "Price";
                String content = "";
                for (SaleItem saleItem : order) {
                    content += System.getProperty("line.separator") + saleItem.toString();
                }

                stdOut.println(title + content + " total:" + total);
            }
        }
    }

    /*
     * Add the current order to the store's sales.
     */
    private void addOrder() {

        if (this.currentOrder.getNumberOfItems() != 0) {
            Order order = new Order();
            for (SaleItem saleItem : this.currentOrder) {
                order.addSaleItem(saleItem);
            }
            this.storeSales.addOrder(order);
            this.currentOrder.clearSaleItem();
            stdOut.println("Successfully added the order to the store sales");
        } else {

            stdErr.println("The current order is null. Please add the product to the order");
        }
    }

    /*
     * Remove a product from the current order.
     */
    private void removeProduct() throws IOException {

        Product product = readProduct();

        if (product == null) {
            stdErr.println("There is no product with that code");
        } else {

            SaleItem saleItem = this.currentOrder.getSaleItem(product.getCode());

            if (saleItem == null) {
                stdErr.println("The product is not included in the order");
            } else {
                this.currentOrder.removeSaleItem(saleItem);
                stdOut.println("The product " + product.getCode() +
                        " has been removed from the current order");
            }
        }
    }

    /*
     * Add a product to the current order.
     */
    private void addProduct() throws IOException {

        Product product = readProduct();

        if (product == null) {
            stdErr.println("There is no product with that code");
        } else {

            SaleItem saleItem = this.currentOrder.getSaleItem(product.getCode());

            if (saleItem == null) {
                this.currentOrder.addSaleItem(new SaleItem(1, product));
            } else {
                saleItem.setQuantity(saleItem.getQuantity() + 1);
            }

            stdOut.println("The product " + product.getCode()
                    + " has been added to the current order");
        }
    }

    /*
     * Displays the current order.
     */
    private void displayOrder() {

        if (currentOrder.getNumberOfItems() == 0) {
            stdErr.println("The current order is empty");
        } else {
            double total = this.currentOrder.getTotal();
            String title = "Quantity" + "|" + "Code" + "|" + "Description" + "|" + "Price";
            String content = "";
            for (SaleItem saleItem : this.currentOrder) {
                content += System.getProperty("line.separator") + saleItem.toString();
            }

            stdOut.println(title + content + " total:" + total);
        }
    }

    /*
     * Displays the information of a product.
     */
    private void displayProduct() throws IOException {

        Product product = readProduct();

        if (product != null) {
            stdOut.println("  Code: " + product.getCode());
            stdOut.println("  Description: " + product.getDescription());
            stdOut.println("  Price: " + product.getPrice());
            stdOut.println("  Production date: " + product.getProductionDate());
            stdOut.println("  Shelf life: " + product.getShelfLife());
            if (product instanceof Jelly) {

                Jelly jelly = (Jelly) product;

                stdOut.println("  Flavor: " + jelly.getFlavor());
            } else if (product instanceof MilkDrink) {

                MilkDrink milkDrink = (MilkDrink) product;

                stdOut.println("  Flavor: " + milkDrink.getFlavor());
                stdOut.println("  Sugar: " + milkDrink.getSugar());
            } else if (product instanceof PureMilk) {

                PureMilk pureMilk = (PureMilk) product;

                stdOut.println("  Country of origin: " + pureMilk.getCountryOfOrigin());
                stdOut.println("  Butterfat: " + pureMilk.getButterfat());
                stdOut.println("  Protein: " + pureMilk.getProtein());
            } else if (product instanceof Yogurt) {

                Yogurt yogurt = (Yogurt) product;

                stdOut.println("  Type: " + yogurt.getType());
                stdOut.println("  Dilute concentration: " + yogurt.getDiluteConcentration());
            }
        } else {
            stdErr.println("There is no product with that code");
        }
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
     * Obtains a Product object  .
     */
    private  Product readProduct() throws IOException  {

        stdErr.print("Product code> ");
        stdErr.flush();

        return this.productCatalog.getProduct(stdIn.readLine());
    }
}
/*!End Snippet:file*/
