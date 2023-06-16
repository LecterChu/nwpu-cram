import java.util.*;
public class Generator {
	
	
	public static SaleItem createSaleItem

		
	}
    
		
	    public static void  main(String[]  args) {

	        String data = "A001_5_2013.54";
	        SaleItem saleItem = createSaleItem(data,"_");
	        System.out.println("isbn: " + saleItem.getIsbn());
	        System.out.println("unitSold: " + saleItem.getUnitsSold());
	        System.out.println("revenue: " + saleItem.getRevenue());
	
	    }
	
}
