/*!Begin Snippet:file*/


import java.io.FileNotFoundException;
import java.io.IOException;

/**
 * This interface declares a method for obtaining a library catalog
 * from a file.
 *
 * @author ydecube
 * @version 1.1.0
 * @see ProductCatalog
 */
public interface MilkProductCatalogLoader {

    /**
     * Loads the information in the specified file into a product
     * catalog and returns the catalog.
     *
     * @param filename  the name of the file that contains the
     *                  catalog data.
     * @return  a {@link ProductCatalog}.
     * @throws IOException if there is an error reading the
     *                     information in the specified file.
     * @throws FileNotFoundException  if the specified file does not
     *                                exist.
     * @throws DataFormatException if the file contains badly-formed
     *                             data.
     */
    ProductCatalog loadCatalog(String filename) throws IOException,
            FileNotFoundException, DataFormatException;
}
/*!End Snippet:file*/
