
import java.util.*;

public class ProductValue  {
	
	/*	
	public static Product CreateProduct(String str,String deli){
		
		StringTokenizer tokenizer = new StringTokenizer(str, deli);
		if (tokenizer.countTokens() == 3){
			
			String name = tokenizer.nextToken();
	        int quantity = Integer.parseInt(tokenizer.nextToken());
	        double price = Double.parseDouble(tokenizer.nextToken());
			return new Product(name,quantity,price);
		} else {
			
			return null;
		}
        
	}*/
	
    public static void  main(String[]  args) {

        String data = "Mini Discs 74 Minute (10-Pack)_5_9.00";
        Product product = CreateProduct(data,"_");
        
        System.out.println("Name: " + product.getName());
        System.out.println("Quantity: " + product.getQuantity());
        System.out.println("Price: " + product.getPrice());
        System.out.println("Total: "+ product.getQuantity() * product.getPrice());
    }
}

