/*!Begin Snippet:file*/

import java.util.ArrayList;
import java.util.Iterator;

/**
 * Maintains the information of a product catalog for a milk store.
 * Contains a collection of {@link Product} objects.
 *
 * @author ydecube
 * @version  1.0.0
 * @see Product
 */
public class ProductCatalog implements Iterable<Product>{

    /* Collection of <code>Product</code> objects.*/
    private ArrayList<Product> products;

    /**
     * Constructs an empty product catalog.
     */
    public ProductCatalog() {

        this.products = new ArrayList<Product>();
    }

    /**
     * Adds a {@link Product} object to this product catalog.
     *
     * @param product  the {@link Product} object.
     */
    public void addProduct(Product product) {

        this.products.add(product);
    }

    /**
     * Removes a {@link Product} object from this collection.
     *
     * @param product  the {@link Product} object.
     */
    public void removeProduct(Product product) {

        this.products.remove(product);
    }

    /**
     * Returns an iterator over the products in this product catalog.
     *
     * return  an {@link Iterator} of {@link Product}
     */
    @Override
    public Iterator<Product> iterator() {

        return this.products.iterator();
    }

    /**
     * Returns the {@link Product} object with the specified
     * <code>code</code>.
     *
     * @param code  the code of an item.
     * @return  The {@link Product} object with the specified
     *          code. Returns <code>null</code> if the object with
     *          the code is not found.
     */
    public Product getProduct(String code) {

        for (Product product : this.products) {
            if (product.getCode().equals(code)) {

                return product;
            }
        }

        return null;
    }

    /**
     * Returns the number of products in the product catalog.
     *
     * @return the number of {@link Product} objects in this product catalog.
     */
    public int getNumberOfProducts(){
        return this.products.size();
    }
}
/*!End Snippet:file*/
