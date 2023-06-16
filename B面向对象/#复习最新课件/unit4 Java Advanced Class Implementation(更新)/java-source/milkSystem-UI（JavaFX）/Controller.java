/*!Begin Snippet:file*/

import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.*;
import java.net.URL;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Iterator;
import java.util.ResourceBundle;
import java.util.StringTokenizer;

/**
 * This class defines some components and their corresponding
 * event handling.
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
public class Controller implements Initializable {

    /* TextField component for the name of user . */
    @FXML
    private TextField username;

    /* TextField component for password.*/
    @FXML
    private TextField password;

    /* Button component for login in.*/
    @FXML
    private Button login;

    /* Button component for sign out.*/
    @FXML
    private Button logout;

    /* ListView component for list of products.*/
    @FXML
    private ListView<String> productsList;

    /* ListView component for list of orders.*/
    @FXML
    private ListView<String> orderList;

    /* Button component for add product.*/
    @FXML
    private Button addProduct;

    /* Button component for remove product.*/
    @FXML
    private Button removeProduct;

    /* Label component for total.*/
    @FXML
    private Label totalText;

    /* TextArea component for product.*/
    @FXML
    private TextArea productText;

    /* Label component for code of product.*/
    @FXML
    private Label codeText;

    /* Button component for submit.*/
    @FXML
    private Button submit;

    /* ListView component for list of sales.*/
    @FXML
    private ListView salesList;

    /* Line separator */
    private final static String NEW_LINE = System.getProperty("line.separator");

    private ProductCatalog productCatalog;

    private Order order = new Order(0);

    private StoreSales storeSales = new StoreSales();

    private static int loginStatus = 0;

    /**
     * Loads the information of the product catalog. Define
     * event listening for some components.
     *
     * @param url Not used.
     * @param resourceBundle Not used.
     */
    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {

        try {
            productCatalog = load();
            displayCatalog(productCatalog);
        } catch (ParseException e) {
            e.printStackTrace();
        }

        login.setOnMouseClicked(e->{

            if (loginStatus == 1) {
                alert("您已经登录！");
            } else {
                if ("".equals(username.getText()) || "".equals(password.getText())) {
                    alert("请输入用户名和密码！");
                } else {
                    if ("123".equals(username.getText()) && "123".equals(password.getText())){
                        loginStatus = 1;
                        displayOrder(order);
                        displaySales();
                        username.clear();
                        password.clear();
                        alert("登录成功！");
                    } else {
                        alert("用户名或密码错误！");
                    }
                }
            }
        });

        logout.setOnMouseClicked(e->{
            if (loginStatus == 1) {
                loginStatus = 0;
                displayOrder(order);
                displaySales();
                alert("退出成功！");
            }
        });

        productsList.getSelectionModel().selectedItemProperty().addListener(e->{

            String productInfo = productsList.getSelectionModel().getSelectedItem();

            if (productInfo != null) {
                StringTokenizer tokenizer =	new StringTokenizer(productInfo, "_");
                if (tokenizer.countTokens() == 3) {
                    String code = tokenizer.nextToken();
                    Product product = productCatalog.getProduct(code);
                    StringBuilder stringBuilder = new StringBuilder();
                    stringBuilder.append("  Description: " + product.getDescription() + NEW_LINE +
                                        "  Price: "  + product.getPrice() + NEW_LINE +
                                        "  Production date: " + product.getProductionDate() + NEW_LINE +
                                        "  Shelf life: " + product.getShelfLife());
                    if (product instanceof Jelly) {

                        Jelly jelly = (Jelly) product;

                        stringBuilder.append(NEW_LINE + "  Flavor: " + jelly.getFlavor());
                    } else if (product instanceof MilkDrink) {

                        MilkDrink milkDrink = (MilkDrink) product;

                        stringBuilder.append(NEW_LINE + "  Flavor: " + milkDrink.getFlavor());
                        stringBuilder.append(NEW_LINE + "  Sugar: " + milkDrink.getSugar());
                    } else if (product instanceof PureMilk) {

                        PureMilk pureMilk = (PureMilk) product;

                        stringBuilder.append(NEW_LINE + "  Country of origin: " + pureMilk.getCountryOfOrigin());
                        stringBuilder.append(NEW_LINE + "  Butterfat: " + pureMilk.getButterfat());
                        stringBuilder.append(NEW_LINE + "  Protein: " + pureMilk.getProtein());
                    } else if (product instanceof Yogurt) {

                        Yogurt yogurt = (Yogurt) product;

                        stringBuilder.append(NEW_LINE + "  Type: " + yogurt.getType());
                        stringBuilder.append(NEW_LINE + "  Dilute concentration: " + yogurt.getDiluteConcentration());
                    }
                    productText.setText(stringBuilder.toString());
                    codeText.setText(code);
                }
            }
        });

        addProduct.setOnMouseClicked(e->{

            if (loginStatus == 1) {

                String productInfo = productsList.getSelectionModel().getSelectedItem();
                if (productInfo != null) {
                    StringTokenizer tokenizer =	new StringTokenizer(productInfo, "_");
                    if (tokenizer.countTokens() == 3) {
                        String code = tokenizer.nextToken();
                        Product product = productCatalog.getProduct(code);

                        if (order == null) {

                        } else {
                            SaleItem saleItem = order.getProductSaleList().getSaleItem(code);

                            if (saleItem == null) {
                                order.getProductSaleList().addSaleItem(new SaleItem(1, product));
                            } else {
                                saleItem.setQuantity(saleItem.getQuantity() + 1);
                            }
                        }
                        displayOrder(order);
                        totalText.setText("Total: $" + order.getTotal());
                    }
                } else {
                    alert("请选择要添加的商品！");
                }
            } else {
                alert("您还未登录，请先登录！");
            }

        });

        removeProduct.setOnMouseClicked(e->{
            String saleItemInfo = orderList.getSelectionModel().getSelectedItem();
            if (saleItemInfo != null) {
                StringTokenizer tokenizer = new StringTokenizer(saleItemInfo,"_");
                if (tokenizer.countTokens() == 4) {
                    int quantity = Integer.parseInt(tokenizer.nextToken());
                    String code = tokenizer.nextToken();

                    SaleItem saleItem = order.getProductSaleList().getSaleItem(code);

                    order.getProductSaleList().removeSaleItem(saleItem);

                    displayOrder(order);
                    totalText.setText("Total: $" + order.getTotal());
                }
            }else {
                alert("请选择要移除的商品！");
            }
        });

        totalText.setText("Total: $0.0");

        submit.setOnMouseClicked(e->{

            if (loginStatus == 1) {
                if (order.getProductSaleList().getNumberOfItems() != 0) {
                    Order currentOrder = new Order(0);
                    for (SaleItem saleItem : order.getProductSaleList()) {
                        currentOrder.getProductSaleList().addSaleItem(saleItem);
                    }
                    this.storeSales.addOrder(currentOrder);
                    order.getProductSaleList().clearSaleItem();
                    displayOrder(order);
                    displaySales();
                    totalText.setText("Total: $" + order.getTotal());
                } else {
                    alert("请先向订单中添加产品！");
                }
            } else {
                alert("您还未登录，请先登录！");
            }
        });
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
     * Displays the catalog.
     */
    private void displayCatalog(ProductCatalog productCatalog) {

        if (productCatalog.getNumberOfProducts() != 0) {

            Iterator<Product> iterator = productCatalog.iterator();
            for (; iterator.hasNext();) {
                Product product =  iterator.next();
                productsList.getItems().add(product.getCode() + "_" + product.getDescription() +
                                            "_" + product.getPrice());
            }
        }
    }

    /*
     * Displays the current order.
     */
    private void displayOrder(Order currentOrder) {

        orderList.getItems().clear();

        if (loginStatus == 1) {
            if (currentOrder.getProductSaleList().getNumberOfItems() != 0) {

                double total = currentOrder.getTotal();

                for (SaleItem saleItem : currentOrder.getProductSaleList()) {

                    Product product = saleItem.getProduct();
                    orderList.getItems().add(saleItem.getQuantity() + "_" + product.getCode() + "_"
                            + product.getDescription()  + "_" + product.getPrice());
                }

            }
        }
    }

    /*
     * Display all the orders that have been sold.
     */
    private void displaySales() {

        salesList.getItems().clear();

        if (loginStatus == 1) {
            if (this.storeSales.getNumberOfOrders() != 0) {

                Iterator<Order> iterator = this.storeSales.iterator();
                for (;iterator.hasNext();) {
                    Order order = iterator.next();
                    double total = order.getTotal();
                    String content = "";
                    for (SaleItem saleItem : order.getProductSaleList()) {
                        content += saleItem.getProduct().getCode() + "(" + saleItem.getQuantity() + ")" + "_";
                    }
                    content += total;
                    salesList.getItems().add(content);
                }
            }
        }
    }

    /*
     * User prompt window.
     */
    public void alert(String msg){

        Alert alert = new Alert(Alert.AlertType.INFORMATION, msg,
                new ButtonType("确定", ButtonBar.ButtonData.YES));
        alert.setHeaderText(null);
        alert.setTitle("提示");
        alert.show();
    }
}
/*!End Snippet:file*/