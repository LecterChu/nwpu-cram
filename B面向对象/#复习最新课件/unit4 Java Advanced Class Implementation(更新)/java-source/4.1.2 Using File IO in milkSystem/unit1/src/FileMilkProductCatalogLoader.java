/*!Begin Snippet:file*/


import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.StringTokenizer;

/**
 * Creates a product catalog of a milk store and loads it with
 * data stored in a file.
 *
 * @author ydecube
 * @version  1.0.0
 * @see MilkProductCatalogLoader
 * @see ProductCatalog
 * @see Product
 * @see Jelly
 * @see MilkDrink
 * @see PureMilk
 * @see Yogurt
 */
public class FileMilkProductCatalogLoader implements MilkProductCatalogLoader {

    /* Prefix of a line with jelly data */
    private final static String JELLY_PREFIX = "Jelly";

    /* Prefix of a line with milk drink data */
    private final static String MILKDRINK_PREFIX = "MilkDrink";

    /* Prefix of a line with pure milk data */
    private final static String PUREMILK_PREFIX = "PureMilk";

    /* Prefix of a line with yogurt data */
    private final static String YOGURT_PREFIX = "Yogurt";

    /* Delimiter */
    private final static String DELIM = "_";

    /* Date conversion format */
    SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd");

    /**
     * Loads the information in the specified file into a product
     * catalog and returns the catalog.
     *
     * @param filename  The name of a file that contains catalog
     *                  information.
     * @return a product catalog.
     * @throws IOException if there is an error reading the
     *                     information in the specified file.
     * @throws FileNotFoundException  if the specified file does not
     *                                exist.
     * @throws DataFormatException if the file contains malformed
     *                             data.
     */
    @Override
    public ProductCatalog loadCatalog(String filename) throws IOException,
            FileNotFoundException, DataFormatException {

        ProductCatalog productCatalog = new ProductCatalog();

        BufferedReader reader = new BufferedReader(new FileReader(filename));

        String line = reader.readLine();
        while (line != null) {
            Product product = null;
            try {

                if (line.startsWith(JELLY_PREFIX)) {
                    product = readJelly(line);
                } else if (line.startsWith(MILKDRINK_PREFIX)) {
                    product = readMilkDrink(line);
                } else if (line.startsWith(PUREMILK_PREFIX)) {
                    product = readPureMilk(line);
                } else if (line.startsWith(YOGURT_PREFIX)) {
                    product = readYogurt(line);
                } else {

                    throw new DataFormatException(line);
                }

                productCatalog.addProduct(product);

                line = reader.readLine();

            } catch (ParseException e) {
                e.printStackTrace();
            }
        }

        reader.close();

        return productCatalog;
    }

    /**
     * Extracts the jelly data in the specified line and returns
     * a {@link Jelly} object that encapsulates the jelly data.
     *
     * @param line  a string that contains jelly data.
     * @return  a <code>Jelly</code> object that encapsulates the
     *          jelly data in the specified line.
     * @throws DataFormatException if the line contains errors.
     * @throws ParseException if there is an error when parsing
     *                        the data.
     */
    private Jelly readJelly(String line)
            throws DataFormatException, ParseException {

        StringTokenizer tokenizer = new StringTokenizer(line,DELIM);

        if (tokenizer.countTokens() != 7) {

            throw new DataFormatException(line);
        } else {

            String prefix = tokenizer.nextToken();

            try {
                return new Jelly(tokenizer.nextToken(),
                        tokenizer.nextToken(),
                        Double.parseDouble(tokenizer.nextToken()),
                        simpleDateFormat.parse(tokenizer.nextToken()),
                        tokenizer.nextToken(),
                        tokenizer.nextToken()
                        );
            } catch (NumberFormatException  nfe)  {

                throw new DataFormatException(line);
            }
        }
    }

    /**
     * Extracts the milk drink data in the specified line and returns
     * a {@link MilkDrink} object that encapsulates the milk drink data.
     *
     * @param line  a string that contains milk drink data.
     * @return  a <code>MilkDrink</code> object that encapsulates the
     *          milk drink data in the specified line.
     * @throws DataFormatException if the line contains errors.
     * @throws ParseException if there is an error when parsing
     *                        the data.
     */
    private MilkDrink readMilkDrink (String line)
            throws DataFormatException, ParseException {

        StringTokenizer tokenizer =	new StringTokenizer(line, DELIM);

        if (tokenizer.countTokens() != 8) {

            throw new DataFormatException(line);
        } else {
            try {

                String prefix = tokenizer.nextToken();

                return new MilkDrink (tokenizer.nextToken(),
                        tokenizer.nextToken(),
                        Double.parseDouble(tokenizer.nextToken()),
                        simpleDateFormat.parse(tokenizer.nextToken()),
                        tokenizer.nextToken(),
                        tokenizer.nextToken(),
                        tokenizer.nextToken());

            } catch (NumberFormatException  nfe)  {

                throw new DataFormatException(line);
            }
        }
    }

    /**
     * Extracts the pure milk data in the specified line and returns
     * a {@link PureMilk} object that encapsulates the pure milk data.
     *
     * @param line  a string that contains pure milk data.
     * @return  a <code>PureMilk</code> object that encapsulates the
     *          pure milk data in the specified line.
     * @throws DataFormatException if the line contains errors.
     * @throws ParseException if there is an error when parsing
     *                        the data.
     */
    private PureMilk readPureMilk(String line)
            throws DataFormatException, ParseException {
        StringTokenizer tokenizer =	new StringTokenizer(line, DELIM);

        if (tokenizer.countTokens() != 9) {

            throw new DataFormatException(line);
        } else {
            try {

                String prefix = tokenizer.nextToken();

                return new PureMilk (tokenizer.nextToken(),
                        tokenizer.nextToken(),
                        Double.parseDouble(tokenizer.nextToken()),
                        simpleDateFormat.parse(tokenizer.nextToken()),
                        tokenizer.nextToken(),
                        tokenizer.nextToken(),
                        tokenizer.nextToken(),
                        tokenizer.nextToken());

            } catch (NumberFormatException  nfe)  {

                throw new DataFormatException(line);
            }
        }
    }

    /**
     * Extracts the yogurt data in the specified line and returns
     * a {@link Yogurt} object that encapsulates the yogurt data.
     *
     * @param line  a string that contains yogurt data.
     * @return  a <code>Yogurt</code> object that encapsulates the
     *          yogurt data in the specified line.
     * @throws DataFormatException if the line contains errors.
     * @throws ParseException if there is an error when parsing
     *                        the data.
     */
    private Yogurt readYogurt(String line)
            throws DataFormatException, ParseException {

        StringTokenizer tokenizer =	new StringTokenizer(line, DELIM);

        if (tokenizer.countTokens() != 8) {

            throw new DataFormatException(line);
        } else {
            try {

                String prefix = tokenizer.nextToken();

                return new Yogurt (tokenizer.nextToken(),
                        tokenizer.nextToken(),
                        Double.parseDouble(tokenizer.nextToken()),
                        simpleDateFormat.parse(tokenizer.nextToken()),
                        tokenizer.nextToken(),
                        tokenizer.nextToken(),
                        tokenizer.nextToken());

            } catch (NumberFormatException  nfe)  {

                throw new DataFormatException(line);
            }
        }
    }
}
/*!End Snippet:file*/
